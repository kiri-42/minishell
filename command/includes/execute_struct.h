/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:26 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/13 20:53:16 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_STRUCT_H
# define EXECUTE_STRUCT_H

# include "libft.h"
# include "parser/parser.h"

typedef void(*	t_content_f)(void *);

typedef struct s_exec_attr
{
	t_list	*cmd_lst;
	t_list	*env_lst;
	t_list	*export_lst;
	int		stdfd[3];
	char	*current_pwd;
	bool	*is_unpermitted;
	bool	invalid_path;
}	t_exec_attr;

typedef struct s_env
{
	t_list		*env_lst;
	t_list		*export_lst;
}	t_env;

typedef struct s_pipe_attr
{
	int		cmd_i;
	t_cmd	*current_cmd;
	int		**pipe_fd;
	int		pipe_count;
	int		*cpid_array;
}	t_pipe_attr;

#endif
