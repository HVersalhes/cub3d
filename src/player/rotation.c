/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:27:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:27:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, double angle)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;
	double		cos_a;
	double		sin_a;

	p = &game->player;
	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos_a - p->dir_y * sin_a;
	p->dir_y = old_dir_x * sin_a + p->dir_y * cos_a;
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos_a - p->plane_y * sin_a;
	p->plane_y = old_plane_x * sin_a + p->plane_y * cos_a;
}

void	update_player_rotation(t_game *game)
{
	if (game->keys.rot_left)
		rotate_player(game, -game->player.rot_speed);
	if (game->keys.rot_right)
		rotate_player(game, game->player.rot_speed);
}
