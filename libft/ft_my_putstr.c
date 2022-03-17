/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:25:14 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:25:17 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int64_t	ft_my_putstr(const char *str)
{
	if (str == NULL)
		return (ft_my_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}
