/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:45:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:45:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	load_sprite_texture(t_game *game, t_bonus *b, int i,
		const char *path)
{
	t_img	*img;

	img = &b->sprite_tex[i];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, (char *)path,
			&img->width, &img->height);
	if (!img->img_ptr)
		error_exit("Failed to load sprite texture", game);
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->data_addr)
		error_exit("Failed to get sprite texture data", game);
}

static int	count_sprites(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'T')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	fill_sprites(t_bonus *b, t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'T')
			{
				b->sprites[i].x = x + 0.5;
				b->sprites[i].y = y + 0.5;
				b->sprites[i].dist = 0.0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	bonus_init_sprites(t_game *game, t_bonus *b)
{
	b->sprite_count = count_sprites(game);
	if (b->sprite_count == 0)
		return ;
	load_sprite_texture(game, b, 0, "textures/sprite_torch1.xpm");
	load_sprite_texture(game, b, 1, "textures/sprite_torch2.xpm");
	load_sprite_texture(game, b, 2, "textures/sprite_torch3.xpm");
	load_sprite_texture(game, b, 3, "textures/sprite_torch4.xpm");
	b->sprites = ft_calloc(b->sprite_count, sizeof(t_sprite));
	if (!b->sprites)
		error_exit("Failed to allocate sprite state", game);
	fill_sprites(b, game);
}

void	bonus_free_sprites(t_game *game, t_bonus *b)
{
	int	i;

	i = 0;
	while (i < SPRITE_FRAMES)
	{
		if (game->mlx_ptr && b->sprite_tex[i].img_ptr)
			mlx_destroy_image(game->mlx_ptr, b->sprite_tex[i].img_ptr);
		b->sprite_tex[i].img_ptr = NULL;
		i++;
	}
	if (b->sprites)
		free(b->sprites);
	b->sprites = NULL;
}
