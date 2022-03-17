/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_metachar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:15:58 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:15:59 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdbool.h>

bool	is_metachar(const char c)
{
	const char	meta_chars[] = "|<>";

	return ((ft_strchr(meta_chars, c) != NULL) || ft_isspace(c));
}
