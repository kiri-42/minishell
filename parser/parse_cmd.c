/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:40:19 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:40:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdbool.h>

/*
input: cat fuga.txt ... hoge.txt > b.txt
[TOKEN_IDENT, TOKEN_IDENT, TOKEN_REDIRECT_OUT, TOKEN_IDENT, TOKEN_EOF]
*/

void
	addback_newfile(t_token **token, t_list *lst, t_list **file, bool append)
{
	*token = lst->next->content;
	ft_lstadd_back(file, ft_lstnew(new_file((*token)->literal, append)));
}

void	addback_heredocfile(t_list **heredocs, t_token **token,
		t_list *lst, t_cmd *cmd)
{
	char	*filename;

	(*token) = lst->next->content;
	filename = ft_kvsget(*heredocs, (*token)->literal);
	ft_lstadd_back(&cmd->filenames_in, ft_lstnew(new_file(filename, true)));
}

t_cmd	*parse_cmd(t_list *token_list, t_list **heredocs)
{
	t_cmd	*cmd;
	t_token	*token;
	t_list	*lst;

	cmd = cmd_init();
	lst = token_list;
	while (lst != NULL)
	{
		token = lst->content;
		if (token->type == TOKEN_EOF || token->type == TOKEN_PIPE)
			break ;
		if (token->type == TOKEN_REDIRECT_IN)
			addback_newfile(&token, lst, &cmd->filenames_in, false);
		else if (token->type == TOKEN_REDIRECT_OUT)
			addback_newfile(&token, lst, &cmd->filenames_out, false);
		else if (token->type == TOKEN_REDIRECT_APPEND)
			addback_newfile(&token, lst, &cmd->filenames_out, true);
		else if (token->type == TOKEN_HEREDOC)
			addback_heredocfile(heredocs, &token, lst, cmd);
		lst = lst->next;
	}
	parse_exec(token_list, &cmd);
	return (cmd);
}
