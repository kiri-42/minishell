/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:00:06 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/14 16:14:50 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

bool	is_valid_path(char *pwd)
{
	size_t	i;
	
	if (!pwd)
		return (false);
	i = 0;
	while(pwd[i])
	{
		if (pwd[i] != '.' || pwd[i] != '/')
			return (true);
		i++;
	}
	return (false);
}
