/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:11:48 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:11:49 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command.h"

void	execute_cmd(t_exec_attr *ea)
{
	int	pipe_count;

	if (ea->cmd_lst == NULL)
		return ;
	pipe_count = ft_lstsize(ea->cmd_lst) - 1;
	if (pipe_count == 0)
	{
		no_pipe_process(ea);
	}
	else
	{
		pipe_process(ea, pipe_count);
	}
	return ;
}
