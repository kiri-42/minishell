/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:15:12 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/15 16:14:00 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "sigaction.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void	write_heredocs(t_lexer *lexer, char *buf, char *delimiter)
{
	char	*filename;

	filename = ft_kvsget(lexer->heredocs, delimiter);
	if (filename == NULL)
		return ;
	write_tmpfile(filename, buf);
}

void	register_heredocs(t_lexer *lexer, char *delimiter)
{
	t_kvs	*kvs;
	char	*tmpfile;

	tmpfile = get_tmpfile_name(ft_itoa(ft_lstsize(lexer->io_here_delimiters)));
	create_tmpfile(tmpfile);
	kvs = ft_kvsnew(delimiter, tmpfile);
	free(tmpfile);
	ft_lstadd_back(&lexer->heredocs, ft_lstnew(kvs));
}
