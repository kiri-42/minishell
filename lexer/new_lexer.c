/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:23 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:24 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_lexer	*new_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexer == NULL)
		exit(EXIT_FAILURE);
	lexer->input = ft_strdup(input);
	if (lexer->input == NULL)
		exit(EXIT_FAILURE);
	lexer->position = 0;
	lexer->read_position = 0;
	lexer->ch = '\0';
	lexer->skip_whitespace = true;
	lexer->io_here_delimiters = NULL;
	lexer->heredocs = NULL;
	read_char(lexer);
	return (lexer);
}
