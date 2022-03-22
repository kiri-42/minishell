/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:31:45 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/22 15:25:20 by tkirihar         ###   ########.fr       */
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
	size_t	tmp;

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
	tmp = i - dot_count - (ddot_count * 2) + 1;
	if (tmp < 0)
	{
		free_char_dptr(split);
		return (false);
	}
	*new_split_len = i - dot_count + 1;
	return (true);
}


/* If the path is ".." exists, the previous path is deleted. except for the first absolute path. */
/* Free one previous new_split if there is ".." */
/* Decrement j. However, if j is negative, stop. */
char	**get_new_split(long long new_split_len, char **split, size_t *new_str_len)
{
	char	**new_split;
	size_t	i;
	size_t	j;

	new_split = (char **)ft_xmalloc(sizeof(char *) * new_split_len);
	i = 0;
	j = 0;
	*new_str_len = 0;
	while (split[i] != NULL)
	{
		if (is_same_str(".", split[i]))
		{
			i++;
			continue ;
		}
		if (is_same_str("..", split[i]))
		{
			if (j != 0)
			{
				free(new_split[j - 1]);
				new_split[j - 1] = NULL;
				j--;
			}
			i++;
			continue ;
		}
		new_split[j] = ft_strjoin("/", split[i]);
		*new_str_len += ft_strlen(new_split[j]);
		j++;
		i++;
	}
	new_split[j] = NULL;
	return (new_split);
}

char	*get_new_path(char **new_split, size_t new_str_len)
{
	size_t	i;
	char 	*new_path;

	new_path = (char *)ft_calloc(sizeof(char), new_str_len + 1);
	i = 0;
	while (new_split[i] != NULL)
	{
		ft_strlcat(new_path, new_split[i], new_str_len + 1);
		i++;
	}
	return (new_path);
}

char	*remove_relative(char *path)
{
	char	**split;
	char	**new_split;
	char	*new_path;
	// size_t	i;
	size_t	new_str_len;
	long long	new_split_len;

	new_str_len = 0;
	split = ft_split(path, '/');
	if (!set_new_split_len(split, &new_split_len))
		return (ft_strdup("/"));
	new_split = get_new_split(new_split_len, split, &new_str_len);
	new_path = get_new_path(new_split, new_str_len);
	if (is_end_of_slash(new_path))
		path = create_str_removed_end(new_path);
	free_char_dptr(split);
	free_char_dptr(new_split);
	return (new_path);
}

void	finish_has_diff(char *cwd, char *pwd, char *path, char *pwd_del_dot)
{
	if (*path != '/')
		free(pwd);
	free(pwd_del_dot);
	free(cwd);
}

bool	has_diff(char *path, t_exec_attr *ea)
{
	char		*cwd;
	char		*pwd;
	bool		flag;
	char		*pwd_del_dot;
	struct stat	buf;

	cwd = x_getcwd(ea);
	if (*path == '/')
		pwd = path;
	else
		pwd = create_new_pwd(ea->current_pwd, path);
	pwd_del_dot = remove_relative(pwd);
	if (lstat(pwd_del_dot, &buf) == -1)
	{
		finish_has_diff(cwd, pwd, path, pwd_del_dot);
		return (false);
	}
	flag = is_same_str(cwd, pwd_del_dot);
	finish_has_diff(cwd, pwd, path, pwd_del_dot);
	return (!flag);
}

char	*get_new_pwd(t_exec_attr *ea, char *path)
{
	char	*new_pwd;
	char	*tmp;

	if (has_diff(path, ea))
	{
		tmp = create_new_pwd(ea->current_pwd, path);
		new_pwd = remove_relative(tmp);
		free(tmp);
	}
	else
	{
		new_pwd = x_getcwd(ea);
		if (new_pwd == NULL)
		{
			print_error(PWD, path);
			return (NULL);
		}
	}
	return (new_pwd);
}

int	x_chdir(char *arg, t_exec_attr *ea)
{
	char	*new_pwd;
	char	*path;

	if (chdir(arg) == -1)
	{
		print_error(CD, arg);
		return (1);
	}
	if (!is_current_dir_exist(ea))
	{
		create_virtual_path(arg, ea);
		return (1);
	}
	if (is_end_of_slash(arg))
		path = create_str_removed_end(arg);
	else
		path = ft_strdup(arg);
	new_pwd = get_new_pwd(ea, path);
	if (new_pwd == NULL)
		return (1);
	update_all_environ(new_pwd, ea);
	free(path);
	free(new_pwd);
	return (0);
}

int	exec_self_cd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;
	int		status;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return (1);
	status = x_chdir(argv_one, ea);
	return (status);
}
