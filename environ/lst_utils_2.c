/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 17:26:55 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

// If new is null, the value is not updated.
// If key is not found, create a new one.
bool	update_value(t_list *lst, char *key, char *new_v, t_exec_attr *ea)
{
	t_list	*target;
	char	*tmp;

	if (new_v == NULL)
		return (true);
	target = get_lst_by_key(lst, key);
	if (target == NULL)
	{
		if (!ft_lstadd_back(&lst, \
			ft_lstnew(ft_kvsnew(key, new_v))))
			return (false);
		return (true);
	}
	tmp = ft_strdup(new_v);
	if (tmp == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	ft_kvsreplace_value(target->content, tmp);
	return (true);
}

bool	swap_lst_content(t_list *a, t_list *b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return (false);
	if (a->content == b->content)
	{
		return (true);
	}
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (true);
}
