NAME = minishell
LIBFT_NAME = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
LDFLAGS = -lreadline

INC_DIR = includes
LIBFT_DIR = libft
SRCS_DIR = src
OBJ_DIR = obj

SRCS_MINISHELL = $(addprefix src/, main.c)
OBJ_MINISHELL := $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS_MINISHELL))

all: $(NAME)

$(NAME): $(OBJ_MINISHELL) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re