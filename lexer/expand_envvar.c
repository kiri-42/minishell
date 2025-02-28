/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:15:33 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:15:34 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "common.h"

/*

hoge$HOME"HOGE"

$HOME
-> /home/akky
hoge + /home/akky + "HOGE"
*/

char	*expand_single_envvar(char *str, const char *from, const char *to,
		size_t *i)
{
	char	*replaced_str;
	char	*tmp_front;
	char	*tmp_back;

	tmp_front = ft_substr(str, 0, *i);
	tmp_back = replace_string(&str[*i + 1], from, to);
	*i = ft_strlen(tmp_front);
	if (to != NULL)
		*i += ft_strlen(to);
	replaced_str = ft_strjoin(tmp_front, tmp_back);
	free(tmp_front);
	free(tmp_back);
	return (replaced_str);
}

char	*replace_string(char *str, const char *from, const char *to)
{
	char	*replaced_str;
	char	*tmp;

	replaced_str = ft_strdup(to);
	tmp = ft_strjoin(replaced_str, &str[ft_strlen(from)]);
	free(replaced_str);
	replaced_str = tmp;
	return (replaced_str);
}

void	process_single_envvar(char **str, size_t *i, t_list *env)
{
	char		*env_var;
	char		*exit_s;
	char		*tmp;

	if (((*str)[*i + 1]) == '?')
	{
		exit_s = ft_itoa(g_exit_status);
		tmp = expand_single_envvar(*str, "?", exit_s, i);
		free(exit_s);
	}
	else
	{
		env_var = get_word(&((*str)[*i + 1]));
		tmp = expand_single_envvar(*str, env_var, ft_kvsget(env, env_var), i);
		free(env_var);
	}
	free(*str);
	*str = tmp;
}

char	*expand_envvar_str(const char *input, void *env)
{
	char	*str;
	size_t	i;
	bool	in_sq;
	bool	in_dq;

	in_sq = false;
	in_dq = false;
	str = ft_strdup(input);
	if (str == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i] != '\0')
	{
		update_flag(str[i], &in_sq, &in_dq);
		if (str[i] == '$' && str[i + 1] != '\0' && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?') && !in_sq)
			process_single_envvar(&str, &i, env);
		else
			i++;
	}
	return (str);
}

void	expand_envvar(t_list *lst, t_list *env_lst)
{
	char	*str;
	t_token	*token;
	bool	is_heredoc;

	is_heredoc = false;
	while (lst != NULL)
	{
		token = lst->content;
		if (token->type == TOKEN_IDENT)
		{
			if (is_heredoc)
			{
				is_heredoc = false;
			}
			else
			{
				str = expand_envvar_str(token->literal, env_lst);
				free(token->literal);
				token->literal = str;
			}
		}
		if (token->type == TOKEN_HEREDOC)
			is_heredoc = true;
		lst = lst->next;
	}
}
