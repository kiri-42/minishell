/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lst_to_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:12:55 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/23 16:22:43 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	**convert_lst_to_vector(t_list *args)
{
	char	**cmdv;
	size_t	cmdc;
	size_t	i;
	t_list	*current_arg;

	cmdc = ft_lstsize(args);
	cmdv = (char **)ft_xmalloc(sizeof(char *) * (cmdc + NULL_CHAR));
	i = 0;
	current_arg = args;
	while (current_arg != NULL)
	{
		cmdv[i] = ft_strdup(current_arg->content);
		i++;
		current_arg = current_arg->next;
	}
	cmdv[i] = NULL;
	return (cmdv);
}
