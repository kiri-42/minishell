/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:22 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:31:24 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

char	*x_getcwd(t_exec_attr *ea)
{
	char	*pathname;
	t_list	*lst;

	lst = get_lst_by_key(ea->env_lst, "PWD");
	if (lst == NULL)
		return (NULL);
	pathname = ft_kvsget_value(lst->content);
	// PWDが空文字のときはea->current_pwdを使用する
	if (ft_strlen(pathname) == 0)
		return (NULL);
	return (pathname);
}

int	exec_self_pwd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*pathname;

	(void)cmd;
	pathname = x_getcwd(ea);
	if (pathname == NULL)
		pathname = ea->current_pwd;
	ft_putstr_fd(pathname, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
