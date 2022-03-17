/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:19:35 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:19:38 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	if (s == NULL || f == NULL)
		return (NULL);
	res = ft_strdup(s);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (res[i] != '\0')
	{
		res[i] = f(i, res[i]);
		i++;
	}
	return (res);
}
