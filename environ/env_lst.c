/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:55 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/11 22:55:47 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

void	store_allenv_in_envlst(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_list		*env_lst;
	char		*tmp;

	i = 0;
	env_lst = NULL;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split[VALUE] == NULL)
		{
			tmp = ft_strdup("");
			ft_lstadd_back(&env_lst, ft_lstnew(ft_kvsnew(split[KEY], tmp)));
			free(tmp);
		}
		else
		{
			ft_lstadd_back(&env_lst, \
			ft_lstnew(ft_kvsnew(split[KEY], split[VALUE])));
		}
		i++;
		free_char_dptr(split);
	}
	ea->env_lst = env_lst;
}

bool	store_arg_in_env(t_exec_attr *ea, char *key, char *value, \
							int export_type)
{
	t_list	*target;

	target = get_lst_by_key(ea->env_lst, key);
	if (target != NULL)
	{
		if (export_type == EXPORT_APPEND)
		{
			if (!append_value(ea->env_lst, key, value))
				return (false);
		}
		else if (export_type == EXPORT_NEW)
		{
			if (!update_value(ea->env_lst, key, value))
				return (false);
		}
	}
	else
	{
		ft_lstadd_back(&ea->env_lst, \
			ft_lstnew(ft_kvsnew(key, value)));
	}
	return (true);
}
