# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcosta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/15 18:12:12 by hcosta            #+#    #+#              #
#    Updated: 2026/10/19 00:07:00 by hcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -I$(LIBFT_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/exit/error.c \
       $(SRC_DIR)/exit/free.c \
       $(SRC_DIR)/init/init_data.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) CC=gcc-12

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
