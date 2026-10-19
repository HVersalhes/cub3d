/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tile_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	mm_tile_color(t_game *game, double wx, double wy)
{
	char	c;
	int		mx;
	int		my;

	mx = (int)wx;
	my = (int)wy;
	if (mx < 0 || my < 0 || mx >= game->map.width
		|| my >= game->map.height)
		return (0);
	c = game->map.grid[my][mx];
	if (c == '1')
		return (MM_WALL_PACKED);
	if (c == 'D')
		return (MM_DOOR_PACKED);
	if (c == 'T')
		return (MM_SPRITE_PACKED);
	if (c == ' ')
		return (0);
	return (MM_FLOOR_PACKED);
}

void	mm_blend(t_img *img, int offset, unsigned int color, double alpha)
{
	char			*dst;
	unsigned int	old;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	dst = img->data_addr + offset;
	old = *(unsigned int *)dst;
	r = (unsigned int)(((color >> 16) & 0xFF) * alpha);
	r += (unsigned int)(((old >> 16) & 0xFF) * (1.0 - alpha));
	g = (unsigned int)(((color >> 8) & 0xFF) * alpha);
	g += (unsigned int)(((old >> 8) & 0xFF) * (1.0 - alpha));
	b = (unsigned int)((color & 0xFF) * alpha);
	b += (unsigned int)((old & 0xFF) * (1.0 - alpha));
	*(unsigned int *)dst = (r << 16) | (g << 8) | b;
}

void	mm_ring(t_game *game)
{
	int	x;
	int	y;
	int	d2;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			d2 = (x - MINIMAP_WIDTH / 2) * (x - MINIMAP_WIDTH / 2)
				+ (y - MINIMAP_HEIGHT / 2) * (y - MINIMAP_HEIGHT / 2);
			if (d2 <= (int)MM_RADIUS2 && d2 >= (int)MM_RADIUS_IN2)
				my_pixel_put(&game->frame, MINIMAP_X + x, MINIMAP_Y + y,
					MM_COLOR_RING);
			x++;
		}
		y++;
	}
}
