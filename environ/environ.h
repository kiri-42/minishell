/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:41:44 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 17:24:25 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define KEY 0
# define VALUE 1

# include <stdbool.h>

# include "libft.h"
# include "execute_struct.h"
# include "error_handle.h"
# include "self_cmd.h"

# define DQUOTE 2
# define NULL_CHAR 1

// env_lst.c
void		store_allenv_in_envlst(t_exec_attr *ea, char **environ);
bool		store_arg_in_env(t_exec_attr *ea, char *key, char *value);

// export_lst.c
char		*create_export_value(char *value);
void		store_allenv_in_export(t_exec_attr *ea, char **environ);
bool		store_arg_in_export(t_exec_attr *ea, char *key, char *value);

// kvs_utils.c
bool		is_lvalue_bigger_ascii(char *lvalue, char *rvalue);
bool		is_same_str(char *a, char *b);

// lst_utils.c
t_list		*get_list_by_min_ascii_key(t_list *lst);
void		del_env_lst_by_key(t_list *lst, char *key, t_exec_attr *ea);
void		del_export_lst_by_key(t_list *lst, char *key, t_exec_attr *ea);
t_list		*get_lst_by_key(t_list *lst, char *key);
void		sort_listkey_by_ascii(t_list *lst);

// lst_utils_2.c
bool		swap_lst_content(t_list *a, t_list *b);
bool		update_value(t_list *lst, char *key, char *new_v, t_exec_attr *ea);

#endif
