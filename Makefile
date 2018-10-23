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
			execution/execute_cmdline.c \
			execution/execute_builtins.c \
			execution/execute_binaries.c \
			env/env_copy.c \
			env/env_search.c \
			shell/shell_free.c \
			shell/shell_clear.c \
			shell/shell_singletone.c \

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
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/execution
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/shell

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