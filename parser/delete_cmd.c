/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:40:02 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:40:03 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_cmd(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
	free((*cmd)->cmd);
	(*cmd)->cmd = NULL;
	if ((*cmd)->args != NULL)
		ft_lstclear(&(*cmd)->args, &free);
	(*cmd)->args = NULL;
	ft_lstclear(&(*cmd)->filenames_in, delete_file);
	(*cmd)->filenames_in = NULL;
	ft_lstclear(&(*cmd)->filenames_out, delete_file);
	(*cmd)->filenames_out = NULL;
	free(*cmd);
	(*cmd) = NULL;
}

void	delete_pipe(void *cmd)
{
	t_cmd	*redirect_cmd;

	redirect_cmd = (t_cmd *)cmd;
	delete_cmd(&redirect_cmd);
}
