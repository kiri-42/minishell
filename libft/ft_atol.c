/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:23:29 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/08 16:27:03 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

static void	read_sign(int *sign, size_t *i, char c)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		(*i)++;
	}
}

bool	ft_atol(const char *nptr, long *num)
{
	size_t		i;
	int			sign;

	*num = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	read_sign(&sign, &i, nptr[i]);
	while ((nptr[i] == '0'))
		i++;
	if (nptr[i] == '\0')
		return (true);
	while (ft_isdigit(nptr[i]))
	{
		if (sign == 1 && *num > (LONG_MAX - (nptr[i] - '0')) / 10)
			return (false);
		else if (sign == -1 && (-1 * *num) < (LONG_MIN + (nptr[i] - '0')) / 10)
			return (false);
		*num = *num * 10 + (nptr[i] - '0');
		i++;
	}
	*num *= sign;
	return (true);
}
