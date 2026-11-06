/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:24:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_north_south(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}

static void	set_player_east_west(t_player *player, char direction)
{
	if (direction == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

static void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N' || direction == 'S')
		set_player_north_south(player, direction);
	else if (direction == 'E' || direction == 'W')
		set_player_east_west(player, direction);
}

void	init_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->pos_x = (double)game->map.player_spawn_x + 0.5;
	player->pos_y = (double)game->map.player_spawn_y + 0.5;
	set_player_direction(player, game->map.player_dir);
}
