NAME 	:= libcommand.a



SRCDIR 	:= ./src/
SRCNAME	:=	execute_builtin.c \
			execute_self.c \
			execute.c \
			redirect_process.c \
			redirect_process_2.c \
			init.c \
			create_cmd.c \
			create_cmd_2.c \
			create_cmd_3.c \
			convert_lst_to_argv.c \
			no_pipe_process.c \
			no_pipe_process_2.c \
			pipe_process.c \
			pipe_process_2.c \
			pipe_process_exec.c \
			free_pipe_attr.c \
			exec_attribute_utils.c \
			cmd_utils.c \
			execve_error.c \


SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))

OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
DEBUG	:= -g -fsanitize=address
INC		:= -I ../includes/
RM		:= rm -rf
LDFLAGS := -Llib/ft_printf -Llib/gnl -Llib/libft -Llib/ft_list
LIBS 	:= -lftprintf -lgnl -lft -llst

# LIBMEM_MGT			=	../libmem_mgt/libmem_mgt.a

HEADERS	:=	. \
			../ \
			./includes/ \
			../libft/ \
			../environ/ \
			../error_handle/ \
			../self_cmd/ \

INCLUDES	=	$(addprefix -I, $(HEADERS))

all:  $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) ${OBJS}

$(OBJSDIR)%.o : $(SRCDIR)%.c
	mkdir -p $(OBJSDIR)$(ENV_DIR)
	mkdir -p $(OBJSDIR)$(SELFCMD_DIR)
	${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJSDIR)

fclean: clean
	${RM} ${NAME}
re:	fclean all

debug:	CFLAGS += $(DEBUG)
debug:	re

.PHONY: all clean fclean re debug lib
