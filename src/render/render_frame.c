/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:41:08 by hcuessec          #+#    #+#             */
/*   Updated: 2026/11/04 17:48:46 by hcuessec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *game)
{
	render_ceiling_floor(game);
	perform_raycasting(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->frame.img_ptr, 0, 0);
}

int	game_loop(t_game *game)
{
	update_player_movement(game);
	render_frame(game);
	return (0);
}
