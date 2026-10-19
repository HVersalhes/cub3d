/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:20:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

# define MINIMAP_MARGIN 20
# define MINIMAP_WIDTH 260
# define MINIMAP_HEIGHT 180
# define MINIMAP_X MINIMAP_MARGIN
# define MINIMAP_Y 600
# define MINIMAP_SCALE 15.0

# define MM_COLOR_WALL 0x9CB8D8
# define MM_COLOR_DOOR 0x3EC8D8
# define MM_COLOR_FLOOR 0x1E2A38
# define MM_COLOR_PLAYER 0xFF3B30
# define MM_COLOR_SPRITE 0xFF9838

# define MM_WALL_PACKED 0x8C9CB8D8
# define MM_DOOR_PACKED 0xA63EC8D8
# define MM_SPRITE_PACKED 0xADFF9838
# define MM_FLOOR_PACKED 0x2E1E2A38

# define DOOR_SPEED 1.5
# define DOOR_INTERACT_DIST 1.5

# define MOUSE_SENSITIVITY 0.0026
# define MOUSE_MAX_ANGLE 1.5707963

# define SPRITE_FRAMES 4
# define SPRITE_FRAME_TIME 0.15
# define SPRITE_MAGENTA 0xFF00FF

# define DOOR_CLOSED 0
# define DOOR_OPENING 1
# define DOOR_OPEN 2
# define DOOR_CLOSING 3

typedef struct s_door
{
	int		x;
	int		y;
	int		state;
	double	openness;
}	t_door;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
}	t_sprite;

typedef struct s_sprite_draw
{
	t_img	*tex;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		width;
	int		height;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
}	t_sprite_draw;

typedef struct s_mm_view
{
	double	fx;
	double	fy;
	double	rx;
	double	ry;
}	t_mm_view;

typedef struct s_bonus
{
	t_img		door_tex;
	t_door		*doors;
	int			door_count;
	t_img		sprite_tex[SPRITE_FRAMES];
	t_sprite	*sprites;
	int			sprite_count;
	int			sprite_frame;
	double		sprite_timer;
	int			mouse_init;
	double		mouse_yaw;
	double		last_time;
}	t_bonus;

void	bonus_init(t_game *game);
void	bonus_update(t_game *game);
void	bonus_render(t_game *game);
void	bonus_free(t_game *game);
void	bonus_render_minimap(t_game *game);
void	bonus_init_doors(t_game *game, t_bonus *b);
int		bonus_find_door(t_bonus *b, int x, int y);
void	bonus_update_doors(t_game *game, t_bonus *b, double dt);
int		bonus_door_blocks(t_game *game, t_ray *ray);
t_img	*bonus_door_texture(t_game *game, t_ray *ray);
int		bonus_mouse_hook(int x, int y, t_game *game);
void	bonus_init_sprites(t_game *game, t_bonus *b);
void	bonus_free_sprites(t_game *game, t_bonus *b);
void	bonus_update_sprites(t_bonus *b, double dt);
void	bonus_render_sprites(t_game *game);
void	bonus_sort_sprites(t_bonus *b, t_player *p);

#endif
