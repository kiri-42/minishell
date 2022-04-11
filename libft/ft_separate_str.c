/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:44:15 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/11 22:44:47 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_separate_str(char *str, char *separator)
{
	char	**ret;
	char	*front_sep_ptr;
	size_t	separator_len;

	if (str == NULL || separator == NULL)
		return (NULL);
	front_sep_ptr = ft_strnstr(str, separator, ft_strlen(str));
	if (front_sep_ptr == NULL)
		return (NULL);
	ret = (char **)ft_xmalloc(sizeof(char *) * (2 + 1));
	separator_len = ft_strlen(separator);
	if (*(front_sep_ptr + separator_len) == '\0')
	{
		ret[0] = ft_substr(str, 0, front_sep_ptr - str);
		ret[1] = NULL;
		ret[2] = NULL;
		return (ret);
	}
	ret[0] = ft_substr(str, 0, front_sep_ptr - str);
	ret[1] = ft_strdup(front_sep_ptr + separator_len);
	ret[2] = NULL;
	return (ret);
}
