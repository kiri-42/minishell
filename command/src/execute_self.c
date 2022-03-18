/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:51:22 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/18 15:45:25 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static bool	is_(char *command, char *cmd)
{
	if (is_same_str(cmd, command))
		return (true);
	return (false);
}

void	execute_self_cmd(t_cmd	*c, t_exec_attr *ea, bool is_pipe)
{
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
