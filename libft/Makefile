# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcosta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 21:30:07 by hcosta            #+#    #+#              #
#    Updated: 2026/09/25 23:24:38 by hcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

FT_DIR	= .
PF_DIR	= ft_printf
GNL_DIR	= gnl/get_next_line_bonus

FT_SRCS	= ft_atoi.c ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c \
		ft_bzero.c ft_memcmp.c ft_split.c ft_strmapi.c ft_calloc.c \
		ft_memcpy.c ft_strchr.c ft_strncmp.c ft_isalnum.c ft_memmove.c \
		ft_strdup.c ft_strnstr.c ft_isalpha.c ft_memset.c \
		ft_striteri.c ft_strrchr.c ft_isascii.c ft_putchar_fd.c \
		ft_strjoin.c ft_strtrim.c ft_isdigit.c ft_putendl_fd.c \
		ft_strlcat.c ft_substr.c ft_isprint.c ft_putnbr_fd.c \
		ft_strlcpy.c ft_tolower.c ft_itoa.c
PF_SRCS	= ft_printf.c ft_putchar.c ft_putnbr.c ft_putnbr_base.c \
	  ft_putptr.c ft_putstr.c

GNL_SRCS	= get_next_line_bonus.c get_next_line_utils_bonus.c

FT_OBJS	= $(patsubst %.c,obj/%.o,$(FT_SRCS))
PF_OBJS	= $(patsubst %.c,obj/%.o,$(PF_SRCS))
GNL_OBJS	= $(patsubst %.c,obj/%.o,$(GNL_SRCS))
OBJS	= $(FT_OBJS) $(PF_OBJS) $(GNL_OBJS)

HEADERS	= libft.h $(PF_DIR)/ft_printf.h $(GNL_DIR)/get_next_line_bonus.h

CC	= cc
CFLAGS	= -Wall -Wextra -Werror \
	  -I$(FT_DIR) -I$(PF_DIR) -I$(GNL_DIR) \
	  -DBUFFER_SIZE=42
AR	= ar rcs
RM	= rm -f

.PHONY: all clean fclean re

all: $(NAME)

obj:
	mkdir -p obj

obj/%.o: $(FT_DIR)/%.c $(HEADERS) | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: $(PF_DIR)/%.c $(HEADERS) | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: $(GNL_DIR)/%.c $(HEADERS) | obj
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
