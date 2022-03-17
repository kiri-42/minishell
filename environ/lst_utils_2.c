/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/17 23:41:30 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

bool	update_value(t_list *lst, char *key, char *new_v, t_exec_attr *ea)
{
	t_list	*target;
	char	*tmp;

	if (new_v == NULL)
		// もしnewがnullだったら値は更新しない。
		return (true);
	target = get_lst_by_key(lst, key);
	if (target == NULL)
	{
		// keyがなかったら新規作成する
		if (!ft_lstadd_back(&lst, \
			ft_lstnew(ft_kvsnew(key, new_v))))
			return (false);
		return (true);
	}
	tmp = ft_strdup(new_v);
	if (tmp == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	ft_kvsreplace_value(target->content, tmp);
	return (true);
}
