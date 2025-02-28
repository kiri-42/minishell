/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_attr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:02 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 16:26:16 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	free_pipe_fd(t_pipe_attr *pa)
{
	int	i;

	i = 0;
	while (i < pa->pipe_count)
	{
		free(pa->pipe_fd[i]);
		i++;
	}
	free(pa->pipe_fd);
}

void	free_pipe_attr(t_pipe_attr *pa)
{
	free_pipe_fd(pa);
	free(pa->cpid_array);
}
