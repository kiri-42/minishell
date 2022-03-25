/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:34:39 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:19:54 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handle.h"

void	free_exec_attr(t_exec_attr *ea)
{
	free_lst(ea->env_lst);
	free_lst(ea->export_lst);
	ft_lstclear(&ea->cmd_lst, &delete_pipe);
	free(ea->current_pwd);
	if (ea != NULL)
		free(ea);
}

void	free_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (lst != NULL)
	{
		free_all_kvs((t_kvs *)lst->content);
		lst = lst->next;
	}
	lst = tmp;
	while (lst != NULL)
	{
		free(lst);
		lst = lst->next;
	}
}

void	free_char_dptr(char **dptr)
{
	size_t	i;

	i = 0;
	if (dptr != NULL)
	{
		while (dptr[i] != NULL)
		{
			free(dptr[i]);
			i++;
		}
		free(dptr);
	}
}

void	free_all_kvs(t_kvs *kvs)
{
	if (kvs != NULL)
	{
		if (kvs->key != NULL)
			free(kvs->key);
		if (kvs->value != NULL)
			free(kvs->value);
		free(kvs);
	}
}
