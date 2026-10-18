/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 20:06:40 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:24:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"
# include "cub3d_structs.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.04

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_E 101
# define KEY_SPACE 32

/* exit / free */
void	error_exit(const char *msg, t_game *game);
void	free_tab(char **tab);
void	free_map(t_map *map);
void	free_game(t_game *game);
int		close_game(t_game *game);

/* init */
void	init_game_data(t_game *game);
int		init_mlx(t_game *game);
void	init_player(t_game *game);
void	init_textures(t_game *game);

/* parsing */
char	*get_next_line(int fd);
void	parse_cub_file(const char *file_path, t_game *game);
int		parse_texture_line(char *line, t_game *game);
int		parse_color_line(char *line, t_game *game);
void	parse_map(int fd, char *first_line, t_game *game);
void	validate_map(t_game *game);

/* raycasting & render */
void	calculate_ray_vector(t_game *game, t_ray *ray, int x);
void	init_ray_step(t_game *game, t_ray *ray);
void	execute_dda(t_game *game, t_ray *ray);
void	calculate_wall_projection(t_game *game, t_ray *ray, int x);
int		game_loop(t_game *game);
void	render_frame(t_game *game);
void	render_ceiling_floor(t_game *game);
void	perform_raycasting(t_game *game);
void	my_pixel_put(t_img *img, int x, int y, int color);
int		get_texture_pixel(t_img *img, int x, int y);

/* player & events */
void	update_player_movement(t_game *game);
int		key_press_handler(int keycode, t_game *game);
int		key_release_handler(int keycode, t_game *game);

#endif
