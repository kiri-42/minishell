/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:28 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*new_quote_token(t_lexer *lexer, t_tokentype type)
{
	char			*quote;
	t_token			*token;
	const size_t	pos = lexer->position;

	read_char(lexer);
	while (lexer->ch != type)
	{
		if (lexer->ch == '\0')
			if (!join_new_line(lexer))
				exit(EXIT_FAILURE);
		read_char(lexer);
	}
	quote = ft_substr(lexer->input, pos + 1, lexer->position - pos - 1);
	token = new_token(type, quote);
	free(quote);
	quote = NULL;
	lexer->skip_whitespace = false;
	return (token);
}
