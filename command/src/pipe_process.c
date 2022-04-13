/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:28:09 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 16:54:03 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	malloc_pipe_fd(t_pipe_attr *pa)
{
	size_t	i;

	pa->pipe_fd = (int **)ft_xmalloc(sizeof(int *) * pa->pipe_count);
	i = 0;
	while (i < (size_t)pa->pipe_count)
	{
		pa->pipe_fd[i] = (int *)ft_xmalloc(sizeof(int) * 2);
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

static int	signal_process(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
	return (sig + 128);
}

static void	wait_process(t_pipe_attr *pa)
{
	int		status;
	size_t	i;
	pid_t	pid;

	set_signal_handler_during_wait();
	i = 0;
	while (i < (size_t)pa->pipe_count + 1)
	{
		pid = waitpid(pa->cpid_array[i], &status, 0);
		if (pid == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	if (WIFSIGNALED(status))
		g_exit_status = signal_process(WTERMSIG(status));
	else
		g_exit_status = WEXITSTATUS(status);
}

void	pipe_process(t_exec_attr *ea, int pipe_count)
{
	t_pipe_attr	pa;
	t_list		*tmp;

	pa.pipe_count = pipe_count;
	malloc_pipe_fd(&pa);
	malloc_cpid_array(&pa);
	ea->is_unpermitted = (bool *)ft_calloc(1, pa.pipe_count + 1);
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
