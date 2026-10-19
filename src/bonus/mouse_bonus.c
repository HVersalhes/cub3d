/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bonus_update_look(t_game *game)
{
	t_bonus	*b;
	int		x;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	if (!b->mouse_init)
	{
		b->mouse_init = 1;
		b->mouse_x = WIN_WIDTH / 2;
		b->mouse_y = WIN_HEIGHT / 2;
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2,
			WIN_HEIGHT / 2);
		return ;
	}
	x = b->mouse_x;
	b->mouse_x = WIN_WIDTH / 2;
	b->mouse_y = WIN_HEIGHT / 2;
	if (x == WIN_WIDTH / 2)
		return ;
	rotate_player(game, (x - WIN_WIDTH / 2) * MOUSE_SENSITIVITY);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2,
		WIN_HEIGHT / 2);
}
