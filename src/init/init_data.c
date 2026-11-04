/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:07:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/04 17:47:50 by hcuessec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_data(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	game->map.player_spawn_x = -1;
	game->map.player_spawn_y = -1;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
}
