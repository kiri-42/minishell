/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:11:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 16:18:26 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

bool	open_files_out(t_cmd *cmd)
{
	t_list	*current_filename;
	t_file	*f;
	int		fd;

	current_filename = cmd->filenames_out;
	while (current_filename != NULL)
	{
		f = (t_file *)current_filename->content;
		if (f->is_double)
			fd = open(f->filename, \
						O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(f->filename, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror(f->filename);
			g_exit_status = EXIT_FAILURE;
			return (false);
		}
		f->fd = fd;
		current_filename = current_filename->next;
	}
	return (true);
}

bool	open_files_in(t_cmd *cmd)
{
	t_list	*current_filename;
	t_file	*f;
	int		fd;

	current_filename = cmd->filenames_in;
	while (current_filename != NULL)
	{
		f = (t_file *)current_filename->content;
		fd = open(f->filename, O_RDONLY);
		if (fd == -1)
		{
			perror(f->filename);
			g_exit_status = EXIT_FAILURE;
			return (false);
		}
		f->fd = fd;
		current_filename = current_filename->next;
	}
	return (true);
}

bool	open_files(t_cmd *cmd, t_exec_attr *ea)
{
	(void)ea;
	if (!open_files_in(cmd))
		return (false);
	if (!open_files_out(cmd))
		return (false);
	return (true);
}

bool	open_files_in_pipe(t_cmd *cmd, t_exec_attr *ea)
{
	(void)ea;
	if (!open_files_in(cmd))
		exit(EXIT_FAILURE);
	if (!open_files_out(cmd))
		exit(EXIT_FAILURE);
	return (true);
}
