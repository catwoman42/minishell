NAME := minishell

SRCS_PATH := srcs
OBJS_PATH := objs

SRCS_FILES = 	main.c						\
				init.c						\
				my_execve.c					\
				my_export.c					\
				my_unset.c					\
				builtin_launcher.c			\
				builtin_echo.c				\
				builtin_cd.c				\
				builtin_pwd.c 				\
				parsing_main.c				\
				libft_utils_1.c				\
				libft_utils_2.c				\
				libft_utils_3.c				\
				libft_utils_4.c				\
				libft_utils_5.c				\
				env_utils.c					\
				free_utils.c				\
				exit.c						\
				parsing_arrays_utils.c		\
				parsing_quotes.c			\
				parsing_env_vars.c			\
				parsing_is_char.c			\
				parsing_str_utils.c			\
				parsing_join_quotes.c		\
				parsing_splits.c			\
				redirect.c					\
				get_next_line.c				\
				parsing_output.c



SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS_FILES := $(SRCS_FILES:%.c=%.o)
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_FILES))

CC := gcc
CFLAGS := -Wextra -Wall -g

LREADLINE := -lreadline

DEPS = ./includes/minishell.h

all:$(OBJS_PATH) $(NAME)

$(NAME):$(OBJS) $(DEPS)
	@ echo "Compilation Minishell.."
	@ $(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LREADLINE)
	@ echo "..done !"

$(OBJS_PATH)/%.o:$(SRCS_PATH)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.phony:
	clean fclean re all
