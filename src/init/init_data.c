/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:07:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:07:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_data(t_game *game)
{
	int	i;

	ft_bzero(game, sizeof(t_game));
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	game->map.player_spawn_x = -1;
	game->map.player_spawn_y = -1;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	i = 0;
	while (i < 4)
	{
		game->textures[i].path = NULL;
		game->textures[i].img.img_ptr = NULL;
		i++;
	}
}
