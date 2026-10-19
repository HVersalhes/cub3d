/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 11:45:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:45:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

/*
** A spawn spot is a free tile far enough from the player, so no pack
** member starts the level breathing on the player's neck.
*/
static int	enemy_candidate(t_game *game, int x, int y)
{
	double	dx;
	double	dy;

	if (game->map.grid[y][x] != '0')
		return (0);
	dx = x + 0.5 - game->player.pos_x;
	dy = y + 0.5 - game->player.pos_y;
	return (dx * dx + dy * dy >= ENEMY_SPAWN_MIN2);
}

static int	count_spots(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
			if (enemy_candidate(game, x, y))
				count++;
	}
	return (count);
}

static void	spawn_one(t_bonus *b, int idx, int x, int y)
{
	t_enemy	*e;

	e = &b->enemies[idx];
	e->x = x + 0.5;
	e->y = y + 0.5;
	e->last_x = e->x;
	e->last_y = e->y;
	e->memory = 0.0;
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

/*
** Second sweep: one enemy every step-th spot.  The step comes from the
** total number of spots, so the pack ends up spread over the whole
** level -- rooms, corridors and the open arena -- instead of crowded
** around the player.
*/
static int	spawn_spots(t_game *game, t_bonus *b, int step)
{
	int	count;
	int	spot;
	int	y;
	int	x;

	count = 0;
	spot = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width && count < ENEMY_MAX)
		{
			if (!enemy_candidate(game, x, y))
				continue ;
			if (spot++ % step == 0)
			{
				spawn_one(b, count, x, y);
				count++;
			}
		}
	}
	return (count);
}

void	bonus_spawn_enemies(t_game *game, t_bonus *b)
{
	int	total;
	int	step;

	total = count_spots(game);
	step = 1;
	if (total > ENEMY_MAX)
		step = (total + ENEMY_MAX - 1) / ENEMY_MAX;
	b->enemy_count = spawn_spots(game, b, step);
	ft_printf("[cub3d] enemies spawned: %d\n", b->enemy_count);
}
