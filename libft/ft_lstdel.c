/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:24:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:24:27 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstdel(t_list *lst, t_list *target)
{
	if (lst == NULL || target == NULL)
		return (false);
	while (lst->next != NULL)
	{
		if (lst->next == target)
		{
			lst->next = target->next;
			free(target);
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}
