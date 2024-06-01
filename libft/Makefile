NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

INC_DIR = includes
SRCS_DIR = src
OBJ_DIR = obj

SRCS_LIBFT := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
			ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c\
			ft_lstnew_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c \
			ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRCS_FT_PRINTF := ft_printf.c ft_printf_sub.c
SRCS_GET_NEXT_LINE := get_next_line.c get_next_line_utils.c

OBJ_FT_PRINTF := $(addprefix $(OBJ_DIR)/ft_printf/,$(SRCS_FT_PRINTF:.c=.o))
OBJ_LIBFT := $(addprefix $(OBJ_DIR)/libft/,$(SRCS_LIBFT:.c=.o))
OBJ_GET_NEXT_LINE := $(addprefix $(OBJ_DIR)/get_next_line/,$(SRCS_GET_NEXT_LINE:.c=.o))

OBJECTS := $(OBJ_FT_PRINTF) $(OBJ_LIBFT) $(OBJ_GET_NEXT_LINE)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/ft_printf/%.o: $(SRCS_DIR)/ft_printf/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/libft/%.o: $(SRCS_DIR)/libft/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/get_next_line/%.o: $(SRCS_DIR)/get_next_line/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
