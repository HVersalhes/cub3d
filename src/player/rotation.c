/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:27:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Rotates both the direction vector and the camera plane by the same
** angle. The formulas are the standard 2D rotation matrix.
*/
void	rotate_player(t_game *game, double angle)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;
	double		cos_angle;
	double		sin_angle;

	player = &game->player;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos_angle
		- player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle
		+ player->dir_y * cos_angle;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos_angle
		- player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle
		+ player->plane_y * cos_angle;
}

void	update_player_rotation(t_game *game)
{
	if (game->keys.rot_left)
		rotate_player(game, -game->player.rot_speed);
	if (game->keys.rot_right)
		rotate_player(game, game->player.rot_speed);
}
