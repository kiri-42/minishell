/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:42:57 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/12 16:45:13 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>

typedef enum e_stdio
{
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2
}						t_stdio;

extern int	g_exit_status;

#endif
