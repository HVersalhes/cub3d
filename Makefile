# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcosta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/15 18:12:12 by hcosta            #+#    #+#              #
#    Updated: 2026/10/19 01:10:00 by hcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
MANDATORY_NAME = cub3d_mandatory
BONUS_NAME = cub3d_bonus
CC = cc

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -I$(LIBFT_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

SRC_DIR = src
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/exit/error.c \
       $(SRC_DIR)/exit/free.c \
       $(SRC_DIR)/init/init_data.c \
       $(SRC_DIR)/init/init_mlx.c \
       $(SRC_DIR)/init/init_player.c \
       $(SRC_DIR)/init/init_textures.c \
       $(SRC_DIR)/parsing/parse_file.c \
       $(SRC_DIR)/parsing/parse_textures.c \
       $(SRC_DIR)/parsing/parse_colors.c \
       $(SRC_DIR)/parsing/parse_map.c \
       $(SRC_DIR)/parsing/validate_map.c \
       $(SRC_DIR)/raycasting/ray_direction.c \
       $(SRC_DIR)/raycasting/dda_algorithm.c \
       $(SRC_DIR)/raycasting/wall_distance.c \
       $(SRC_DIR)/render/render_floor_ceiling.c \
       $(SRC_DIR)/render/render_frame.c \
       $(SRC_DIR)/render/texture_mapping.c \
       $(SRC_DIR)/events/keyboard.c \
       $(SRC_DIR)/player/movement.c \
       $(SRC_DIR)/player/rotation.c \
       $(SRC_DIR)/player/collision.c \
       $(SRC_DIR)/bonus/stub_bonus.c \
       $(SRC_DIR)/bonus/stub_ray_bonus.c

BONUS_SRCS = $(filter-out $(SRC_DIR)/bonus/stub_bonus.c \
             $(SRC_DIR)/bonus/stub_ray_bonus.c, $(SRCS)) \
             $(SRC_DIR)/bonus/core_bonus.c \
             $(SRC_DIR)/bonus/minimap_bonus.c \
             $(SRC_DIR)/bonus/doors_bonus.c \
             $(SRC_DIR)/bonus/doors_update_bonus.c \
             $(SRC_DIR)/bonus/doors_ray_bonus.c \
             $(SRC_DIR)/bonus/mouse_bonus.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
BONUS_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(BONUS_SRCS))

all: $(MANDATORY_NAME)
	@cp $(MANDATORY_NAME) $(NAME)

bonus: $(BONUS_NAME)
	@cp $(BONUS_NAME) $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) CC=gcc-12

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MANDATORY_NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(OBJS) $(LDFLAGS) -o $(MANDATORY_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(MANDATORY_NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
