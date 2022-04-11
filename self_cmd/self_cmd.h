/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:32:03 by tkirihar          #+#    #+#             */
/*   Updated: 2022/04/11 17:21:35 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELF_CMD_H
# define SELF_CMD_H

# include <errno.h>
# include <limits.h>
# include <sys/stat.h>

# include "libft.h"
# include "error_handle.h"
# include "environ.h"
# include "execute_struct.h"
# include "common.h"
# include "command.h"

typedef enum e_export_type
{
	EXPORT_ERROR = -1,
	EXPORT_NOKEY,
	EXPORT_APPEND,
	EXPORT_NEW,
}	t_export_type;

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"
# define CMD_ARG 1
# define SLASH 1

// self_pwd.c
int			exec_self_pwd(t_cmd *cmd, t_exec_attr *ea);

// self_cd.c
int			exec_self_cd(t_cmd *cmd, t_exec_attr *ea);

// self_cd_utils.c
char		*get_pwd(t_list *pwdlst, t_exec_attr *ea);
void		update_all_environ(char *new_pwd, t_exec_attr *ea);
char		*create_new_pwd(char *pwd, char *path);
bool		is_symlink(char *path, t_exec_attr *ea);
bool		is_end_of_slash(char *path);

// self_cd_utils2.c
char		*x_getcwd(t_exec_attr *ea);
bool		is_current_dir_exist(t_exec_attr *ea);
void		create_virtual_path(char *path, t_exec_attr *ea);
bool		set_new_split_len(char **split, long long *new_split_len);
bool		search_dots(size_t *i, size_t *j, char **new_split, char **split);

// self_cd_utils3.c
char		*remove_relative(char *path);
char		*create_str_removed_end(char *path);

// self_echo.c
int			exec_self_echo(t_cmd *cmd, t_exec_attr *ea);

// self_exit.c
int			exec_self_exit(t_cmd *cmd, bool is_pipe);

// self_env.c
int			exec_self_env(t_cmd *cmd, t_exec_attr *ea);
void		print_all_env_lst(t_exec_attr *ea);
void		print_env_kvs(void *content);

// self_unset.c
int			exec_self_unset(t_cmd *cmd, t_exec_attr *ea);

// self_export.c
int			exec_self_export(t_cmd *cmd, t_exec_attr *ea);
void		store_arg_only_export(t_exec_attr *ea, char *key);
int			check_export_arg(char **arg);
void		export_with_args(t_cmd *cmd, t_exec_attr *ea, bool *exit_stat);
bool		addlst_sort_by_ascii(t_list **export_lst, char **arg);

// self_export_utils.c
void		print_export_kvs(void *content);
void		sort_listkey_by_ascii(t_list *export_lst);
void		print_all_export_lst(t_exec_attr *ea);
bool		is_sharp(char *arg);
int			check_export_arg(char **arg);
void		store_null_env(t_exec_attr *ea, char *arg, bool *exit_stat);

// self_cmd_utils.c
bool		is_invalid_name(char *name);
void		print_error_msg_with_var(char *cmd_name, char *var);
void		print_error(char *cmd, char *input);
bool		has_caps(char *path);

#endif
