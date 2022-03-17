/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:24:43 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:24:46 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstadd_back(t_list **lst, t_list *new_elm)
{
	t_list	*list;

	if (lst == NULL || new_elm == NULL)
		return (false);
	if (*lst == NULL)
		*lst = new_elm;
	else
	{
		list = ft_lstlast(*lst);
		list->next = new_elm;
	}
	return (true);
}
