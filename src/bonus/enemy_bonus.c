/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

void	enemy_set_state(t_enemy *e, int state)
{
	e->state = state;
	e->frame = 0;
	e->timer = 0.0;
	if (state == ENEMY_ATTACK)
		e->hit_applied = 0;
}

static int	enemy_can_spawn(t_game *game, int x, int y)
{
	double	dx;
	double	dy;
	double	d2;

	if (game->map.grid[y][x] != '0')
		return (0);
	dx = x + 0.5 - game->player.pos_x;
	dy = y + 0.5 - game->player.pos_y;
	d2 = dx * dx + dy * dy;
	if (d2 < 16.0 || d2 > 81.0)
		return (0);
	return ((x * 7 + y * 13) % 5 == 0);
}

static void	spawn_one(t_bonus *b, int idx, int x, int y)
{
	t_enemy	*e;

	e = &b->enemies[idx];
	e->x = x + 0.5;
	e->y = y + 0.5;
	e->dist = 0.0;
	e->type = idx % 2;
	e->hp = ENEMY_SPIDER_HP;
	if (e->type == ENEMY_ZOMBIE)
		e->hp = ENEMY_ZOMBIE_HP;
	e->state = ENEMY_WALK;
	e->frame = 0;
	e->timer = 0.0;
	e->hit_applied = 0;
	e->alive = 1;
}

void	bonus_spawn_enemies(t_game *game, t_bonus *b)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height && count < ENEMY_MAX)
	{
		x = 0;
		while (x < game->map.width && count < ENEMY_MAX)
		{
			if (enemy_can_spawn(game, x, y) && (x * 7 + y * 13) % 5 == 0)
			{
				spawn_one(b, count, x, y);
				count++;
			}
			x++;
		}
		y++;
	}
	b->enemy_count = count;
	ft_printf("[cub3d] enemies spawned: %d\n", count);
}
