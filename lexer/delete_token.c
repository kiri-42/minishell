/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:15:26 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:15:27 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	delete_token(void *token)
{
	t_token	*tmp_token;

	tmp_token = (t_token *)token;
	free(tmp_token->literal);
	tmp_token->literal = NULL;
	free(tmp_token);
	tmp_token = NULL;
	return ;
}
