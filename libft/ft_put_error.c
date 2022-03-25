/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:25:07 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:23:39 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_put_error(char *message)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

void	ft_put_cmd_error(char *cmd, char *message)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

void	ft_put_arg_error(char *cmd, char *arg, char *message)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}
