# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdraper <mdraper@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/11 14:49:44 by mdraper       #+#    #+#                  #
#    Updated: 2024/06/11 17:17:36 by mdraper       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

# **************************************|************************************** #
#								    LIBRARIES									#
# **************************************|************************************** #

GIT_CLONE	:= @git clone

LIBFT_DIR	:= lib/libft
GIT_LIBFT	:= $(GIT_CLONE) https://github.com/mdrapercodam/libft.git $(LIBFT_DIR)
LIBFT		:= $(LIBFT_DIR)/libft.a

# **************************************|************************************** #
#								   INGREDIENTS									#
# **************************************|************************************** #

INCS		:= inc

SRC_DIR		:= src
OBJ_DIR		:= obj

SRCS		:= $(shell find $(SRC_DIR) -iname "*.c")
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
HEADERS		:= -I $(INCS) -I $(LIBFT_DIR)/inc
LDFLAGS		:= -lreadline

# **************************************|************************************** #
#									 UTENSILS									#
# **************************************|************************************** #

RM			:= rm -f
RM_DIR		:= rm -rf
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

# **************************************|************************************** #
#									 RECIPES									#
# **************************************|************************************** #

all: $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)
	
$(LIBFT_DIR):
	$(GIT_LIBFT)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM_DIR) $(OBJ_DIR)
	$(info REMOVED OBJ $(NAME))

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(info REMOVED $(NAME))

re: fclean all

# **************************************|************************************** #
#									  SPEC										#
# **************************************|************************************** #

.PHONY: all clean fclean re
.SILENT:
