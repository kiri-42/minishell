/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:32:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/12 03:02:00 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

static void	error_process(char *var, bool *exit_stat)
{
	*exit_stat = false;
	print_error_msg_with_var(EXPORT, var);
}

int	check_export_type(char *arg)
{
	char	*strchr_ret;

	strchr_ret = ft_strchr(arg, '=');
	if (strchr_ret == NULL)
		return (EXPORT_NULL);
	if (is_same_str(strchr_ret, arg))
		return (EXPORT_NOKEY);
	if (*(strchr_ret - 1) == '+')
	{
		if (is_same_str(strchr_ret - 1, arg))
			return (EXPORT_NOKEY);
		return (EXPORT_APPEND);
	}
	return (EXPORT_NEW);
}

void	store_process(int export_type, char *arg, t_exec_attr *ea,
						 bool *exit_stat)
{
	char	**kv;
	int		ret;

	kv = NULL;
	if (export_type == EXPORT_APPEND)
		kv = ft_separate_str(arg, "+=");
	else if (export_type == EXPORT_NEW)
		kv = ft_separate(arg, '=');
	ret = check_export_arg(kv);
	if (ret == INVALID_IDENTIFER)
		error_process(kv[KEY], exit_stat);
	else
		store_env(ret, ea, kv, export_type);
	free_char_dptr(kv);
}

void	export_with_args(t_cmd *cmd, t_exec_attr *ea, bool *exit_stat)
{
	char		*arg;
	t_list		*lst;
	int			export_type;

	lst = cmd->args->next;
	while (lst != NULL)
	{
		arg = (char *)(lst->content);
		export_type = check_export_type(arg);
		if (export_type == EXPORT_NULL)
			store_null_env(ea, arg, exit_stat);
		else if (export_type == EXPORT_NOKEY)
			error_process(arg, exit_stat);
		else
			store_process(export_type, arg, ea, exit_stat);
		lst = lst->next;
	}
}

int	exec_self_export(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;
	bool	exit_stat;

	exit_stat = true;
	argv_one = get_argv_one(cmd);
	if (argv_one == NULL || is_sharp(argv_one))
		print_all_export_lst(ea);
	else if (ft_strlen(argv_one) == 0)
		error_process(argv_one, &exit_stat);
	else
		export_with_args(cmd, ea, &exit_stat);
	if (exit_stat)
		return (0);
	return (1);
}
