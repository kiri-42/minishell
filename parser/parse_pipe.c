/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:35:31 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:35:32 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

static bool	is_invalid(t_list *left_tokens, t_cmd **cmd)
{
	if (((t_token *)left_tokens->content)->type == TOKEN_EOF)
	{
		*cmd = cmd_init();
		(*cmd)->is_invalid_syntax = true;
		return (true);
	}
	return (false);
}

static void	check_valid(t_list *right_tokens, t_list **lst)
{
	if (((t_token *)right_tokens->content)->type == TOKEN_EOF)
		((t_cmd *)(*lst)->content)->is_invalid_syntax = true;
}

t_list	*parse_pipe_helper(t_list *token_list, t_list **heredocs)
{
	t_list	*right_tokens;
	t_list	*left_tokens;
	t_token	*token;
	t_list	*lst;
	t_cmd	*cmd;

	left_tokens = token_list;
	if (is_invalid(left_tokens, &cmd))
		return (ft_lstnew(cmd));
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF)
			break ;
		if (token->type == TOKEN_PIPE)
		{
			right_tokens = token_list->next;
			lst = parse_pipe_helper(right_tokens, heredocs);
			check_valid(right_tokens, &lst);
			ft_lstadd_front(&lst, ft_lstnew(parse_cmd(left_tokens, heredocs)));
			return (lst);
		}
		token_list = token_list->next;
	}
	return (ft_lstnew(parse_cmd(left_tokens, heredocs)));
}

t_list	*parse_pipe(t_list *token_list, t_list **heredocs)
{
	t_list	*result;

	result = parse_pipe_helper(token_list, heredocs);
	if (result == NULL)
		return (NULL);
	return (result);
}
