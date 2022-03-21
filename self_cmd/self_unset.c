/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:32 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/21 15:11:48 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

int	exec_self_unset(t_cmd *cmd, t_exec_attr *ea)
{
	t_list	*lst;
	char	*arg;
	int		exit_status;

	exit_status = true;
	lst = cmd->args->next;
	while (lst != NULL)
	{
		arg = (char *)(lst->content);
		if (arg == NULL)
			return (1);
		if (is_invalid_name(arg))
		{
			exit_status = false;
			print_error_msg_with_var(UNSET, arg);
		}
		del_env_lst_by_key(ea->env_lst, arg, ea);
		del_export_lst_by_key(ea->export_lst, arg, ea);
		if (is_same_str(arg, "PWD"))
			(ea->current_pwd)[0] = '\0';
		lst = lst->next;
	}
	if (exit_status)
		return (0);
	return (1);
}
