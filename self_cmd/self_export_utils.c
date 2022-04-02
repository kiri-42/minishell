/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:07 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/19 17:22:14 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	print_all_export_lst(t_exec_attr *ea)
{
	t_content_f	f;

	f = print_export_kvs;
	ft_lstiter(ea->export_lst, f);
}

void	print_export_kvs(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	if (kvs->value == NULL)
		printf("declare -x %s\n", kvs->key);
	else
		printf("declare -x %s=%s\n", kvs->key, kvs->value);
}

bool	is_sharp(char *arg)
{
	if (arg == NULL)
		return (false);
	if (*arg == '#')
		return (true);
	return (false);
}

int	check_export_arg(char **arg)
{
	if (is_invalid_name(arg[KEY]))
		return (INVALID_IDENTIFER);
	if (arg[VALUE] == NULL)
		return (NO_VALUE);
	return (10);
}

void	store_null_env(t_exec_attr *ea, char *arg, bool *exit_stat)
{
	if (is_invalid_name(arg))
	{
		print_error_msg_with_var(EXPORT, arg);
		*exit_stat = false;
	}
	else
	{
		store_arg_in_export(ea, arg, NULL);
		store_arg_in_env(ea, arg, NULL);
	}
}
