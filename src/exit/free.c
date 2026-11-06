/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:06:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_map(t_map *map)
{
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

/*
** Destroys the images, the window, the display connection and finally
** the MiniLibX context itself.
*/
static void	free_mlx_resources(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->mlx_ptr && game->textures[i].img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->textures[i].img_ptr);
		game->textures[i].img_ptr = NULL;
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
		mlx_do_key_autorepeaton(game->mlx_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

/*
** Releases every allocation owned by the game. It is safe to call this
** function more than once because all pointers are set to NULL after
** they are freed.
*/
void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map_fd >= 0)
	{
		close(game->map_fd);
		game->map_fd = -1;
	}
	get_next_line(-1);
	free_map(&game->map);
	if (game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
	free_mlx_resources(game);
}

int	close_game(t_game *game)
{
	ft_printf("[cub3D] exit (X)\n");
	quit_game(game);
	return (0);
}
