/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:32:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/11 17:24:09 by tkirihar         ###   ########.fr       */
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

static void	error_process(char *var, bool *exit_stat)
{
	*exit_stat = false;
	print_error_msg_with_var(EXPORT, var);
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

int	check_export_type(char *arg)
{
	char	*strchr_ret;

	strchr_ret = ft_strchr(arg, '=');
	if (strchr_ret == NULL)
		return (EXPORT_ERROR);
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

char	**ft_separate2(char *str, char *separators)
{
	char	**ret;
	char	*front_sep_ptr;
	size_t	separators_len;

	if (str == NULL || separators == NULL)
		return (NULL);
	front_sep_ptr = ft_strnstr(str, separators, ft_strlen(str));
	if (front_sep_ptr == NULL)
		return (NULL);
	ret = (char **)ft_xmalloc(sizeof(char *) * (2 + 1));
	separators_len = ft_strlen(separators);
	if (*(front_sep_ptr + separators_len) == '\0')
	{
		ret[0] = ft_substr(str, 0, front_sep_ptr - str);
		ret[1] = NULL;
		ret[2] = NULL;
		return (ret);
	}
	ret[0] = ft_substr(str, 0, front_sep_ptr - str);
	ret[1] = ft_strdup(front_sep_ptr + separators_len);
	ret[2] = NULL;
	return (ret);
}

void	export_with_args(t_cmd *cmd, t_exec_attr *ea, bool *exit_stat)
{
	char		**kv;
	int			ret;
	char		*arg;
	t_list		*lst;
	int			export_type;

	lst = cmd->args->next;
	while (lst != NULL)
	{
		arg = (char *)(lst->content);
		export_type = check_export_type(arg);
		if (export_type == EXPORT_ERROR)
			store_null_env(ea, arg, exit_stat);
		else if (export_type == EXPORT_NOKEY)
			error_process(arg, exit_stat);
		else
		{
			if (export_type == EXPORT_APPEND)
			{
				kv = ft_separate2(arg, "+=");
				ret = check_export_arg(kv);
				if (ret == INVALID_IDENTIFER)
					error_process(kv[KEY], exit_stat);
				else
					store_env(ret, ea, kv, export_type);
				free_char_dptr(kv);
			}
			else if (export_type == EXPORT_NEW)
			{
				kv = ft_separate(arg, '=');
				ret = check_export_arg(kv);
				if (ret == INVALID_IDENTIFER)
					error_process(kv[KEY], exit_stat);
				else
					store_env(ret, ea, kv, export_type);
				free_char_dptr(kv);
			}
		}
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
	else
		export_with_args(cmd, ea, &exit_stat);
	if (exit_stat)
		return (0);
	return (1);
}
