/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:45 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 16:21:42 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"
#include "command.h"

void	finish_has_diff(char *cwd, char *pwd, char *path, char *pwd_del_dot)
{
	if (*path != '/')
		free(pwd);
	free(pwd_del_dot);
	free(cwd);
}

bool	has_diff(char *path, t_exec_attr *ea)
{
	char		*cwd;
	char		*pwd;
	bool		flag;
	char		*pwd_del_dot;
	struct stat	buf;

	cwd = x_getcwd(ea);
	if (*path == '/')
		pwd = path;
	else
		pwd = create_new_pwd(ea->current_pwd, path);
	pwd_del_dot = remove_relative(pwd);
	if (lstat(pwd_del_dot, &buf) == -1)
	{
		finish_has_diff(cwd, pwd, path, pwd_del_dot);
		return (false);
	}
	flag = is_same_str(cwd, pwd_del_dot);
	finish_has_diff(cwd, pwd, path, pwd_del_dot);
	return (!flag);
}

char	*get_new_pwd(t_exec_attr *ea, char *path)
{
	char	*new_pwd;
	char	*tmp;

	if (has_diff(path, ea))
	{
		tmp = create_new_pwd(ea->current_pwd, path);
		new_pwd = remove_relative(tmp);
		free(tmp);
	}
	else
	{
		new_pwd = x_getcwd(ea);
		if (new_pwd == NULL)
		{
			print_error(PWD, path);
			return (NULL);
		}
	}
	return (new_pwd);
}

int	x_chdir(char *arg, t_exec_attr *ea)
{
	char	*new_pwd;
	char	*path;

	if (chdir(arg) == -1)
	{
		print_error(CD, arg);
		return (1);
	}
	if (!is_current_dir_exist(ea))
	{
		create_virtual_path(arg, ea);
		return (1);
	}
	if (is_end_of_slash(arg))
		path = create_str_removed_end(arg);
	else
		path = ft_strdup(arg);
	new_pwd = get_new_pwd(ea, path);
	if (new_pwd == NULL)
		return (1);
	update_all_environ(new_pwd, ea);
	free(path);
	free(new_pwd);
	return (0);
}

int	exec_self_cd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;
	int		status;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return (1);
	status = x_chdir(argv_one, ea);
	return (status);
}
