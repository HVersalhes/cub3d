/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:24:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:24:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_north_south(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0.0;
		p->dir_y = -1.0;
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0.0;
		p->dir_y = 1.0;
		p->plane_x = -0.66;
		p->plane_y = 0.0;
	}
}

static void	set_player_east_west(t_player *p, char dir)
{
	if (dir == 'E')
	{
		p->dir_x = 1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		p->dir_x = -1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	t_player	*p;
	char		dir;

	p = &game->player;
	dir = game->map.player_dir;
	p->pos_x = (double)game->map.player_spawn_x + 0.5;
	p->pos_y = (double)game->map.player_spawn_y + 0.5;
	p->move_speed = MOVE_SPEED;
	p->rot_speed = ROT_SPEED;
	if (dir == 'N' || dir == 'S')
		set_player_north_south(p, dir);
	else if (dir == 'E' || dir == 'W')
		set_player_east_west(p, dir);
}
