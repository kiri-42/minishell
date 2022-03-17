/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:02 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:03 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_valid_tokens(t_list *token_list)
{
	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type == TOKEN_ILLEGAL)
			return (false);
		token_list = token_list->next;
	}
	return (true);
}
