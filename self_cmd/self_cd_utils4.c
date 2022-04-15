/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:00:06 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/15 15:57:09 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

bool	is_only_dot(char *pwd)
{	
	if (!pwd)
		return (false);
	if (is_same_str(pwd, ".") || is_same_str(pwd, "./"))
		return (true);
	return (false);
}
