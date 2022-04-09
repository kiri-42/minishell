/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_putchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:25:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/09 16:06:11 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int64_t	ft_my_putchar(char c)
{
	ssize_t	ret;

	ret = write(1, &c, 1);
	if (ret < 0)
		exit(EXIT_FAILURE);
	return (ret);
}
