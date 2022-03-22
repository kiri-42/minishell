/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:02:16 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/22 16:10:56 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

/* If the path is ".." exists, the previous path is deleted.
except for the first absolute path. */
char
	**get_new_split(long long new_split_len, char **split, size_t *new_str_len)
{
	char	**new_split;
	size_t	i;
	size_t	j;

	new_split = (char **)ft_xmalloc(sizeof(char *) * new_split_len);
	i = 0;
	j = 0;
	while (split[i] != NULL)
	{
		if (search_dots(&i, &j, new_split, split))
			continue ;
		new_split[j] = ft_strjoin("/", split[i]);
		*new_str_len += ft_strlen(new_split[j]);
		j++;
		i++;
	}
	new_split[j] = NULL;
	return (new_split);
}

char	*get_new_path(char **new_split, size_t new_str_len)
{
	size_t	i;
	char	*new_path;

	new_path = (char *)ft_calloc(sizeof(char), new_str_len + 1);
	i = 0;
	while (new_split[i] != NULL)
	{
		ft_strlcat(new_path, new_split[i], new_str_len + 1);
		i++;
	}
	return (new_path);
}

char	*remove_relative(char *path)
{
	char		**split;
	char		**new_split;
	char		*new_path;
	size_t		new_str_len;
	long long	new_split_len;

	new_str_len = 0;
	split = ft_split(path, '/');
	if (!set_new_split_len(split, &new_split_len))
		return (ft_strdup("/"));
	new_split = get_new_split(new_split_len, split, &new_str_len);
	new_path = get_new_path(new_split, new_str_len);
	if (is_end_of_slash(new_path))
		path = create_str_removed_end(new_path);
	free_char_dptr(split);
	free_char_dptr(new_split);
	return (new_path);
}

char	*create_str_removed_end(char *path)
{
	size_t	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	path[i - 1] = '\0';
	return (ft_strdup(path));
}
