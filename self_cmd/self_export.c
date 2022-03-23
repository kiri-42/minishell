/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:32:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/23 16:10:59 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

int	exec_self_export(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;
	bool	exit_stat;

	exit_stat = true;
	argv_one = get_argv_one(cmd);
	if (argv_one == NULL || is_sharp(argv_one))
		print_all_export_lst(ea);
	else
		export_with_args(cmd, ea, &exit_stat);
	if (exit_stat)
		return (0);
	return (1);
}

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

static void	error_process(char *var, bool *exit_stat)
{
	*exit_stat = false;
	print_error_msg_with_var(EXPORT, var);
}

void	store_env(int ret, t_exec_attr *ea, char **kv)
{
	if (ret == NO_VALUE)
		kv[VALUE] = ft_strdup("");
	if (!store_arg_in_env(ea, kv[KEY], kv[VALUE]))
	{
		perror("store_env");
		exit(EXIT_FAILURE);
	}
	if (!store_arg_in_export(ea, kv[KEY], kv[VALUE]))
	{
		perror("store_env");
		exit(EXIT_FAILURE);
	}
}

void	export_with_args(t_cmd *cmd, t_exec_attr *ea, bool *exit_stat)
{
	char		**kv;
	int			ret;
	char		*arg;
	t_list		*lst;

	lst = cmd->args->next;
	while (lst != NULL)
	{
		arg = (char *)(lst->content);
		if (ft_strchr(arg, '=') == NULL)
			store_null_env(ea, arg, exit_stat);
		else if (ft_strchr(arg, '=') == arg)
			error_process(arg, exit_stat);
		else
		{
			kv = ft_separate(arg, '=');
			ret = check_export_arg(kv);
			if (ret == INVALID_IDENTIFER)
				error_process(kv[KEY], exit_stat);
			else
				store_env(ret, ea, kv);
			free_char_dptr(kv);
		}
		lst = lst->next;
	}
}
