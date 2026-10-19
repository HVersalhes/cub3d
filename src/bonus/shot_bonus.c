/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shot_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static double	shot_angle_diff(double a, double b)
{
	double	d;

	d = a - b;
	while (d > M_PI)
		d -= 2.0 * M_PI;
	while (d < -M_PI)
		d += 2.0 * M_PI;
	if (d < 0.0)
		d = -d;
	return (d);
}

static int	shot_blocked(t_game *game, double px, double py)
{
	int		mx;
	int		my;
	char	c;

	mx = (int)px;
	my = (int)py;
	if (mx < 0 || my < 0 || mx >= game->map.width || my >= game->map.height)
		return (1);
	c = game->map.grid[my][mx];
	if (c == '1')
		return (1);
	if (c == 'D' && bonus_door_solid(game, mx, my))
		return (1);
	return (0);
}

static double	enemy_shot_dist(t_game *game, int i, double angle)
{
	t_enemy	*e;
	double	dist;
	double	diff;

	e = &((t_bonus *)game->bonus)->enemies[i];
	if (!e->alive || e->state == ENEMY_DIE)
		return (-1.0);
	dist = sqrt((e->x - game->player.pos_x) * (e->x - game->player.pos_x)
			+ (e->y - game->player.pos_y) * (e->y - game->player.pos_y));
	diff = shot_angle_diff(angle, atan2(e->y - game->player.pos_y,
				e->x - game->player.pos_x));
	if (diff > SHOT_ANGLE)
		return (-1.0);
	return (dist);
}

static int	shot_pick_target(t_game *game, double angle, double max_dist)
{
	double	dist;
	double	best_dist;
	int		best;
	int		i;

	best = -1;
	best_dist = 0.0;
	i = 0;
	while (i < ((t_bonus *)game->bonus)->enemy_count)
	{
		dist = enemy_shot_dist(game, i, angle);
		if (dist > 0.0 && dist <= max_dist
			&& (best < 0 || dist < best_dist))
		{
			best = i;
			best_dist = dist;
		}
		i++;
	}
	return (best);
}

void	bonus_hitscan(t_game *game)
{
	double	angle;
	double	px;
	double	py;
	double	t;
	int		idx;

	angle = atan2(game->player.dir_y, game->player.dir_x);
	t = 0.0;
	while (t <= SHOT_RANGE)
	{
		px = game->player.pos_x + cos(angle) * t;
		py = game->player.pos_y + sin(angle) * t;
		if (shot_blocked(game, px, py))
			break ;
		t += 0.05;
	}
	idx = shot_pick_target(game, angle, t);
	if (idx >= 0)
		bonus_damage_enemy(game, idx, SHOT_DAMAGE);
	else
		ft_printf("[shot] no target\n");
}
