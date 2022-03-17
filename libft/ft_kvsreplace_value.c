/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvsreplace_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:24:49 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:24:54 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_kvsreplace_value(void *content, char *new_value)
{
	t_kvs	*k;
	char	*tmp;

	k = (t_kvs *)content;
	tmp = k->value;
	k->value = new_value;
	free(tmp);
}
