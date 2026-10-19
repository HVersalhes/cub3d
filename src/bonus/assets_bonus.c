/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static const char	*g_torch_paths[TORCH_FRAMES] = {
	"textures/bonus/torch1.xpm",
	"textures/bonus/torch2.xpm",
	"textures/bonus/torch3.xpm",
	"textures/bonus/torch4.xpm",
	"textures/bonus/torch5.xpm"
};

static const char	*g_spider_paths[ENEMY_FRAMES] = {
	"textures/bonus/spider_walk1.xpm",
	"textures/bonus/spider_walk2.xpm",
	"textures/bonus/spider_walk3.xpm",
	"textures/bonus/spider_walk4.xpm",
	"textures/bonus/spider_attack1.xpm",
	"textures/bonus/spider_attack2.xpm",
	"textures/bonus/spider_hurt.xpm",
	"textures/bonus/spider_die1.xpm",
	"textures/bonus/spider_die2.xpm",
	"textures/bonus/spider_die3.xpm"
};

static const char	*g_zombie_paths[ENEMY_FRAMES] = {
	"textures/bonus/zombie_walk1.xpm",
	"textures/bonus/zombie_walk2.xpm",
	"textures/bonus/zombie_walk3.xpm",
	"textures/bonus/zombie_walk4.xpm",
	"textures/bonus/zombie_attack1.xpm",
	"textures/bonus/zombie_attack2.xpm",
	"textures/bonus/zombie_hurt.xpm",
	"textures/bonus/zombie_die1.xpm",
	"textures/bonus/zombie_die2.xpm",
	"textures/bonus/zombie_die3.xpm"
};

static const char	*g_weapon_paths[WEAPON_FRAMES] = {
	"textures/bonus/hands_idle.xpm",
	"textures/bonus/hands_fire.xpm",
	"textures/bonus/hands_recoil.xpm"
};

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

static void	load_set(t_game *game, t_img *set, const char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		bonus_load_image(game, &set[i], paths[i]);
		i++;
	}
}

void	bonus_load_assets(t_game *game, t_bonus *b)
{
	load_set(game, b->torch_tex, g_torch_paths, TORCH_FRAMES);
	load_set(game, b->enemy_tex[0], g_spider_paths, ENEMY_FRAMES);
	load_set(game, b->enemy_tex[1], g_zombie_paths, ENEMY_FRAMES);
	load_set(game, b->weapon_tex, g_weapon_paths, WEAPON_FRAMES);
	bonus_load_image(game, &b->door_tex, "textures/bonus/door.xpm");
	bonus_load_image(game, &b->floor_tex, "textures/bonus/floor.xpm");
	bonus_load_image(game, &b->ceil_tex, "textures/bonus/ceiling.xpm");
}

static void	free_set(t_game *game, t_img *set, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (set[i].img_ptr && game->mlx_ptr)
			mlx_destroy_image(game->mlx_ptr, set[i].img_ptr);
		set[i].img_ptr = NULL;
		set[i].data_addr = NULL;
		i++;
	}
}

void	bonus_free_assets(t_game *game, t_bonus *b)
{
	free_set(game, b->torch_tex, TORCH_FRAMES);
	free_set(game, b->enemy_tex[0], ENEMY_FRAMES);
	free_set(game, b->enemy_tex[1], ENEMY_FRAMES);
	free_set(game, b->weapon_tex, WEAPON_FRAMES);
	free_set(game, &b->door_tex, 1);
	free_set(game, &b->floor_tex, 1);
	free_set(game, &b->ceil_tex, 1);
}
