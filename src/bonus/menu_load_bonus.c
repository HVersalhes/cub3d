/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_load_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static void	free_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path)
			free(game->textures[i].path);
		game->textures[i].path = NULL;
		if (game->mlx_ptr && game->textures[i].img.img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->textures[i].img.img_ptr);
		game->textures[i].img.img_ptr = NULL;
		i++;
	}
}

void	bonus_unload_level(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	free_wall_textures(game);
	free_map(&game->map);
	ft_bzero(&game->map, sizeof(t_map));
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	if (!b)
		return ;
	if (b->doors)
		free(b->doors);
	b->doors = NULL;
	b->door_count = 0;
	bonus_free_sprites(game, b);
	b->enemy_count = 0;
	ft_bzero(b->enemies, sizeof(t_enemy) * ENEMY_MAX);
}

int	bonus_load_selected(t_game *game)
{
	t_bonus		*b;
	const char	*path;

	b = (t_bonus *)game->bonus;
	path = b->menu.paths[b->menu.selected];
	if (!b->menu.valid[b->menu.selected])
	{
		bonus_log_map_err(path, b->menu.errors[b->menu.selected]);
		return (0);
	}
	bonus_log_map_ok(path);
	bonus_unload_level(game);
	ft_printf("[cub3d] loading map: %s\n", path);
	parse_cub_file(path, game);
	init_player(game);
	init_textures(game);
	bonus_init_level(game, b);
	bonus_enter_overlay(game, STATE_PLAYING);
	return (1);
}

void	bonus_restart_level(t_game *game)
{
	bonus_load_selected(game);
}

void	bonus_back_to_menu(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (b && b->menu.count == 0)
		bonus_menu_init(b);
	bonus_unload_level(game);
	bonus_enter_overlay(game, STATE_MENU);
}
