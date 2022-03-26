/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:02:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/26 15:43:29 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

char	*x_getcwd(t_exec_attr *ea)
{
	char	*ret;

	redirect_dev_null(ea);
	ret = getcwd(NULL, 0);
	reset_stdfd(ea);
	return (ret);
}

bool	is_current_dir_exist(t_exec_attr *ea)
{
	char	*pwd;

	pwd = x_getcwd(ea);
	free(pwd);
	if (pwd == NULL)
		return (false);
	return (true);
}

void	create_virtual_path(char *path, t_exec_attr *ea)
{
	char	*pwd;
	char	*new_pwd;

	pwd = ea->current_pwd;
	new_pwd = x_getcwd(ea);
	if (new_pwd == NULL)
	{
		new_pwd = create_new_pwd(pwd, path);
		ft_putstr_fd("cd: error retrieving current directory: \
getcwd: cannot access parent directories: \
No such file or directory\n", STDERR_FILENO);
	}
	update_all_environ(new_pwd, ea);
	free(new_pwd);
}

bool	set_new_split_len(char **split, long long *new_split_len)
{
	size_t	i;
	size_t	ddot_count;
	size_t	dot_count;

	i = 0;
	ddot_count = 0;
	dot_count = 0;
	while (split[i] != NULL)
	{
		if (is_same_str(".", split[i]))
			dot_count++;
		if (is_same_str("..", split[i]))
			ddot_count++;
		i++;
	}
	if (i + 1 < dot_count + (ddot_count * 2))
	{
		free_char_dptr(split);
		return (false);
	}
	*new_split_len = i - dot_count + 1;
	return (true);
}

bool	search_dots(size_t *i, size_t *j, char **new_split, char **split)
{
	if (is_same_str(".", split[*i]))
	{
		(*i)++;
		return (true);
	}
	if (is_same_str("..", split[*i]))
	{
		if ((*j) != 0)
		{
			free(new_split[*j - 1]);
			new_split[*j - 1] = NULL;
			(*j)--;
		}
		(*i)++;
		return (true);
	}
	return (false);
}
