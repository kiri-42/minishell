/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:28:11 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 15:28:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "errno.h"

void	print_error_and_exit(char *cmd, int exits, char *err)
{
	ft_put_cmd_error(cmd, err);
	exit(exits);
}

void	make_pipe(t_pipe_attr *pa)
{
	if (pa->cmd_i != pa->pipe_count)
	{
		pipe(pa->pipe_fd[pa->cmd_i]);
	}
}
