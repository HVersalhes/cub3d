/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:10:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	size;

	size = MINIMAP_TILE * (2 * MINIMAP_RADIUS + 1);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_pixel_put(&game->frame, MINIMAP_X + x, MINIMAP_Y + y,
				MM_COLOR_BG);
			x++;
		}
		y++;
	}
}

static void	draw_tile_at(t_game *game, int dx, int dy, int color)
{
	int	sx;
	int	sy;
	int	x;
	int	y;

	sx = MINIMAP_X + (MINIMAP_RADIUS + dx) * MINIMAP_TILE;
	sy = MINIMAP_Y + (MINIMAP_RADIUS + dy) * MINIMAP_TILE;
	y = 0;
	while (y < MINIMAP_TILE - 1)
	{
		x = 0;
		while (x < MINIMAP_TILE - 1)
		{
			my_pixel_put(&game->frame, sx + x, sy + y, color);
			x++;
		}
		y++;
	}
}

static int	tile_color(t_game *game, int mx, int my)
{
	char	c;

	if (mx < 0 || my < 0 || mx >= game->map.width
		|| my >= game->map.height)
		return (MM_COLOR_BG);
	c = game->map.grid[my][mx];
	if (c == '1')
		return (MM_COLOR_WALL);
	if (c == 'D')
		return (MM_COLOR_DOOR);
	if (c == 'T')
		return (MM_COLOR_SPRITE);
	if (c == ' ')
		return (MM_COLOR_BG);
	return (MM_COLOR_FLOOR);
}

static void	draw_map_tiles(t_game *game)
{
	int	cx;
	int	cy;
	int	dx;
	int	dy;
	int	color;

	cx = (int)game->player.pos_x;
	cy = (int)game->player.pos_y;
	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		dx = -MINIMAP_RADIUS;
		while (dx <= MINIMAP_RADIUS)
		{
			color = tile_color(game, cx + dx, cy + dy);
			if (dx == 0 && dy == 0)
				color = MM_COLOR_PLAYER;
			draw_tile_at(game, dx, dy, color);
			dx++;
		}
		dy++;
	}
}

void	bonus_render_minimap(t_game *game)
{
	int	dx;
	int	cx;
	int	cy;

	draw_background(game);
	draw_map_tiles(game);
	cx = MINIMAP_X + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2;
	cy = MINIMAP_Y + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2;
	dx = 1;
	while (dx <= MINIMAP_TILE)
	{
		my_pixel_put(&game->frame, cx + (int)(game->player.dir_x * dx),
			cy + (int)(game->player.dir_y * dx), MM_COLOR_DIR);
		dx++;
	}
}
