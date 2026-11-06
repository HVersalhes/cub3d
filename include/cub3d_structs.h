/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:22:46 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <stdbool.h>

/*
** MiniLibX image: the pixel buffer and the information needed to
** address a pixel with the formula y * line_len + x * (bpp / 8).
*/
typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/*
** Current keyboard state. Movement is applied while a key is held,
** so key presses only change these flags.
*/
typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	rot_left;
	bool	rot_right;
}	t_keys;

/*
** Player position and camera vectors. dir_* points where the player
** looks and plane_* is perpendicular to it; together they define the
** field of view used by the raycasting code.
*/
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

/*
** Everything read from the .cub file. The grid is rectangular: shorter
** map lines are padded with spaces during parsing.
*/
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		player_count;
	char	player_dir;
	int		player_spawn_x;
	int		player_spawn_y;
}	t_map;

/*
** Temporary linked list used while reading map lines. The grid is only
** allocated after the width and height are known.
*/
typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}	t_map_node;

/*
** State of one cast ray. DDA fills map_x/map_y and the side values until
** a wall is found; the projection values are then used to draw one column.
*/
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/*
** Main game object. It owns the map, the player, the window, the
** framebuffer and the four wall textures (NO, SO, WE, EA).
*/
typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		frame;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_img		textures[4];
	char		*current_line;
	int			map_fd;
}	t_game;

#endif
