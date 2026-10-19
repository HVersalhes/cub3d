/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 02:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	mm_is_player(int x, int y)
{
	double	dx;
	double	dy;

	dx = (double)(x - MINIMAP_WIDTH / 2) / MINIMAP_SCALE;
	dy = (double)(MINIMAP_HEIGHT / 2 - y) / MINIMAP_SCALE;
	if (dy > 0.4667 || dy < -0.3333)
		return (0);
	if (dx < 0.0)
		dx = -dx;
	if (dx > (0.4667 - dy) * 0.4162)
		return (0);
	return (1);
}

static unsigned int	mm_tile_color(t_game *game, double wx, double wy)
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

static void	mm_blend(t_img *img, int offset, unsigned int color,
		double alpha)
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

static void	mm_put_sample(t_game *game, t_mm_view *view, int x, int y)
{
	double			lat;
	double			depth;
	unsigned int	packed;
	double			alpha;
	int				offset;

	if (mm_is_player(x, y))
	{
		my_pixel_put(&game->frame, MINIMAP_X + x, MINIMAP_Y + y,
			MM_COLOR_PLAYER);
		return ;
	}
	lat = (double)(x - MINIMAP_WIDTH / 2) / MINIMAP_SCALE;
	depth = (double)(MINIMAP_HEIGHT / 2 - y) / MINIMAP_SCALE;
	packed = mm_tile_color(game,
			game->player.pos_x + view->fx * depth + view->rx * lat,
			game->player.pos_y + view->fy * depth + view->ry * lat);
	if (packed == 0)
		return ;
	alpha = (double)((packed >> 24) & 0xFF) / 255.0;
	offset = (MINIMAP_Y + y) * game->frame.line_len;
	offset += (MINIMAP_X + x) * (game->frame.bpp / 8);
	mm_blend(&game->frame, offset, packed & 0xFFFFFF, alpha);
}

void	bonus_render_minimap(t_game *game)
{
	t_mm_view	view;
	double		plen;
	int			x;
	int			y;

	plen = sqrt(game->player.plane_x * game->player.plane_x
			+ game->player.plane_y * game->player.plane_y);
	view.fx = game->player.dir_x;
	view.fy = game->player.dir_y;
	view.rx = game->player.plane_x / plen;
	view.ry = game->player.plane_y / plen;
	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			mm_put_sample(game, &view, x, y);
			x++;
		}
		y++;
	}
}
