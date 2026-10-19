/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:24:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

void	render_frame(t_game *game)
{
	if (bonus_world_active(game))
	{
		if (!bonus_render_floor_ceiling(game))
			render_ceiling_floor(game);
		perform_raycasting(game);
	}
	bonus_render(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->frame.img_ptr, 0, 0);
	bonus_render_text(game);
}

int	game_loop(t_game *game)
{
	if (bonus_world_active(game))
		update_player_movement(game);
	bonus_update(game);
	render_frame(game);
	return (0);
}
