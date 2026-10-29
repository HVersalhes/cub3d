/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

void	bonus_tick_timers(t_bonus *b, double dt)
{
	if (b->damage_flash > 0.0)
		b->damage_flash -= dt;
	if (b->damage_flash < 0.0)
		b->damage_flash = 0.0;
	if (b->hurt_cd > 0.0)
		b->hurt_cd -= dt;
	if (b->hurt_cd < 0.0)
		b->hurt_cd = 0.0;
}

void	bonus_damage_player(t_game *game, int dmg)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b || b->state != STATE_PLAYING)
		return ;
	if (b->hurt_cd > 0.0)
		return ;
	b->hurt_cd = HURT_COOLDOWN;
	b->health -= dmg;
	b->damage_flash = FLASH_TIME;
	ft_printf("[combat] player hit for %d (hp %d)\n", dmg, b->health);
	if (b->health <= 0)
	{
		b->health = 0;
		ft_printf("Game Over! You died.\n");
		close_game(game);
	}
}

void	bonus_damage_enemy(t_game *game, int idx, int dmg)
{
	t_bonus	*b;
	t_enemy	*e;

	b = (t_bonus *)game->bonus;
	if (!b || idx < 0 || idx >= b->enemy_count)
		return ;
	e = &b->enemies[idx];
	if (!e->alive || e->state == ENEMY_DIE)
		return ;
	e->hp -= dmg;
	ft_printf("[combat] enemy %d hit for %d (hp %d)\n", idx, dmg, e->hp);
	if (e->hp <= 0)
	{
		enemy_set_state(e, ENEMY_DIE);
		ft_printf("[combat] enemy %d is dead\n", idx);
	}
	else
		enemy_set_state(e, ENEMY_HURT);
}
