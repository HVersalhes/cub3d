/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:27:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward_backward(t_game *game, double *dx, double *dy)
{
	double	spd;

	spd = game->player.move_speed;
	if (game->keys.w)
	{
		*dx += game->player.dir_x * spd;
		*dy += game->player.dir_y * spd;
	}
	if (game->keys.s)
	{
		*dx -= game->player.dir_x * spd;
		*dy -= game->player.dir_y * spd;
	}
}

static void	move_strafe(t_game *game, double *dx, double *dy)
{
	double	spd;

	spd = game->player.move_speed;
	if (game->keys.d)
	{
		*dx += game->player.plane_x * spd;
		*dy += game->player.plane_y * spd;
	}
	if (game->keys.a)
	{
		*dx -= game->player.plane_x * spd;
		*dy -= game->player.plane_y * spd;
	}
}

static void	apply_movement(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dx;
	new_y = game->player.pos_y + dy;
	if (is_valid_walk_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_walk_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	update_player_movement(t_game *game)
{
	double	dx;
	double	dy;

	dx = 0.0;
	dy = 0.0;
	move_forward_backward(game, &dx, &dy);
	move_strafe(game, &dx, &dy);
	if (dx != 0.0 || dy != 0.0)
		apply_movement(game, dx, dy);
	update_player_rotation(game);
}
