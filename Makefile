NAME		:=	minishell
CC			:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror
DEBUG		:= -g -fsanitize=address


LIBFT_DIR			=	libft
LEXER_DIR			=	lexer
PARSER_DIR			=	parser
REPL_DIR			=	repl
COMMAND_DIR			=	command
ENVIRON_DIR			=	environ
ERROR_HANDLE_DIR	=	error_handle
SELF_CMD_DIR		=	self_cmd
SIGNAL_DIR			=	signal


HEADERS		=	. \
				$(LIBFT_DIR) \
				$(LEXER_DIR) \
				$(PARSER_DIR) \
				$(REPL_DIR) \
				$(COMMAND_DIR)/includes \
				$(ENVIRON_DIR) \
				$(SIGNAL_DIR)/includes \

LIBFT				=	$(LIBFT_DIR)/libft.a
LIB_LEXER			=	$(LEXER_DIR)/liblexer.a
LIB_PARSER			=	$(PARSER_DIR)/libparser.a
LIB_REPL			=	$(REPL_DIR)/librepl.a
LIB_COMMAND 		=	$(COMMAND_DIR)/libcommand.a
LIB_ENVIRON			=	$(ENVIRON_DIR)/libenvion.a
LIB_ERROR_HANDLE	=	$(ERROR_HANDLE_DIR)/liberrorhandle.a
LIB_SELF_CMD		=	$(SELF_CMD_DIR)/libselfcmd.a
LIB_SIGNAL			=	$(SIGNAL_DIR)/libsignal.a

INCLUDES	=	$(addprefix -I, $(HEADERS))

UNAME	=	$(shell uname)

ifeq ($(UNAME),Darwin)
	HEADERS	+=	$(shell brew --prefix readline)/include
	RLFLAGS	=	-lreadline -lhistory -L$(shell brew --prefix readline)/lib
else
	RLFLAGS	=	-lreadline -lhistory
endif


RM			=	rm -f
RM_DIR		=	rm -rf

SRCS	= ./main.c
OBJS	= $(SRCS:.c=.o)


all: $(NAME)

RED			=	'\033[31m'
GREEN		=	'\033[32m'
YELLOW		=	'\033[33m'
RESET		=	'\033[0m'

$(NAME): $(LIBFT)  $(LIB_LEXER) $(LIB_REPL) $(LIB_COMMAND) $(LIB_ENVIRON) $(LIB_PARSER) $(LIB_ERROR_HANDLE) $(LIB_SELF_CMD) $(LIB_SIGNAL) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES)  -o $(NAME) $(OBJS) $(LIB_REPL) $(LIB_COMMAND) $(LIB_PARSER) $(LIB_ERROR_HANDLE) $(LIB_SELF_CMD) $(LIB_ENVIRON) $(LIB_LEXER) $(LIB_SIGNAL) $(LIBFT) $(RLFLAGS)
	@echo $(YELLOW)"@@@@@ $(NAME) compiling done @@@@@"$(RESET)

$(LIBFT): dummy
	@make -C $(LIBFT_DIR) bonus

$(LIB_LEXER): dummy
	@make -C $(LEXER_DIR)

$(LIB_PARSER): dummy
	@make -C $(PARSER_DIR)

$(LIB_REPL): dummy
	@make -C $(REPL_DIR)

$(LIB_COMMAND): dummy
	@make -C $(COMMAND_DIR)

$(LIB_ENVIRON): dummy
	@make -C $(ENVIRON_DIR)

$(LIB_ERROR_HANDLE): dummy
	@make -C $(ERROR_HANDLE_DIR)

$(LIB_SELF_CMD): dummy
	@make -C $(SELF_CMD_DIR)

$(LIB_SIGNAL): dummy
	@make -C $(SIGNAL_DIR)

.PHONY: dummy
dummy:

%.o: %.c
	@echo $(GREEN)"Creating: $@"$(RESET)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(LEXER_DIR) clean
	@make -C $(REPL_DIR) clean
	@make -C $(PARSER_DIR) clean
	@make -C $(COMMAND_DIR) clean
	@make -C $(ENVIRON_DIR) clean
	@make -C $(ERROR_HANDLE_DIR) clean
	@make -C $(SELF_CMD_DIR) clean
	@make -C $(SIGNAL_DIR) clean
	@$(RM) $(OBJS)
	@echo $(RED)"REMOVE OBJECT FILES $(OBJS)"$(RESET)

fclean:	clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LEXER_DIR) fclean
	@make -C $(REPL_DIR) fclean
	@make -C $(PARSER_DIR) fclean
	@make -C $(COMMAND_DIR) fclean
	@make -C $(ENVIRON_DIR) fclean
	@make -C $(ERROR_HANDLE_DIR) fclean
	@make -C $(SELF_CMD_DIR) fclean
	@make -C $(SIGNAL_DIR) fclean
	@$(RM) $(NAME)
	@echo $(RED)"REMOVE $(NAME)"$(RESET)

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus
