/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_new_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:08 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:09 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "lexer.h"
#include "libft.h"
#include <readline/readline.h>
#include <stdbool.h>

bool	join_new_line(t_lexer *lexer)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(lexer->input, "\n");
	free(lexer->input);
	lexer->input = tmp;
	line = readline("> ");
	if (line == NULL)
		return (false);
	tmp = ft_strjoin(lexer->input, line);
	free(lexer->input);
	free(line);
	lexer->input = tmp;
	return (true);
}
