/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:48:47 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 15:50:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

bool	init_readdir(DIR **dirp, char ***path)
{
	*dirp = opendir(**path);
	if (*dirp == NULL)
	{
		(*path)++;
		return (false);
	}
	return (true);
}
