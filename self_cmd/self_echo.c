/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:32:17 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 15:59:04 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

static int	get_n_index(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr("n", str[i]) == NULL)
			break ;
		i++;
	}
	return (i);
}

static bool	search_n_opt(t_list **args)
{
	int		i;
	char	*str;
	bool	ret;

	ret = false;
	while (*args != NULL)
	{
		str = (*args)->content;
		if (str == NULL || str[0] != '-')
			break ;
		i = get_n_index(str);
		if (str[1] == '\0' || str[i] != '\0')
			break ;
		i = 1;
		while (str[i] != '\0')
		{
			if (str[i] == 'n')
				ret = true;
			i++;
		}
		*args = (*args)->next;
	}
	return (ret);
}

static void	print_content(t_list **args)
{
	char	*str;

	while (*args != NULL)
	{
		str = (*args)->content;
		if (str == NULL)
			break ;
		*args = (*args)->next;
		ft_putstr_fd(str, STDOUT_FILENO);
		if (*args != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	exec_self_echo(t_cmd *cmd, t_exec_attr *ea)
{
	t_list	*args;
	bool	display_return ;

	args = cmd->args->next;
	(void)ea;
	display_return = search_n_opt(&args);
	print_content(&args);
	if (!display_return)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
