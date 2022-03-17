/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:53 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:54 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

void	delete_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	ft_lstclear(&lexer->io_here_delimiters, free);
	ft_lstclear(&lexer->heredocs, ft_kvsdelete);
	free(lexer);
	return ;
}

void	delete_lexer_without_heredocs(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	ft_lstclear(&lexer->io_here_delimiters, free);
	free(lexer);
	return ;
}
