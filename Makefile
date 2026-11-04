# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/15 18:12:12 by hcosta            #+#    #+#              #
#    Updated: 2026/11/04 17:23:30 by hcuessec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft -Iminilibx
LDLIBS		= -Lminilibx -lmlx -Llibft -lft -lXext -lX11 -lm

SRC			= src/main.c \
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
			  src/raycasting/raycasting.c \
			  src/render/render_floor_ceiling.c \
			  src/render/render_frame.c \
			  src/render/texture_mapping.c \
			  src/events/keyboard.c \
			  src/player/movement.c \
			  src/player/rotation.c \
			  src/player/collision.c

OBJ			= $(SRC:.c=.o)
HEADERS		= include/cub3d.h include/cub3d_structs.h libft/libft.h \
			  libft/ft_printf.h
LIBFT		= libft/libft.a
MLX			= minilibx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(OBJ) $(LDLIBS) -o $(NAME)

$(OBJ): $(HEADERS)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
