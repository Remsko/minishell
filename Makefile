NAME = minishell
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I./incs
LIBFT = libft/libft.a

SRC_PATH = srcs/
SRC_NAME =	main.c \
			error.c \
			builtins/ft_echo.c \
			builtins/ft_exit.c \
			builtins/ft_cd.c \
			builtins/ft_unsetenv.c \
			builtins/ft_setenv.c \
			builtins/ft_env.c \
			execution/execute_cmdline.c \
			execution/execute_builtins.c \
			execution/execute_binaries.c \
			env/env_copy.c \
			env/env_search.c \
			env/env_change.c \
			env/env_add.c \
			env/env_rm.c \
			shell/shell_free.c \
			shell/shell_clear.c \
			shell/shell_singletone.c \
			display/display_prompt.c \
			display/display_path.c \
			display/display_git.c \
			expansion/expansion_sandr.c \

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CPPFLAGS = -Iincs -Ilibft
LDFLAGS = -Llibft
LDLIBS = -lft

all: $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)builtins
	mkdir -p $(OBJ_PATH)execution
	mkdir -p $(OBJ_PATH)env
	mkdir -p $(OBJ_PATH)shell
	mkdir -p $(OBJ_PATH)display
	mkdir -p $(OBJ_PATH)expansion

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS)  -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	make clean -C libft
	$(RM) $(OBJ)
	$(RM) $(OBJ_PATH)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re