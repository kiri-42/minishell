/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:28:14 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/23 16:22:43 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	run_cmd(t_exec_attr *ea, t_pipe_attr *pa, char *cmd_path)
{
	char	**cmdv;
	char	**environ;

	environ = convert_envlst_to_array(ea);
	cmdv = convert_lst_to_vector(pa->current_cmd->args);
	if (is_self_cmd(pa->current_cmd->cmd))
	{
		execute_self_cmd(pa->current_cmd, ea, PIPE);
		free(cmd_path);
		exit(0);
	}
	else
	{
		if (execve(cmd_path, cmdv, environ) == -1)
		{
			execve_error(errno, pa->current_cmd->cmd);
			exit(EXIT_FAILURE);
		}
	}
}

static void	set_cmd_path(char **cmd_path, t_pipe_attr *pa, t_exec_attr *ea)
{
	if (is_path(pa->current_cmd->cmd))
		*cmd_path = ft_strdup(pa->current_cmd->cmd);
	else
	{
		*cmd_path = find_path(pa->current_cmd->cmd, ea, pa->cmd_i);
		if (*cmd_path == NULL)
		{
			if (ea->is_unpermitted[pa->cmd_i])
				print_error_and_exit(pa->current_cmd->cmd,
					126, "Permission denied");
			else
				print_error_and_exit(pa->current_cmd->cmd,
					127, "command not found");
		}
	}
}

static void	close_pipe(t_pipe_attr *pa)
{
	ft_xclose(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN]);
	ft_xclose(pa->pipe_fd[pa->cmd_i - 1][PIPE_OUT]);
}

static void	set_pipe_fd(t_pipe_attr *pa)
{
	if (pa->cmd_i == 0)
	{
		ft_xdup2(pa->pipe_fd[pa->cmd_i][PIPE_OUT], STDOUT_FILENO);
		ft_xclose(pa->pipe_fd[pa->cmd_i][PIPE_IN]);
		ft_xclose(pa->pipe_fd[pa->cmd_i][PIPE_OUT]);
	}
	else if (pa->cmd_i == pa->pipe_count)
	{
		ft_xdup2(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN], STDIN_FILENO);
		ft_xclose(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN]);
		ft_xclose(pa->pipe_fd[pa->cmd_i - 1][PIPE_OUT]);
	}
	else
	{
		ft_xdup2(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN], STDIN_FILENO);
		ft_xdup2(pa->pipe_fd[pa->cmd_i][PIPE_OUT], STDOUT_FILENO);
		ft_xclose(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN]);
		ft_xclose(pa->pipe_fd[pa->cmd_i - 1][PIPE_OUT]);
		ft_xclose(pa->pipe_fd[pa->cmd_i][PIPE_IN]);
		ft_xclose(pa->pipe_fd[pa->cmd_i][PIPE_OUT]);
	}
}

// TODO:構造体がexec単位でわけられているので、eaを渡したくない
void	exec_cmd(t_exec_attr *ea, t_pipe_attr *pa)
{
	int		pid;
	char	*cmd_path;

	cmd_path = NULL;
	pid = ft_xfork();
	pa->cpid_array[pa->cmd_i] = pid;
	if (pid == 0)
	{
		if (has_redirect_file(pa->current_cmd))
			open_files_in_pipe(pa->current_cmd, ea);
		set_pipe_fd(pa);
		if (!is_self_cmd(pa->current_cmd->cmd))
		{
			set_cmd_path(&cmd_path, pa, ea);
			if (is_dir(cmd_path))
				print_error_and_exit(pa->current_cmd->cmd,
					126, "is a directory");
		}
		if (has_redirect_file(pa->current_cmd))
			redirect(pa->current_cmd, ea);
		run_cmd(ea, pa, cmd_path);
	}
	else if (pa->cmd_i > 0)
		close_pipe(pa);
}
