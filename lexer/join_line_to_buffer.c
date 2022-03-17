/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_line_to_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:11 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	join_line_to_buffer(char **buffer, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*buffer, *line);
	free(*buffer);
	free(*line);
	*line = NULL;
	*buffer = tmp;
	tmp = ft_strjoin(*buffer, "\n");
	free(*buffer);
	*buffer = tmp;
}
