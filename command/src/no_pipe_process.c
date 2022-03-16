/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:53:46 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/16 16:53:47 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	child_process(char *cmd_path, char **cmdv, t_cmd *c, \
							t_exec_attr *ea)
{
	char	**environ;

	environ = convert_envlst_to_array(ea);
	if (is_dir(cmd_path))
	{
		ft_put_cmd_error(c->cmd, "is a directory");
		exit(126);
	}
	if (has_redirect_file(c))
		redirect(c, ea);
	if (execve(cmd_path, cmdv, environ) == -1)
		execve_error(errno, c->cmd);
}

static void	parent_process(char *cmd_path, char **cmdv, pid_t cpid)
{
	pid_t	wait_ret;
	int		status;

	free(cmd_path);
	free_char_dptr(cmdv);
	while (true)
	{
		wait_ret = waitpid(cpid, &status, 0);
		if (wait_ret > 0)
			break ;
		if (WIFSIGNALED(status))
			continue ;
		exit(EXIT_FAILURE);
	}
	if (!WIFSIGNALED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	fork_process(char *cmd_path, t_exec_attr *ea, t_cmd *c, char **cmdv)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0)
		child_process(cmd_path, cmdv, c, ea);
	else
		parent_process(cmd_path, cmdv, cpid);
}

void	execute_ext_cmd(t_cmd *c, t_exec_attr *ea)
{
	char	**cmdv;
	char	*cmd_path;

	cmdv = convert_lst_to_argv(c->args);
	if (is_path(c->cmd))
		cmd_path = ft_strdup(c->cmd);
	else
	{
		cmd_path = find_path(c->cmd, ea, 0);
		if (cmd_path == NULL)
		{
			free_char_dptr(cmdv);
			if (ea->is_unpermitted[0])
				print_error_and_set_es(c->cmd, 126, "Permission denied");
			else
				print_error_and_set_es(c->cmd, 127, "command not found");
			return ;
		}
	}
	fork_process(cmd_path, ea, c, cmdv);
}

/* 135(if (has_redirect_file(c))):fileのopenの処理はコマンドに関わらず行う */
/* 144(if (c->cmd == NULL)):TODO: コマンドが存在しない時、ここでsegvする */

void	no_pipe_process(t_exec_attr *ea)
{
	t_cmd	*c;

	c = get_cmd(ea);
	ea->is_unpermitted = malloc_is_unpermitted(1);
	if (check_redirect_file(c, ea))
		return ;
	if (c->cmd == NULL)
	{
		free(ea->is_unpermitted);
		return ;
	}
	if (is_self_cmd(c->cmd))
	{
		if (has_redirect_file(c))
			redirect(c, ea);
		execute_self_cmd(c, ea, NO_PIPE);
		if (has_redirect_file(c))
			reset_stdfd(ea);
	}
	else
		execute_ext_cmd(c, ea);
	free(ea->is_unpermitted);
}
