/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tile_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:30:00 by hcosta           ###   ########.fr       */
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

void	mm_blend(t_img *img, int offset, unsigned int color, int alpha)
{
	char			*dst;
	unsigned int	old;
	int				r;
	int				g;
	int				b;

	dst = img->data_addr + offset;
	old = *(unsigned int *)dst;
	r = (int)((old >> 16) & 0xFF);
	g = (int)((old >> 8) & 0xFF);
	b = (int)(old & 0xFF);
	r += ((((int)((color >> 16) & 0xFF) - r) * alpha) >> 8);
	g += ((((int)((color >> 8) & 0xFF) - g) * alpha) >> 8);
	b += ((((int)(color & 0xFF) - b) * alpha) >> 8);
	*(unsigned int *)dst = (unsigned int)((r << 16) | (g << 8) | b);
}

/*
** Half width of the round border on the scanline dy lines above the
** centre: floor(sqrt(radius^2 - dy^2)), zero when the row misses the
** circle.
*/
int	ring_edge(int radius_sq, int dy)
{
	if (radius_sq - dy * dy > 0)
		return ((int)sqrt(radius_sq - (double)dy * dy));
	return (0);
}

/*
** First pixel of the border on that scanline: ceil(sqrt(...)), so the
** hole in the middle keeps exactly the pixels the old per-pixel test
** left untouched.
*/
int	ring_inner(int radius_sq, int dy)
{
	int	i;

	if (radius_sq - dy * dy <= 0)
		return (0);
	i = (int)sqrt(radius_sq - (double)dy * dy);
	if (i * i < radius_sq - dy * dy)
		i++;
	return (i);
}
