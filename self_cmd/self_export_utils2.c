/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:50:03 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/11 22:51:30 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

bool	addlst_sort_by_ascii(t_list **export_lst, char **arg)
{
	bool	flag;

	flag = ft_lstadd_back(export_lst, \
			ft_lstnew(ft_kvsnew(arg[KEY], \
				create_export_value(arg[VALUE]))));
	if (!flag)
		return (false);
	sort_listkey_by_ascii(*export_lst);
	return (true);
}

void	store_env(int ret, t_exec_attr *ea, char **kv, int export_type)
{
	if (ret == NO_VALUE)
		kv[VALUE] = ft_strdup("");
	if (!store_arg_in_env(ea, kv[KEY], kv[VALUE], export_type))
	{
		perror("store_env");
		exit(EXIT_FAILURE);
	}
	if (!store_arg_in_export(ea, kv[KEY], kv[VALUE], export_type))
	{
		perror("store_env");
		exit(EXIT_FAILURE);
	}
}
