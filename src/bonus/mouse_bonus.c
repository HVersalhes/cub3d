/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:55:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	center_mouse(t_game *game)
{
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

int	bonus_mouse_hook(int x, int y, t_game *game)
{
	t_bonus	*b;
	int		delta;

	(void)y;
	if (!game->bonus)
		return (0);
	b = (t_bonus *)game->bonus;
	if (b->mouse_x < 0)
	{
		if (x < WIN_WIDTH / 2 - MOUSE_START_ZONE
			|| x > WIN_WIDTH / 2 + MOUSE_START_ZONE)
		{
			center_mouse(game);
			return (0);
		}
		b->mouse_x = x;
		return (0);
	}
	delta = x - b->mouse_x;
	if (delta == 0)
		return (0);
	rotate_player(game, delta * MOUSE_SENSITIVITY);
	center_mouse(game);
	b->mouse_x = WIN_WIDTH / 2;
	return (0);
}
