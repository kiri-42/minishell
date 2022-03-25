/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvar_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:15:30 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:34:55 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	update_flag(char c, bool *in_sq, bool *in_dq)
{
	if (c == '\'')
	{
		if (*in_sq == false && *in_dq == false)
			*in_sq = true;
		else if (*in_sq == true && *in_dq == false)
			*in_sq = false;
	}
	if (c == '\"')
	{
		if (*in_sq == false && *in_dq == false)
			*in_dq = true;
		else if (*in_sq == false && *in_dq == true)
			*in_dq = false;
	}
}

bool	is_word_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* return argv[i] when $0 ~ $9 */
char	*get_word(char *str)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		exit(EXIT_FAILURE);
	while (is_word_char(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}
