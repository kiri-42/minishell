/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:56:42 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 20:13:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	reset_stdfd(t_exec_attr *ea)
{
	ft_xdup2(ea->stdfd[0], STDIN_FILENO);
	ft_xdup2(ea->stdfd[1], STDOUT_FILENO);
	ft_xdup2(ea->stdfd[2], STDERR_FILENO);
}

bool	has_redirect_file(t_cmd *cmd)
{
	if (cmd->filenames_in != NULL || cmd->filenames_out != NULL)
		return (true);
	return (false);
}

void	redirect_dev_null(t_exec_attr *ea)
{
	int	fd;

	(void)ea;
	fd = open("/dev/null", O_WRONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	ft_xdup2(fd, STDOUT_FILENO);
	ft_xclose(fd);
}

void	change_fd(t_list *files, bool is_in)
{
	t_file	*f;
	size_t	i;
	t_list	*tmp;

	i = 0;
	tmp = files;
	while (tmp != NULL)
	{
		f = (t_file *)tmp->content;
		if (is_in)
			ft_xdup2(f->fd, STDIN_FILENO);
		else
			ft_xdup2(f->fd, STDOUT_FILENO);
		ft_xclose(f->fd);
		tmp = tmp->next;
		i++;
	}
}

void	redirect(t_cmd *cmd, t_exec_attr *ea)
{
	(void)ea;
	if (cmd->filenames_in != NULL)
		change_fd(cmd->filenames_in, true);
	if (cmd->filenames_out != NULL)
		change_fd(cmd->filenames_out, false);
}
