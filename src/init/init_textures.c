/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_texture(t_game *game, int idx, char *path)
{
	t_img	*img;

	img = &game->textures[idx].img;
	img->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->img_ptr)
		error_exit("Failed to load XPM texture image", game);
	img->data_addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->line_len, &img->endian);
	if (!img->data_addr)
		error_exit("Failed to get texture data address", game);
}

void	init_textures(t_game *game)
{
	load_single_texture(game, 0, game->map.no_path);
	load_single_texture(game, 1, game->map.so_path);
	load_single_texture(game, 2, game->map.we_path);
	load_single_texture(game, 3, game->map.ea_path);
}
