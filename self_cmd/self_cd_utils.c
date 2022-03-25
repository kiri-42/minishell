/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:00:06 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:15:05 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

char	*get_pwd(t_list *pwdlst, t_exec_attr *ea)
{
	char	*pwd;

	if (pwdlst == NULL)
		pwd = ft_strdup("");
	else
	{
		if (ft_strlen(ft_kvsget_value(pwdlst->content)) == 0)
			pwd = ft_strdup("");
		else
			pwd = ft_strdup(ea->current_pwd);
	}
	return (pwd);
}

/* If PWD is lost in unset, or in the case
where the value of "export PWD= PWD" is overwritten
to an empty string, pwd will be an empty string. */
void	update_all_environ(char *new_pwd, t_exec_attr *ea)
{
	char	*export_new_pwd;
	char	*export_pwd;
	char	*pwd;
	t_list	*pwdlst;

	pwdlst = get_lst_by_key(ea->env_lst, "PWD");
	pwd = get_pwd(pwdlst, ea);
	free(ea->current_pwd);
	ea->current_pwd = ft_strdup(new_pwd);
	export_pwd = create_export_value(pwd);
	if (pwdlst != NULL)
	{
		export_new_pwd = create_export_value(new_pwd);
		update_value(ea->env_lst, "PWD", new_pwd, ea);
		update_value(ea->export_lst, "PWD", export_new_pwd, ea);
		free(export_new_pwd);
	}
	update_value(ea->env_lst, "OLDPWD", pwd, ea);
	update_value(ea->export_lst, "OLDPWD", export_pwd, ea);
	free(pwd);
	free(export_pwd);
}

// virtual pathの場合、最後に"/"が入る場合があるため、新しい"/"とかぶってしまう。
// なので、/を余分に付け加えないようにする
char	*create_new_pwd(char *pwd, char *path)
{
	char	*new_value;
	size_t	new_value_len;
	size_t	path_len;
	size_t	pwd_len;

	pwd_len = ft_strlen(pwd);
	path_len = ft_strlen(path);
	if (pwd[pwd_len - 1] == '/')
		new_value_len = (pwd_len + path_len + NULL_CHAR);
	else
		new_value_len = (pwd_len + SLASH + path_len + NULL_CHAR);
	new_value = (char *)ft_calloc(sizeof(char), new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, pwd, new_value_len);
	if (pwd[pwd_len - 1] != '/')
		ft_strlcat(new_value, "/", new_value_len);
	ft_strlcat(new_value, path, new_value_len);
	return (new_value);
}

bool	is_symlink(char *path, t_exec_attr *ea)
{
	struct stat	buf;
	char		*pwd;
	char		*new_pwd;

	pwd = ea->current_pwd;
	new_pwd = create_new_pwd(pwd, path);
	lstat(new_pwd, &buf);
	free(new_pwd);
	return (S_ISLNK(buf.st_mode));
}

/* Not applicable for slash only */
bool	is_end_of_slash(char *path)
{
	size_t	i;

	i = 0;
	if (ft_strlen(path) == 1)
		return (false);
	while (path[i] != '\0')
		i++;
	if (path[i - 1] == '/')
		return (true);
	return (false);
}
