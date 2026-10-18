/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:06:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:06:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	if (map->grid)
	{
		free_tab(map->grid);
		map->grid = NULL;
	}
}

static void	free_mlx_resources(t_game *game)
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
	if (game->mlx_ptr && game->frame.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->frame.img_ptr);
	game->frame.img_ptr = NULL;
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	game->win_ptr = NULL;
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	if (game->z_buffer)
	{
		free(game->z_buffer);
		game->z_buffer = NULL;
	}
	free_mlx_resources(game);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
