/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Draws one complete frame: background colors first, then the textured
** walls. Finally MiniLibX copies the framebuffer to the window.
*/
void	render_frame(t_game *game)
{
	render_ceiling_floor(game);
	perform_raycasting(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->frame.img_ptr, 0, 0);
}

/*
** Called by MiniLibX as often as possible. The player is moved before
** the new frame is rendered.
*/
int	game_loop(t_game *game)
{
	update_player_movement(game);
	render_frame(game);
	return (0);
}
