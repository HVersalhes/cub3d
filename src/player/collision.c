/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:27:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:27:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_solid_cell(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	char	tile;

	if (x < 0.0 || y < 0.0)
		return (1);
	map_x = (int)x;
	map_y = (int)y;
	if (map_y >= game->map.height || map_x >= game->map.width)
		return (1);
	tile = game->map.grid[map_y][map_x];
	if (tile == '1' || tile == ' ' || tile == 'D')
		return (1);
	return (0);
}

int	is_valid_walk_position(t_game *game, double x, double y)
{
	double	margin;

	margin = 0.20;
	if (is_solid_cell(game, x - margin, y - margin))
		return (0);
	if (is_solid_cell(game, x + margin, y - margin))
		return (0);
	if (is_solid_cell(game, x - margin, y + margin))
		return (0);
	if (is_solid_cell(game, x + margin, y + margin))
		return (0);
	return (1);
}
