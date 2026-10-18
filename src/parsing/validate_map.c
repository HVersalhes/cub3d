/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:11:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:11:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable_tile(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

static void	check_tile_enclosed(t_game *game, int y, int x)
{
	int	dy;
	int	dx;
	int	ny;
	int	nx;

	if (y == 0 || y == game->map.height - 1
		|| x == 0 || x == game->map.width - 1)
		error_exit("Map is not closed: walkable tile at boundary", game);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			ny = y + dy;
			nx = x + dx;
			if (game->map.grid[ny][nx] == ' '
				|| game->map.grid[ny][nx] == '\0')
				error_exit("Map is not closed: open space next to wall", game);
			dx++;
		}
		dy++;
	}
}

static void	check_player_spawn(t_game *game, int y, int x, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->map.player_count++;
		game->map.player_spawn_x = x;
		game->map.player_spawn_y = y;
		game->map.player_dir = c;
	}
}

static void	validate_tiles(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ' && c != 'D')
				error_exit("Invalid character found in map", game);
			check_player_spawn(game, y, x, c);
			if (is_walkable_tile(c))
				check_tile_enclosed(game, y, x);
			x++;
		}
		y++;
	}
}

void	validate_map(t_game *game)
{
	if (game->map.height < 3 || game->map.width < 3)
		error_exit("Map dimensions too small (minimum 3x3)", game);
	validate_tiles(game);
	if (game->map.player_count != 1)
		error_exit("Map must have exactly one player spawn (N, S, E, or W)",
			game);
}
