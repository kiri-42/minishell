/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:50 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 17:20:44 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

void	sort_listkey_by_ascii(t_list *lst)
{
	t_list	*min;

	if (lst == NULL)
		return ;
	while (lst->next != NULL)
	{
		min = get_list_by_min_ascii_key(lst);
		swap_lst_content(lst, min);
		lst = lst->next;
	}
}

t_list	*get_lst_by_key(t_list *lst, char *key)
{
	t_list	*ret;

	ret = lst;
	while (ret != NULL)
	{
		if (is_same_str(ft_kvsget_key(ret->content), key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_list	*get_list_by_min_ascii_key(t_list *lst)
{
	t_list	*tmp;
	char	*min_key;
	char	*next_key;

	tmp = lst;
	while (lst->next != NULL)
	{
		min_key = ft_kvsget_key(tmp->content);
		next_key = ft_kvsget_key(lst->next->content);
		if (is_lvalue_bigger_ascii(min_key, next_key))
			tmp = lst->next;
		lst = lst->next;
	}
	return (tmp);
}

void	del_env_lst_by_key(t_list *lst, char *key, t_exec_attr *ea)
{
	t_list	*target;

	target = get_lst_by_key(lst, key);
	if (target == NULL)
		return ;
	ft_kvsdelete(target->content);
	if (lst == target)
	{
		ea->env_lst = target->next;
		free(target);
		return ;
	}
	ft_lstdel(lst, target);
}

void	del_export_lst_by_key(t_list *lst, char *key, t_exec_attr *ea)
{
	t_list	*target;

	target = get_lst_by_key(lst, key);
	if (target == NULL)
		return ;
	ft_kvsdelete(target->content);
	if (lst == target)
	{
		ea->export_lst = target->next;
		free(target);
		return ;
	}
	ft_lstdel(lst, target);
}
