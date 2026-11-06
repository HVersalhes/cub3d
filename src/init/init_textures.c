/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, int index, char *path)
{
	t_img	*img;

	img = &game->textures[index];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->img_ptr)
		error_exit("Failed to load an XPM texture", game);
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->data_addr)
		error_exit("Failed to read an XPM texture address", game);
}

void	init_textures(t_game *game)
{
	load_texture(game, 0, game->map.no_path);
	load_texture(game, 1, game->map.so_path);
	load_texture(game, 2, game->map.we_path);
	load_texture(game, 3, game->map.ea_path);
}
