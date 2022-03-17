/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvsget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:24:56 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:24:57 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_kvsget(t_list *lst, char *key)
{
	t_list	*ret;

	ret = lst;
	while (ret != NULL)
	{
		if (ft_streq(ft_kvsget_key(ret->content), key))
			return (((t_kvs *)ret->content)->value);
		ret = ret->next;
	}
	return (NULL);
}
