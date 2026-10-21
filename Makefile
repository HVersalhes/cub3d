#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/15 18:12:12 by hcosta            #+#    #+#              #
#    Updated: 2026/10/21 12:45:44 by hcuessec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -Ilibft
LDFLAGS = -Lminilibx -lmlx -Llibft -lft -lXext -lX11 -lm -lz
RM = rm -rf

LIBFT = libft/libft.a
MLX = minilibx/libmlx.a

INCS = include/cub3d.h \
	include/cub3d_structs.h \
	include/cub3d_bonus.h

COMMON_SRCS = src/main.c \
	src/exit/error.c \
	src/exit/free.c \
	src/init/init_data.c \
	src/init/init_mlx.c \
	src/init/init_player.c \
	src/init/init_textures.c \
	src/parsing/parse_file.c \
	src/parsing/parse_textures.c \
	src/parsing/parse_colors.c \
	src/parsing/parse_map.c \
	src/parsing/validate_map.c \
	src/raycasting/ray_direction.c \
	src/raycasting/dda_algorithm.c \
	src/raycasting/wall_distance.c \
	src/render/render_floor_ceiling.c \
	src/render/render_frame.c \
	src/render/img_draw.c \
	src/render/texture_mapping.c \
	src/events/keyboard.c \
	src/player/movement.c \
	src/player/rotation.c \
	src/player/collision.c

SRCS = $(COMMON_SRCS) \
	src/bonus/stub_bonus.c \
	src/bonus/stub2_bonus.c \
	src/bonus/stub_ray_bonus.c

BONUS_SRCS = $(COMMON_SRCS) \
	src/bonus/assets_bonus.c \
	src/bonus/assets_free_bonus.c \
	src/bonus/assets_paths_bonus.c \
	src/bonus/combat_bonus.c \
	src/bonus/core_bonus.c \
	src/bonus/doors_bonus.c \
	src/bonus/doors_ray_bonus.c \
	src/bonus/doors_update_bonus.c \
	src/bonus/draw_rect_bonus.c \
	src/bonus/enemy_ai_bonus.c \
	src/bonus/enemy_los_bonus.c \
	src/bonus/enemy_render_bonus.c \
	src/bonus/enemy_spawn_bonus.c \
	src/bonus/enemy_state_bonus.c \
	src/bonus/enemy_tick_bonus.c \
	src/bonus/floor_ceil_bonus.c \
	src/bonus/fullscreen_bonus.c \
	src/bonus/hud_bonus.c \
	src/bonus/input_bonus.c \
	src/bonus/log_bonus.c \
	src/bonus/menu_bonus.c \
	src/bonus/menu_load_bonus.c \
	src/bonus/menu_render_bonus.c \
	src/bonus/menu_rows_bonus.c \
	src/bonus/minimap_bonus.c \
	src/bonus/minimap_enemy_bonus.c \
	src/bonus/minimap_ring_bonus.c \
	src/bonus/minimap_tile_bonus.c \
	src/bonus/mouse_bonus.c \
	src/bonus/pause_bonus.c \
	src/bonus/pause_render_bonus.c \
	src/bonus/render_bonus.c \
	src/bonus/resize_bonus.c \
	src/bonus/shot_bonus.c \
	src/bonus/sprites_bonus.c \
	src/bonus/sprites_init_bonus.c \
	src/bonus/sprites_list_bonus.c \
	src/bonus/sprites_render_bonus.c \
	src/bonus/sprites_sort_bonus.c \
	src/bonus/sprites_update_bonus.c \
	src/bonus/state_bonus.c \
	src/bonus/validate_bonus.c \
	src/bonus/validate_closed_bonus.c \
	src/bonus/validate_grid_bonus.c \
	src/bonus/validate_lines_bonus.c \
	src/bonus/weapon_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

bonus: $(BONUS_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)

$(OBJS) $(BONUS_OBJS): $(INCS)

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C minilibx > /dev/null 2>&1

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C libft clean
	@$(MAKE) -C minilibx clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
