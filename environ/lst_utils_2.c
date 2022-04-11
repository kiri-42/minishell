/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/11 16:47:52 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

// If new is null, the value is not updated.
// If key is not found, create a new one.
bool	update_value(t_list *lst, char *key, char *new_v)
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
	ft_kvsreplace_value(target->content, tmp);
	return (true);
}

static char	*make_new_v(void *content, char *append_v)
{
	t_kvs	*k;

	k = (t_kvs *)content;
	return (ft_strjoin(k->value, append_v));
}

bool	append_value(t_list *lst, char *key, char *append_v)
{
	t_list	*target;
	char	*new_v;

	if (append_v == NULL)
		return (true);
	target = get_lst_by_key(lst, key);
	if (target == NULL)
	{
		if (!ft_lstadd_back(&lst, \
			ft_lstnew(ft_kvsnew(key, append_v))))
			return (false);
		return (true);
	}
	new_v = make_new_v(target->content, append_v);
	ft_kvsreplace_value(target->content, new_v);
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
