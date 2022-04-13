/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:40:06 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 16:07:09 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_file(void *file_ptr)
{
	t_file	*file;

	file = (t_file *)file_ptr;
	free(file->filename);
	file->filename = NULL;
	free(file);
}
