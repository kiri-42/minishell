/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:24:38 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:24:41 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_elm)
{
	if (lst == NULL || new_elm == NULL)
		return ;
	ft_lstlast(new_elm)->next = (*lst);
	(*lst) = new_elm;
}
