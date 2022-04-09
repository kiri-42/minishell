/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:25:14 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/09 16:08:23 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int64_t	ft_my_putstr(const char *str)
{
	ssize_t	ret;

	if (str == NULL)
		return (ft_my_putstr("(null)"));
	ret = write(1, str, ft_strlen(str));
	if (ret < 0)
		exit(EXIT_FAILURE);
	return (ret);
}
