/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:40:10 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:40:11 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_cmds(t_list *cmds)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	cmd_list = cmds;
	while (cmd_list != NULL)
	{
		cmd = cmd_list->content;
		if (cmd->is_invalid_syntax)
			return (false);
		cmd_list = cmd_list->next;
	}
	return (true);
}

bool	is_valid_cmd(t_cmd *cmd)
{
	return (!(cmd->cmd == NULL && cmd->filenames_in == NULL
			&& cmd->filenames_out == NULL));
}
