/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lexer_product.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:16:50 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:16:51 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	delete_lexer_product(t_lexer_product *lexer_product)
{
	ft_lstclear(&lexer_product->token_list, delete_token);
	ft_lstclear(&lexer_product->heredocs, ft_kvsdelete);
	free(lexer_product);
}
