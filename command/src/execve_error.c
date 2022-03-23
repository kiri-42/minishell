/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:12:32 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/23 16:17:35 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/* Checking the owner's execute
and read permissions. */
static bool	can_exit(char *cmd_path)
{
	struct stat	stat_buf;

	if (stat(cmd_path, &stat_buf) == -1)
		exit(EXIT_FAILURE);
	if ((stat_buf.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((stat_buf.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

/* Even if errno is ENOEXEC,
change to EACCES if there is no execution authority */
void	execve_error(int cp_errno, char *cmd_path)
{
	int	exit_status;

	if (cp_errno == ENOENT)
		exit_status = 127;
	else
		exit_status = 126;
	if (cp_errno == ENOEXEC && !can_exit(cmd_path))
		cp_errno = EACCES;
	else if (cp_errno == ENOEXEC)
		exit(EXIT_SUCCESS);
	ft_put_cmd_error(cmd_path, strerror(cp_errno));
	exit(exit_status);
}
