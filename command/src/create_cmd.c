/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:11:53 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 15:49:39 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

//  /* Since there is no readline, the environment variable of the original one
// 	is called if $ is put in the argument. */
// // Respond to be readable with QUOTE on.
// // arg++;
// bool	is_dollar(char *arg)
// {
// 	if (*arg == '$')
// 		return (true);
// 	return (false);
// }

// // $はkeyに不要なので一つポインタを進める
// // TODO:あとで消す quote対応
// char	*convert_env_var(t_exec_attr *ea, char *arg)
// {
// 	char	*key;
// 	t_list	*ret;
// 	char	*value;

// 	arg = ft_strtrim(arg, "\'");
// 	key = ++arg;
// 	ret = get_lst_by_key(ea->env_lst, key);
// 	if (ret == NULL)
// 		return (NULL);
// 	value = ft_kvsget_value(ret->content);
// 	return (value);
// }

// char	*concat_path_and_cmd(char *path, char *command)
// {
// 	char			*new_cmd;
// 	size_t			new_cmd_len;

// 	new_cmd_len = ft_strlen(path) + SLASH + ft_strlen(command) + NULL_CHAR;
// 	new_cmd = (char *)ft_calloc(sizeof(char), (new_cmd_len));
// 	ft_strlcat(new_cmd, path, new_cmd_len);
// 	ft_strlcat(new_cmd, "/", new_cmd_len);
// 	ft_strlcat(new_cmd, command, new_cmd_len);
// 	return (new_cmd);
// }

// /* Checking the owner's execute and read permissions. */
// bool	can_exec(char *cmd_path)
// {
// 	struct stat	stat_buf;

// 	if (stat(cmd_path, &stat_buf) == -1)
// 		exit(EXIT_FAILURE);
// 	if ((stat_buf.st_mode & S_IXUSR) != S_IXUSR)
// 		return (false);
// 	if ((stat_buf.st_mode & S_IRUSR) != S_IRUSR)
// 		return (false);
// 	return (true);
// }

// bool	should_break(t_exec_attr *ea, char *new_cmd, size_t cmd_i)
// {
// 	ea->is_unpermitted[cmd_i] = false;
// 	if (!can_exec(new_cmd))
// 	{
// 		ea->is_unpermitted[cmd_i] = true;
// 		free(new_cmd);
// 		return (true);
// 	}
// 	return (false);
// }

// bool	init_readdir(DIR **dirp, char ***path)
// {
// 	*dirp = opendir(**path);
// 	if (*dirp == NULL)
// 	{
// 		(*path)++;
// 		return (false);
// 	}
// 	return (true);
// }

char	*return_new_cmd(char *new_cmd, DIR *dirp)
{
	closedir(dirp);
	return (new_cmd);
}

/* Loop through PATH until other executables are found,
without error even if you don't have permissions */
char	*create_cmd_from_path(char *cmd, char **path, t_exec_attr *ea,
								size_t cmd_i)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*new_cmd;

	dirp = NULL;
	while (*path != NULL)
	{
		if (!init_readdir(&dirp, &path))
			continue ;
		dp = readdir(dirp);
		while (dp != NULL)
		{
			if (is_same_str(dp->d_name, cmd))
			{
				new_cmd = concat_path_and_cmd(*path, cmd);
				if (should_break(ea, new_cmd, cmd_i))
					break ;
				return (return_new_cmd(new_cmd, dirp));
			}
			dp = readdir(dirp);
		}
		closedir(dirp);
		path++;
	}
	return (NULL);
}

/* Replace ":" pointing to the current directory with "." */
char	*replace_colon_to_currentdir(char *env_path)
{
	char	*ret;
	char	*tmp;

	if (env_path[0] == ':')
	{
		ret = ft_strjoin(".", env_path);
		if (ret == NULL)
			exit(EXIT_FAILURE);
		free(env_path);
		return (ret);
	}
	ret = ft_replace_str(env_path, "::", ":.:");
	if (ret == NULL)
		exit(EXIT_FAILURE);
	if (env_path[ft_strlen(env_path) - 1] == ':')
	{
		tmp = ft_strjoin(ret, ".");
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		free(ret);
		ret = tmp;
	}
	free(env_path);
	return (ret);
}

char	*find_path(char *cmd_name, t_exec_attr *ea, size_t cmd_i)
{
	char			*env_path;
	char			**path;
	char			*new_cmd;
	t_list			*lst;

	lst = get_lst_by_key(ea->env_lst, "PATH");
	if (lst == NULL)
		return (NULL);
	env_path = ft_strdup(ft_kvsget_value(lst->content));
	if (env_path == NULL)
		return (NULL);
	env_path = replace_colon_to_currentdir(env_path);
	path = ft_split(env_path, ':');
	if (path == NULL)
		abort_minishell_with(MALLOC_ERROR, ea, path);
	new_cmd = create_cmd_from_path(cmd_name, path, ea, cmd_i);
	if (new_cmd == NULL)
	{
		free_char_dptr(path);
		free(env_path);
		return (NULL);
	}
	free_char_dptr(path);
	free(env_path);
	return (new_cmd);
}
