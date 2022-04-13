/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:22 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 15:55:47 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

/* Use ea->current_pwd if PWD is an empty string */
static char	*get_pathname(t_exec_attr *ea)
{
	char	*pathname;
	t_list	*lst;

	lst = get_lst_by_key(ea->env_lst, "PWD");
	if (lst == NULL)
		return (NULL);
	pathname = ft_kvsget_value(lst->content);
	if (!pathname || ft_strlen(pathname) == 0)
		return (NULL);
	return (pathname);
}

int	exec_self_pwd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*pathname;

	(void)cmd;
	pathname = get_pathname(ea);
	if (ea->current_pwd == NULL && !is_current_dir_exist(ea))
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		return (0);
	}
	if (pathname == NULL)
		pathname = ea->current_pwd;
	else
	{
		ft_putstr_fd(pathname, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
