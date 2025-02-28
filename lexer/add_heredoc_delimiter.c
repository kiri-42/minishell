/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc_delimiter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:37 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:38 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

size_t	process_in_quote_heredoc(t_lexer *lexer, size_t pos_tail, char quote)
{
	pos_tail++;
	while (lexer->input[pos_tail] != quote)
	{
		if (lexer->input[pos_tail] == '\0')
		{
			printf("error: not quoted heredoc delimiter\n");
			exit(EXIT_FAILURE);
		}
		pos_tail++;
	}
	return (pos_tail);
}

void	add_heredoc_delimiter(t_lexer *lexer)
{
	char	*delimiter;
	size_t	pos;
	size_t	pos_tail;

	read_char(lexer);
	if (lexer->skip_whitespace)
		skip_whitespace(lexer);
	pos = lexer->position;
	pos_tail = pos;
	while (!is_metachar(lexer->input[pos_tail])
		&& lexer->input[pos_tail] != '\0')
	{
		if (lexer->input[pos_tail] == '"' || lexer->input[pos_tail] == '\'')
		{
			pos_tail = process_in_quote_heredoc(lexer, pos_tail,
					lexer->input[pos_tail]);
		}
		pos_tail++;
	}
	delimiter = ft_substr(lexer->input, pos, pos_tail - pos);
	ft_lstadd_back(&lexer->io_here_delimiters, ft_lstnew(delimiter));
}
