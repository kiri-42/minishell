/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmdv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:37:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/10 20:56:16 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	**make_cmdv(t_redirect_cmd *rc)
{
	char	**cmdv;
	char	*tmp_arg;
	size_t	cmdc;
	size_t	i;

	//TODO +1用のマクロを作る
	cmdc = ft_lstsize(rc->cmd->args) + 1;
	cmdv = (char **)malloc(sizeof(char) * (cmdc + 1));
	if (cmdv == NULL)
		printf("malloc error\n");
	cmdv[0] = ft_strdup(rc->cmd->cmd);
	if (cmdv[0] == NULL)
		printf("malloc error\n");
	i = 1;
	while (i < cmdc)
	{
		tmp_arg = rc->cmd->args->content;
		cmdv[i] = ft_strdup(tmp_arg);
		i++;
	}
	cmdv[i] = NULL;
	return (cmdv);
}
