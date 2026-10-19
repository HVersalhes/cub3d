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

# define MINIMAP_X 20
# define MINIMAP_Y 20
# define MINIMAP_TILE 15
# define MINIMAP_RADIUS 6

# define MM_COLOR_BG 0x0A0A12
# define MM_COLOR_WALL 0x7080A0
# define MM_COLOR_DOOR 0xC08040
# define MM_COLOR_FLOOR 0x202028
# define MM_COLOR_PLAYER 0xFF3030
# define MM_COLOR_DIR 0xFFD040

# define DOOR_SPEED 1.5
# define DOOR_INTERACT_DIST 1.5

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

typedef struct s_bonus
{
	t_img	door_tex;
	t_door	*doors;
	int		door_count;
	double	last_time;
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

#endif
