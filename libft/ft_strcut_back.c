/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:21:17 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:27:34 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut_back(char *str, char c)
{
	char	*position;
	char	*tmp;
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	tmp = str;
	position = ft_strrchr(str, c);
	if (position == NULL)
		return (NULL);
	while (tmp++ != position)
		i++;
	return (ft_substr(str, 0, i));
}
