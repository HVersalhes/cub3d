/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Creates the connection with the X server, the window and the image
** used as the framebuffer. Rendering writes directly into that image
** and then asks MiniLibX to display it.
*/
void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_exit("Failed to initialize MiniLibX", game);
	mlx_do_key_autorepeatoff(game->mlx_ptr);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!game->win_ptr)
		error_exit("Failed to create the window", game);
	game->frame.img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img_ptr)
		error_exit("Failed to create the framebuffer", game);
	game->frame.data_addr = mlx_get_data_addr(game->frame.img_ptr,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	if (!game->frame.data_addr)
		error_exit("Failed to read the framebuffer address", game);
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
}
