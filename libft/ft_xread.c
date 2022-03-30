/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_read.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:20:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/30 15:23:15 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_xread(int fd, void *buf, size_t count)
{
	ssize_t	ret;

	ret = read(fd, buf, count);
	if (ret == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
