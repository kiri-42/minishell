/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:48:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 15:55:09 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/* Since there is no readline, the environment variable of the original one
is called if $ is put in the argument. */
/* Respond to be readable with QUOTE on. arg++ */
bool	is_dollar(char *arg)
{
	if (*arg == '$')
		return (true);
	return (false);
}

/* Advance one pointer since $ is not needed for key */
char	*convert_env_var(t_exec_attr *ea, char *arg)
{
	char	*key;
	t_list	*ret;
	char	*value;

	arg = ft_strtrim(arg, "\'");
	key = ++arg;
	ret = get_lst_by_key(ea->env_lst, key);
	if (ret == NULL)
		return (NULL);
	value = ft_kvsget_value(ret->content);
	return (value);
}

char	*concat_path_and_cmd(char *path, char *command)
{
	char			*new_cmd;
	size_t			new_cmd_len;

	new_cmd_len = ft_strlen(path) + SLASH + ft_strlen(command) + NULL_CHAR;
	new_cmd = (char *)ft_calloc(sizeof(char), (new_cmd_len));
	ft_strlcat(new_cmd, path, new_cmd_len);
	ft_strlcat(new_cmd, "/", new_cmd_len);
	ft_strlcat(new_cmd, command, new_cmd_len);
	return (new_cmd);
}

/* Checking the owner's execute and read permissions. */
bool	can_exec(char *cmd_path)
{
	struct stat	stat_buf;

	if (stat(cmd_path, &stat_buf) == -1)
		exit(EXIT_FAILURE);
	if ((stat_buf.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((stat_buf.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

bool	should_break(t_exec_attr *ea, char *new_cmd, size_t cmd_i)
{
	ea->is_unpermitted[cmd_i] = false;
	if (!can_exec(new_cmd))
	{
		ea->is_unpermitted[cmd_i] = true;
		free(new_cmd);
		return (true);
	}
	return (false);
}
