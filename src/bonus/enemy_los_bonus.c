/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_los_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	enemy_solid(char c)
{
	return (c == '1' || c == 'D' || c == 'T');
}

int	enemy_has_los(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;
	double	t;
	int		mx;
	int		my;

	dx = (game->player.pos_x - e->x) / e->dist;
	dy = (game->player.pos_y - e->y) / e->dist;
	t = 0.2;
	while (t < e->dist)
	{
		mx = (int)(e->x + dx * t);
		my = (int)(e->y + dy * t);
		if (enemy_solid(game->map.grid[my][mx]))
			return (0);
		t += 0.2;
	}
	return (1);
}
