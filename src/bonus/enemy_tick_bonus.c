/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_tick_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	enemy_walk_tick(t_enemy *e, double dt)
{
	e->timer += dt;
	e->frame = ((int)(e->timer / ENEMY_WALK_TIME)) % 4;
}

void	enemy_hurt_tick(t_enemy *e, double dt)
{
	e->timer += dt;
	if (e->timer >= ENEMY_HURT_TIME)
		enemy_set_state(e, ENEMY_WALK);
}

void	enemy_die_tick(t_enemy *e, double dt)
{
	e->timer += dt;
	e->frame = (int)(e->timer / ENEMY_DIE_TIME);
	if (e->frame > 2)
		e->frame = 2;
	if (e->timer >= ENEMY_DIE_TIME * 3.0)
		e->alive = 0;
}

void	enemy_attack_tick(t_game *game, t_enemy *e, double dt)
{
	const int	dmg[2] = {ENEMY_SPIDER_DMG, ENEMY_ZOMBIE_DMG};
	double		dx;
	double		dy;

	e->timer += dt;
	if (e->timer < ENEMY_ATTACK_TIME)
		return ;
	e->timer = 0.0;
	e->frame++;
	if (e->frame == 1 && !e->hit_applied)
	{
		dx = game->player.pos_x - e->x;
		dy = game->player.pos_y - e->y;
		if (sqrt(dx * dx + dy * dy) <= ENEMY_ATTACK_DIST + 0.4
			&& enemy_has_los(game, e))
			bonus_damage_player(game, dmg[e->type]);
		e->hit_applied = 1;
	}
	if (e->frame >= 2)
		enemy_set_state(e, ENEMY_WALK);
}

void	enemy_close_tick(t_game *game, t_enemy *e, double dt)
{
	if (e->state != ENEMY_ATTACK)
		enemy_set_state(e, ENEMY_ATTACK);
	enemy_attack_tick(game, e, dt);
}
