/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:51:22 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/30 15:32:49 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static bool	is_(char *command, char *cmd)
{
	if (is_same_str(cmd, command))
		return (true);
	return (false);
}

int	exec_redirect_process(t_cmd *c, t_exec_attr *ea)
{
	ssize_t	read_ret;
	char	buf[128];

	(void)ea;
	if (c->filenames_out == NULL)
		return (0);
	read_ret = ft_xread(STDIN_FILENO, (void *)buf, sizeof(buf) - 1);
	while (read_ret != 0)
	{
		printf("%s", buf);
		read_ret = ft_xread(STDIN_FILENO, (void *)buf, sizeof(buf) - 1);
	}
	return (0);
}

void	execute_self_cmd(t_cmd	*c, t_exec_attr *ea, bool is_pipe)
{
	if (c->cmd == NULL && has_redirect_file(c))
		g_exit_status = exec_redirect_process(c, ea);
	if (is_(CD, c->cmd))
		g_exit_status = exec_self_cd(c, ea);
	else if (is_(EXPORT, c->cmd))
		g_exit_status = exec_self_export(c, ea);
	else if (is_(EXIT, c->cmd))
		g_exit_status = exec_self_exit(c, is_pipe);
	else if (is_(UNSET, c->cmd))
		g_exit_status = exec_self_unset(c, ea);
	else if (is_(PWD, c->cmd))
		g_exit_status = exec_self_pwd(c, ea);
	else if (is_(ECHO, c->cmd))
		g_exit_status = exec_self_echo(c, ea);
	else if (is_(ENV, c->cmd))
		g_exit_status = exec_self_env(c, ea);
	if (is_pipe)
		exit(g_exit_status);
}

bool	is_self_cmd(char *cmd)
{
	if (cmd == NULL)
		return (true);
	if (is_(CD, cmd))
		return (true);
	if (is_(EXPORT, cmd))
		return (true);
	if (is_(EXIT, cmd))
		return (true);
	if (is_(UNSET, cmd))
		return (true);
	if (is_(PWD, cmd))
		return (true);
	if (is_(ECHO, cmd))
		return (true);
	if (is_(ENV, cmd))
		return (true);
	return (false);
}
