/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:22 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/21 16:23:42 by tkirihar         ###   ########.fr       */
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
	if (ft_strlen(pathname) == 0)
		return (NULL);
	return (pathname);
}

int	exec_self_pwd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*pathname;

	(void)cmd;
	pathname = get_pathname(ea);
	if (pathname == NULL)
		pathname = ea->current_pwd;
	ft_putstr_fd(pathname, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
