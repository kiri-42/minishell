/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:40:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 16:07:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_file	*new_file(char *filename, bool is_double)
{
	t_file	*file;

	file = (t_file *)ft_calloc(sizeof(t_file), 1);
	if (file == NULL)
		exit(EXIT_FAILURE);
	if (filename != NULL)
	{
		file->filename = ft_strdup(filename);
		if (file->filename == NULL)
			exit(EXIT_FAILURE);
	}
	else
		file->filename = NULL;
	file->is_double = is_double;
	return (file);
}
