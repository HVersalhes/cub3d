/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	enemy_dist(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;

	dx = game->player.pos_x - e->x;
	dy = game->player.pos_y - e->y;
	return (sqrt(dx * dx + dy * dy));
}

static void	enemy_try_move(t_game *game, t_enemy *e, double nx, double ny)
{
	int		mx;
	int		my;
	char	c;

	mx = (int)nx;
	my = (int)ny;
	if (mx < 0 || my < 0 || mx >= game->map.width || my >= game->map.height)
		return ;
	c = game->map.grid[my][mx];
	if (enemy_solid(c))
		return ;
	e->x = nx;
	e->y = ny;
}

static void	enemy_chase(t_game *game, t_enemy *e, double dt)
{
	double	dx;
	double	dy;
	double	len;
	double	step;

	dx = game->player.pos_x - e->x;
	dy = game->player.pos_y - e->y;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.0001)
		return ;
	step = ENEMY_WALK_SPEED * dt;
	enemy_try_move(game, e, e->x + dx / len * step, e->y);
	enemy_try_move(game, e, e->x, e->y + dy / len * step);
	enemy_walk_tick(e, dt);
}

static void	enemy_think(t_game *game, t_enemy *e, double dt)
{
	double	dist;

	if (e->state == ENEMY_DIE)
	{
		enemy_die_tick(e, dt);
		return ;
	}
	if (e->state == ENEMY_HURT)
	{
		enemy_hurt_tick(e, dt);
		return ;
	}
	dist = enemy_dist(game, e);
	e->dist = dist;
	if (dist <= ENEMY_ATTACK_DIST)
		enemy_close_tick(game, e, dt);
	else if (e->state == ENEMY_ATTACK)
		enemy_set_state(e, ENEMY_WALK);
	else if (dist < ENEMY_AGGRO)
		enemy_chase(game, e, dt);
}

void	bonus_update_enemies(t_game *game, double dt)
{
	t_bonus	*b;
	int		i;

	b = (t_bonus *)game->bonus;
	i = 0;
	while (i < b->enemy_count)
	{
		enemy_think(game, &b->enemies[i], dt);
		i++;
	}
}
