/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:28:09 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 15:48:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "errno.h"

static void	malloc_pipe_fd(t_pipe_attr *pa)
{
	int	i;

	pa->pipe_fd = (int **)malloc(sizeof(int *) * pa->pipe_count);
	if (pa->pipe_fd == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pa->pipe_count)
	{
		pa->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pa->pipe_fd[i] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return ;
}

static void	malloc_cpid_array(t_pipe_attr *pa)
{
	pa->cpid_array = (int *)malloc(sizeof(int *) * (pa->pipe_count + 1));
	if (pa->cpid_array == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
}

static void	wait_process(t_pipe_attr *pa)
{
	int		status;
	int		i;
	pid_t	pid;
	bool	is_EINTR;

	i = 0;
	while (i < pa->pipe_count + 1)
	{
		is_EINTR = false;
		while (true)
		{
			pid = waitpid(pa->cpid_array[i], &status, 0);
			if (pid > 0)
				break ;
			if (errno == EINTR)
			{
				is_EINTR = true;
				continue ;
			}
			exit(EXIT_FAILURE);
		}
		if (!is_EINTR)
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	pipe_process(t_exec_attr *ea, int pipe_count)
{
	t_pipe_attr	pa;
	t_list		*tmp;

	pa.pipe_count = pipe_count;
	malloc_pipe_fd(&pa);
	malloc_cpid_array(&pa);
	ea->is_unpermitted = (bool *)ft_xmalloc(pa.pipe_count + 1);
	pa.cmd_i = 0;
	tmp = ea->cmd_lst;
	while (pa.cmd_i < pa.pipe_count + 1)
	{
		pa.current_cmd = tmp->content;
		make_pipe(&pa);
		exec_cmd(ea, &pa);
		pa.cmd_i++;
		tmp = tmp->next;
	}
	wait_process(&pa);
	free_pipe_attr(&pa);
	free(ea->is_unpermitted);
}
