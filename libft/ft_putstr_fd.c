/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:26:37 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/09 16:07:31 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	ssize_t	ret;

	if (s == NULL)
		return ;
	ret = write(fd, s, ft_strlen(s));
	if (ret < 0)
		exit(EXIT_FAILURE);
}
