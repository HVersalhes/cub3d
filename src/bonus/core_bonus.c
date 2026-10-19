/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:20:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	bonus_init(t_game *game)
{
	t_bonus	*b;

	b = ft_calloc(1, sizeof(t_bonus));
	if (!b)
		error_exit("Failed to allocate bonus state", game);
	game->bonus = b;
	bonus_init_doors(game, b);
	bonus_init_sprites(game, b);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	b->mouse_x = -1;
	b->last_time = get_time();
}

void	bonus_update(t_game *game)
{
	t_bonus	*b;
	double	now;
	double	dt;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	now = get_time();
	dt = now - b->last_time;
	b->last_time = now;
	if (dt < 0.0)
		dt = 0.0;
	if (dt > 0.1)
		dt = 0.1;
	bonus_update_doors(game, b, dt);
	bonus_update_sprites(b, dt);
}

void	bonus_render(t_game *game)
{
	bonus_render_sprites(game);
	bonus_render_minimap(game);
}

void	bonus_free(t_game *game)
{
	t_bonus	*b;

	if (!game->bonus)
		return ;
	b = (t_bonus *)game->bonus;
	bonus_free_sprites(game, b);
	if (game->mlx_ptr && b->door_tex.img_ptr)
		mlx_destroy_image(game->mlx_ptr, b->door_tex.img_ptr);
	if (b->doors)
		free(b->doors);
	free(b);
	game->bonus = NULL;
}
