/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:16:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_exit("Failed to initialize MiniLibX", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "cub3D - Maze Runner");
	if (!game->win_ptr)
		error_exit("Failed to create MiniLibX window", game);
	game->frame.img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img_ptr)
		error_exit("Failed to allocate main framebuffer image", game);
	game->frame.data_addr = mlx_get_data_addr(game->frame.img_ptr,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	game->z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	if (!game->z_buffer)
		error_exit("Failed to allocate z-buffer", game);
	return (1);
}
