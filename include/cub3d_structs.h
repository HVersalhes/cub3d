/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:22:46 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:12:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <stdbool.h>

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

typedef struct s_texture
{
	char	*path;
	t_img	img;
}	t_texture;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

/*
** Per-column state of a textured wall slice.  Kept in a struct so the
** inner pixel loop needs a single variable and writes the framebuffer
** through raw pointers (no per-pixel function calls).
*/
typedef struct s_wallcol
{
	char	*tex;
	char	*row;
	char	*end;
	int		tline;
	int		txoff;
	int		hmask;
	int		line;
	int		step;
	int		pos;
	int		shade;
	int		tex_h;
}	t_wallcol;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	rot_left;
	bool	rot_right;
	bool	door_interact;
	bool	door_interact_held;
}	t_keys;

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

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}	t_map_node;

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
	double	wall_x;
	int		tex_x;
	int		is_door;
	int		tex_offset;
}	t_ray;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		frame;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_texture	textures[4];
	double		*z_buffer;
	char		*current_line;
	void		*bonus;
}	t_game;

#endif