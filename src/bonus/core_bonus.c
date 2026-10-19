/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static double	update_dt(t_bonus *b)
{
	struct timeval	tv;
	double			now;
	double			dt;

	gettimeofday(&tv, NULL);
	now = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	dt = now - b->last_time;
	b->last_time = now;
	if (dt < 0.0)
		dt = 0.0;
	if (dt > 0.1)
		dt = 0.1;
	return (dt);
}

static void	fps_tick(t_bonus *b)
{
	struct timeval	tv;
	double			elapsed;

	if (!b->menu_mode)
		return ;
	b->fps_frames++;
	gettimeofday(&tv, NULL);
	if (b->fps_start == 0.0)
		b->fps_start = (double)tv.tv_sec
			+ (double)tv.tv_usec / 1000000.0;
	elapsed = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0
		- b->fps_start;
	if (elapsed < 5.0)
		return ;
	ft_printf("[perf] %d frames in %d ms (%d fps)\n", b->fps_frames,
		(int)(elapsed * 1000.0), (int)(b->fps_frames / elapsed));
	b->fps_frames = 0;
	b->fps_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

void	bonus_init(t_game *game)
{
	t_bonus	*b;

	b = bonus_state_new(game);
	bonus_init_level(game, b);
	bonus_enter_overlay(game, STATE_PLAYING);
	ft_printf("[cub3d] level ready: %d torches, %d enemies\n",
		b->sprite_count, b->enemy_count);
}

void	bonus_update(t_game *game)
{
	t_bonus	*b;
	double	dt;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	fps_tick(b);
	dt = update_dt(b);
	if (b->state != STATE_PLAYING)
		return ;
	bonus_tick_timers(b, dt);
	if (b->menu_mode)
		bonus_update_look(game);
	bonus_update_doors(game, b, dt);
	bonus_update_sprites(b, dt);
	bonus_update_enemies(game, dt);
	bonus_update_weapon(game, dt);
}

void	bonus_free(t_game *game)
{
	t_bonus	*b;

	if (!game->bonus)
		return ;
	b = (t_bonus *)game->bonus;
	if (b->doors)
		free(b->doors);
	bonus_free_sprites(game, b);
	bonus_free_assets(game, b);
	free(b);
	game->bonus = NULL;
}
