/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_lstpop_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:26:16 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:26:17 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_my_lstpop_front(t_list **lst)
{
	t_list	*top;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	top = *lst;
	*lst = (*lst)->next;
	top->next = NULL;
	return (top);
}
