/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:45:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

	dx = e->last_x - e->x;
	dy = e->last_y - e->y;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.0001)
		return ;
	step = ENEMY_WALK_SPEED * dt;
	enemy_try_move(game, e, e->x + dx / len * step, e->y);
	enemy_try_move(game, e, e->x, e->y + dy / len * step);
	enemy_walk_tick(e, dt);
}

/*
** Pack reaction: inside the sight radius and with a clear line to the
** player, the enemy memorises where the player is and walks there.
** Without a line of sight it keeps walking towards the last place it
** saw the player for a few seconds, then it freezes again.  A closed
** door stops the pack exactly like it stops the player.
*/
static void	enemy_pursue(t_game *game, t_enemy *e, double dt)
{
	if (e->dist < ENEMY_SIGHT && enemy_has_los(game, e))
	{
		e->last_x = game->player.pos_x;
		e->last_y = game->player.pos_y;
		e->memory = ENEMY_MEMORY;
		enemy_chase(game, e, dt);
		return ;
	}
	if (e->memory > 0.0)
	{
		e->memory -= dt;
		enemy_chase(game, e, dt);
	}
}

static void	enemy_think(t_game *game, t_enemy *e, double dt)
{
	if (!e->alive)
		return ;
	if (e->state == ENEMY_DIE)
		enemy_die_tick(e, dt);
	else if (e->state == ENEMY_HURT)
		enemy_hurt_tick(e, dt);
	else
	{
		e->dist = enemy_dist(game, e);
		if (e->dist <= ENEMY_ATTACK_DIST)
			enemy_close_tick(game, e, dt);
		else if (e->state == ENEMY_ATTACK)
			enemy_set_state(e, ENEMY_WALK);
		else
			enemy_pursue(game, e, dt);
	}
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
