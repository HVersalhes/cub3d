/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:20:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:20:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	toggle_door(t_game *game, t_door *door)
{
	if (door->state == DOOR_OPEN || door->state == DOOR_OPENING)
	{
		door->state = DOOR_CLOSING;
		game->map.grid[door->y][door->x] = 'D';
	}
	else
		door->state = DOOR_OPENING;
}

static void	advance_door(t_game *game, t_door *door, double dt)
{
	if (door->state == DOOR_OPENING)
	{
		door->openness += DOOR_SPEED * dt;
		if (door->openness >= 1.0)
		{
			door->openness = 1.0;
			door->state = DOOR_OPEN;
			game->map.grid[door->y][door->x] = '0';
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->openness -= DOOR_SPEED * dt;
		if (door->openness <= 0.0)
		{
			door->openness = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
}

static void	interact_with_door(t_game *game, t_bonus *b)
{
	double	dist;
	int		mx;
	int		my;
	int		idx;

	dist = 0.4;
	while (dist <= DOOR_INTERACT_DIST)
	{
		mx = (int)(game->player.pos_x + game->player.dir_x * dist);
		my = (int)(game->player.pos_y + game->player.dir_y * dist);
		if (mx < 0 || my < 0 || mx >= game->map.width
			|| my >= game->map.height)
			return ;
		if (game->map.grid[my][mx] == '1')
			return ;
		idx = bonus_find_door(b, mx, my);
		if (idx >= 0)
		{
			if (mx != (int)game->player.pos_x
				|| my != (int)game->player.pos_y)
				toggle_door(game, &b->doors[idx]);
			return ;
		}
		dist += 0.2;
	}
}

void	bonus_update_doors(t_game *game, t_bonus *b, double dt)
{
	int	i;

	i = 0;
	while (i < b->door_count)
	{
		advance_door(game, &b->doors[i], dt);
		i++;
	}
	if (game->keys.door_interact)
	{
		game->keys.door_interact = false;
		interact_with_door(game, b);
	}
}
