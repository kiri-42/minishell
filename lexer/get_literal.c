/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_literal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:15:55 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:15:57 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "lexer.h"
#include "libft.h"

char	*get_literal(t_token *token)
{
	if (is_word_token(token->type))
		return (ft_strdup(token->literal));
	else
		exit(EXIT_FAILURE);
	return (NULL);
}
