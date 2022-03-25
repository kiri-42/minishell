/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:34:39 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:20:11 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handle.h"

void	abort_minishell(char *msg, t_exec_attr *ea)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (ea != NULL)
		free_exec_attr(ea);
	exit(EXIT_FAILURE);
}

void	abort_minishell_with(char *msg, t_exec_attr *ea, char **split)
{
	if (split != NULL)
		free_char_dptr(split);
	perror(msg);
	if (ea != NULL)
		free_exec_attr(ea);
	exit(EXIT_FAILURE);
}
