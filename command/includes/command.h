/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:13:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/28 15:25:02 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <dirent.h>

# include "libft.h"
# include "color.h"
# include "execute_struct.h"
# include "environ.h"
# include "self_cmd.h"
# include "error_handle.h"
# include "common.h"

# define MY_COMMAND_NUM 4
# define CMD_NAME 0
# define CMD_ARG 1
# define EQUAL 1
# define LF 1
# define PIPE_IN 0
# define PIPE_OUT 1
# define SLASH 1
# define IN 0
# define OUT 1
# define NO_PIPE 0
# define PIPE 1

// execute.c
void		execute_cmd(t_exec_attr *ea);
void		print_cmdv(char **cmdv);

// execute_self.c
bool		is_self_cmd(char *cmd);
void		execute_self_cmd(t_cmd	*c, t_exec_attr *ea, bool is_pipe);
void		create_cmd_from_arg(int argc, const char *argv[], t_exec_attr *ea);
void		exec_in_child_process(t_exec_attr *ea);
bool		exec_in_main_process(t_exec_attr *ea);

// execute_builtin.c
bool		is_not_exec_path(const char *command);
char		**convert_envlst_to_array(t_exec_attr *ea);
char		*create_environ_line(char *key, char *value, bool is_end);

// create_cmd.c
bool		is_dollar(char *arg);
char		*convert_env_var(t_exec_attr *ea, char *arg);
char		*concat_path_and_cmd(char *path, char *command);
void		create_cmd_from_arg(int argc, const char **argv, t_exec_attr *ea);
char		*find_path(char *cmd_name, t_exec_attr *ea, size_t cmd_i);

// create_cmd_2.c
bool		is_dollar(char *arg);
char		*convert_env_var(t_exec_attr *ea, char *arg);
char		*concat_path_and_cmd(char *path, char *command);
bool		can_exec(char *cmd_path);
bool		should_break(t_exec_attr *ea, char *new_cmd, size_t cmd_i);

// create_cmd_3.c
bool		init_readdir(DIR **dirp, char ***path);

// init.c
void		init(t_exec_attr **ea);
void		init_new(t_exec_attr **ea);

// convert_lst_to_argv.c
char		**convert_lst_to_vector(t_list *args);

// no_pipe_process.c
void		no_pipe_process(t_exec_attr *ea);
void		execute_ext_cmd(t_cmd *c, t_exec_attr *ea);
bool		is_path(char *cmd);

// no_pipe_process_2.c
bool		is_path(char *cmd);
void		print_error_and_set_es(char *cmd, int exits, char *err);
bool		check_redirect_file(t_cmd *c, t_exec_attr *ea);

// pipe_process.c
void		pipe_process(t_exec_attr *ea, int pipe_count);

// pipe_process_2.c
void		print_error_and_exit(char *cmd, int exits, char *err);
void		make_pipe(t_pipe_attr *pa);

// pipe_process_exec.c
void		exec_cmd(t_exec_attr *ea, t_pipe_attr *pa);

// free_pipe_attr.c
void		free_pipe_attr(t_pipe_attr *pa);

// cmd_utils.c
char		*get_filename(t_cmd *c, int io);
void		exec_error(int cp_errno, char *cmd_path);
bool		is_dir(char *cmd_path);
bool		*malloc_is_unpermitted(size_t size);

// execve_error.c
void		execve_error(int cp_errno, char *cmd_path);

// exec_attribute_utils.c
t_cmd		*get_cmd(t_exec_attr *ea);
char		*get_cmd_name(t_list *cmd);
char		*get_argv_one(t_cmd *cmd);

// redirect_process.c
void		redirect_dev_null(t_exec_attr *ea);
bool		open_files(t_cmd *cmd, t_exec_attr *ea);
bool		open_files_in_pipe(t_cmd *cmd, t_exec_attr *ea);
bool		open_files_in(t_cmd *cmd);
bool		open_files_out(t_cmd *cmd);

// redirect_process_2.c
void		reset_stdfd(t_exec_attr *ea);
bool		has_redirect_file(t_cmd *cmd);
void		redirect_dev_null(t_exec_attr *ea);
void		change_fd(t_list *files, bool is_in);
void		redirect(t_cmd *cmd, t_exec_attr *ea);

// redirect_process_3.c
bool		init_readdir(DIR **dirp, char ***path);

#endif
