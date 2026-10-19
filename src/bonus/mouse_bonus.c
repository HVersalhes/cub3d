/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:35:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bonus_mouse_hook(int x, int y, t_game *game)
{
	t_bonus	*b;
	int		delta;

	(void)y;
	if (!game->bonus)
		return (0);
	b = (t_bonus *)game->bonus;
	delta = x - b->mouse_x;
	if (delta == 0)
	{
		b->mouse_x = x;
		return (0);
	}
	rotate_player(game, delta * MOUSE_SENSITIVITY);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	b->mouse_x = WIN_WIDTH / 2;
	return (0);
}
