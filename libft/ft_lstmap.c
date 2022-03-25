/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:23:55 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:21:34 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*now;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	now = ft_lstnew(f(lst->content));
	if (now == NULL)
		return (NULL);
	res = now;
	while (lst->next != NULL)
	{
		tmp = ft_lstnew(f(lst->next->content));
		if (tmp == NULL)
		{
			ft_lstclear(&res, del);
			return (res);
		}
		now->next = tmp;
		now = now->next;
		lst = lst->next;
	}
	return (res);
}
