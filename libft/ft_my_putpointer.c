/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_putpointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:25:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:25:39 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t	ft_my_putpointer(size_t n)
{
	int64_t	cnt;

	cnt = ft_my_putstr("0x");
	cnt += ft_my_putbase(n, "0123456789abcdef");
	return ((int64_t)cnt);
}
