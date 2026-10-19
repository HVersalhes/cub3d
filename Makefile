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
CC = cc
MODE ?= mandatory
MODE_STAMP = .build_mode

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -I$(LIBFT_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

SRC_DIR = src
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

HEADERS = include/cub3d.h include/cub3d_structs.h include/cub3d_bonus.h

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
       $(SRC_DIR)/bonus/stub2_bonus.c \
       $(SRC_DIR)/bonus/stub_ray_bonus.c

BONUS_SRCS = $(filter-out $(SRC_DIR)/bonus/stub_bonus.c \
             $(SRC_DIR)/bonus/stub2_bonus.c \
             $(SRC_DIR)/bonus/stub_ray_bonus.c, $(SRCS)) \
             $(SRC_DIR)/bonus/assets_bonus.c \
             $(SRC_DIR)/bonus/combat_bonus.c \
             $(SRC_DIR)/bonus/core_bonus.c \
             $(SRC_DIR)/bonus/doors_bonus.c \
             $(SRC_DIR)/bonus/doors_ray_bonus.c \
             $(SRC_DIR)/bonus/doors_update_bonus.c \
             $(SRC_DIR)/bonus/draw_rect_bonus.c \
             $(SRC_DIR)/bonus/enemy_ai_bonus.c \
             $(SRC_DIR)/bonus/enemy_bonus.c \
             $(SRC_DIR)/bonus/enemy_los_bonus.c \
             $(SRC_DIR)/bonus/enemy_render_bonus.c \
             $(SRC_DIR)/bonus/enemy_tick_bonus.c \
             $(SRC_DIR)/bonus/floor_ceil_bonus.c \
             $(SRC_DIR)/bonus/fullscreen_bonus.c \
             $(SRC_DIR)/bonus/hud_bonus.c \
             $(SRC_DIR)/bonus/input_bonus.c \
             $(SRC_DIR)/bonus/log_bonus.c \
             $(SRC_DIR)/bonus/menu_bonus.c \
             $(SRC_DIR)/bonus/menu_load_bonus.c \
             $(SRC_DIR)/bonus/menu_render_bonus.c \
             $(SRC_DIR)/bonus/minimap_bonus.c \
             $(SRC_DIR)/bonus/minimap_tile_bonus.c \
             $(SRC_DIR)/bonus/mouse_bonus.c \
             $(SRC_DIR)/bonus/pause_bonus.c \
             $(SRC_DIR)/bonus/pause_render_bonus.c \
             $(SRC_DIR)/bonus/render_bonus.c \
             $(SRC_DIR)/bonus/shot_bonus.c \
             $(SRC_DIR)/bonus/sprites_bonus.c \
             $(SRC_DIR)/bonus/sprites_init_bonus.c \
             $(SRC_DIR)/bonus/sprites_list_bonus.c \
             $(SRC_DIR)/bonus/sprites_render_bonus.c \
             $(SRC_DIR)/bonus/sprites_sort_bonus.c \
             $(SRC_DIR)/bonus/sprites_update_bonus.c \
             $(SRC_DIR)/bonus/state_bonus.c \
             $(SRC_DIR)/bonus/validate_bonus.c \
             $(SRC_DIR)/bonus/validate_closed_bonus.c \
             $(SRC_DIR)/bonus/validate_grid_bonus.c \
             $(SRC_DIR)/bonus/validate_lines_bonus.c \
             $(SRC_DIR)/bonus/weapon_bonus.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
BONUS_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(BONUS_SRCS))

ifeq ($(MODE),bonus)
 BUILD_OBJS = $(BONUS_OBJS)
else
 BUILD_OBJS = $(OBJS)
endif

all:
	@$(MAKE) --no-print-directory MODE=mandatory $(NAME)

bonus:
	@$(MAKE) --no-print-directory MODE=bonus $(NAME)

$(MODE_STAMP): FORCE
	@printf '%s\n' '$(MODE)' | cmp -s - $@ || printf '%s\n' '$(MODE)' > $@

$(NAME): $(BUILD_OBJS) $(LIBFT_LIB) $(MLX_LIB) $(MODE_STAMP)
	$(CC) $(BUILD_OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) CC=gcc-12

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(MODE_STAMP)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

FORCE:

.PHONY: all bonus clean fclean re FORCE
