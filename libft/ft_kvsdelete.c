/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvsdelete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:22:31 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:22:32 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_kvsdelete(void *elm)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)elm;
	free(kvs->key);
	kvs->key = NULL;
	free(kvs->value);
	kvs->value = NULL;
	free(kvs);
	kvs = NULL;
}
