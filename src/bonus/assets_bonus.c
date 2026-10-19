/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

void	bonus_load_image(t_game *game, t_img *img, const char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, (char *)path,
			&img->width, &img->height);
	if (!img->img_ptr)
	{
		ft_printf("[cub3d] missing texture: %s\n", path);
		error_exit("Failed to load bonus texture", game);
	}
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->data_addr)
		error_exit("Failed to get bonus texture data", game);
}

void	bonus_load_set(t_game *game, t_img *set, const char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		bonus_load_image(game, &set[i], paths[i]);
		i++;
	}
}

static void	load_torches(t_game *game, t_bonus *b)
{
	const char	*paths[TORCH_FRAMES];

	paths[0] = "textures/bonus/torch1.xpm";
	paths[1] = "textures/bonus/torch2.xpm";
	paths[2] = "textures/bonus/torch3.xpm";
	paths[3] = "textures/bonus/torch4.xpm";
	paths[4] = "textures/bonus/torch5.xpm";
	bonus_load_set(game, b->torch_tex, paths, TORCH_FRAMES);
}

static void	load_weapons(t_game *game, t_bonus *b)
{
	const char	*paths[WEAPON_FRAMES];

	paths[0] = "textures/bonus/hands_idle.xpm";
	paths[1] = "textures/bonus/hands_fire.xpm";
	paths[2] = "textures/bonus/hands_recoil.xpm";
	bonus_load_set(game, b->weapon_tex, paths, WEAPON_FRAMES);
}

void	bonus_load_assets(t_game *game, t_bonus *b)
{
	load_torches(game, b);
	load_weapons(game, b);
	bonus_load_enemies(game, b);
	bonus_load_image(game, &b->door_tex, "textures/bonus/door.xpm");
	bonus_load_image(game, &b->floor_tex, "textures/bonus/floor.xpm");
	bonus_load_image(game, &b->ceil_tex, "textures/bonus/ceiling.xpm");
}
