/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 20:06:40 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 13:30:36 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# include "cub3d_structs.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.01
# define COLLISION_RADIUS 0.20

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* exit and cleanup */
void	error_exit(const char *message, t_game *game);
void	free_game(t_game *game);
int		close_game(t_game *game);

/* initialization */
void	init_game_data(t_game *game);
void	init_player(t_game *game);
void	init_mlx(t_game *game);
void	init_textures(t_game *game);

/* parsing */
void	parse_cub_file(const char *file_path, t_game *game);
int		parse_texture_line(char *line, t_game *game);
int		parse_color_line(char *line, t_game *game);
void	parse_map(int fd, char *first_line, t_game *game);
void	validate_map(t_game *game);

/* raycasting */
void	calculate_ray_vector(t_game *game, t_ray *ray, int x);
void	init_ray_step(t_game *game, t_ray *ray);
void	execute_dda(t_game *game, t_ray *ray);
void	calculate_wall_projection(t_game *game, t_ray *ray);
void	perform_raycasting(t_game *game);

/* rendering */
int		game_loop(t_game *game);
void	render_frame(t_game *game);
void	render_ceiling_floor(t_game *game);
void	draw_textured_wall_slice(t_game *game, t_ray *ray, int x);
int		get_wall_texture_index(t_ray *ray);
void	my_pixel_put(t_img *img, int x, int y, int color);

/* player and events */
void	update_player_movement(t_game *game);
void	update_player_rotation(t_game *game);
void	rotate_player(t_game *game, double angle);
int		is_valid_walk_position(t_game *game, double x, double y);
int		key_press_handler(int keycode, t_game *game);
int		key_release_handler(int keycode, t_game *game);

#endif
