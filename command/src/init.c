/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:12:49 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/12 16:23:44 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	init_oldpwd(t_exec_attr *ea)
{
	del_env_lst_by_key(ea->env_lst, "OLDPWD", ea);
	del_export_lst_by_key(ea->export_lst, "OLDPWD", ea);
	del_env_lst_by_key(ea->env_lst, "PWD", ea);
	del_export_lst_by_key(ea->export_lst, "PWD", ea);
	store_arg_in_export(ea, "OLDPWD", NULL, EXPORT_NEW);
	store_arg_in_env(ea, "OLDPWD", NULL, EXPORT_NEW);
	ea->current_pwd = getcwd(NULL, 0);
	if (!ea->current_pwd)
		ft_putstr_fd("shell-init: error retrieving current directory: getcwd\
		cannot access parent directories: No such file or directory\n", \
		STDERR_FILENO);
	store_arg_in_export(ea, "PWD", ea->current_pwd, EXPORT_NEW);
	store_arg_in_env(ea, "PWD", ea->current_pwd, EXPORT_NEW);
}

void	store_stdfd(t_exec_attr *ea)
{
	ea->stdfd[0] = dup(STDIN_FILENO);
	ea->stdfd[1] = dup(STDOUT_FILENO);
	ea->stdfd[2] = dup(STDERR_FILENO);
}

void	init_new(t_exec_attr **ea)
{
	extern char	**environ;

	*ea = (t_exec_attr *)ft_calloc(sizeof(t_exec_attr), 1);
	store_allenv_in_envlst(*ea, environ);
	store_allenv_in_export(*ea, environ);
	store_stdfd(*ea);
	init_oldpwd(*ea);
	(*ea)->is_sigint_hdoc = false;
}
