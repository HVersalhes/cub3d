# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcosta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/15 18:12:12 by hcosta            #+#    #+#              #
#    Updated: 2026/09/15 18:40:55 by hcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC_DIR = src
OBJ_DIR = obj

SRC = $(SRC_DIR)/main.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
