/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 02:30:00 by hcosta           ###   ########.fr       */
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
	double	target;

	(void)y;
	if (!game->bonus)
		return (0);
	b = (t_bonus *)game->bonus;
	if (!b->mouse_init)
	{
		center_mouse(game);
		b->mouse_init = 1;
		return (0);
	}
	target = (double)(x - WIN_WIDTH / 2) * MOUSE_SENSITIVITY;
	if (target > MOUSE_MAX_ANGLE)
		target = MOUSE_MAX_ANGLE;
	else if (target < -MOUSE_MAX_ANGLE)
		target = -MOUSE_MAX_ANGLE;
	if (target == b->mouse_yaw)
		return (0);
	rotate_player(game, target - b->mouse_yaw);
	b->mouse_yaw = target;
	return (0);
}
