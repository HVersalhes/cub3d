/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	fc_tex_init(t_fc *f, t_img *tex)
{
	f->base = tex->data_addr;
	f->line = tex->line_len;
	f->px = tex->bpp >> 3;
	f->tw = tex->width;
	f->th = tex->height;
}

/*
** One scanline of the floor (or ceiling) plane.  The world position is
** kept in 16.16 fixed point and advanced with integer adds; the texel
** is then addressed with two integer multiplies.  No floor(), no double
** arithmetic and no per-pixel call in the inner loop.
*/
static void	fc_row_setup(t_game *game, t_fc *f, int y)
{
	double	dist;
	double	half;
	double	rx;
	double	ry;

	half = game->frame.height / 2.0;
	dist = half / (y - game->frame.height / 2);
	rx = game->player.dir_x - game->player.plane_x;
	ry = game->player.dir_y - game->player.plane_y;
	f->u = (int)((game->player.pos_x + dist * rx) * 65536.0);
	f->v = (int)((game->player.pos_y + dist * ry) * 65536.0);
	f->du = (int)(dist * 2.0 * game->player.plane_x
			* 65536.0 / game->frame.width);
	f->dv = (int)(dist * 2.0 * game->player.plane_y
			* 65536.0 / game->frame.width);
}

static void	fc_pixels(t_fc *f, t_game *game, int y, int w)
{
	unsigned int	*dst;
	int				u;
	int				v;
	int				i;

	dst = (unsigned int *)(game->frame.data_addr
			+ (long)y * game->frame.line_len);
	u = f->u;
	v = f->v;
	i = 0;
	while (i < w)
	{
		dst[i] = *(unsigned int *)(f->base + (((v & 0xFFFF) * f->th) >> 16)
				* f->line + (((u & 0xFFFF) * f->tw) >> 16) * f->px);
		u += f->du;
		v += f->dv;
		i++;
	}
}

int	bonus_render_floor_ceiling(t_game *game)
{
	t_bonus	*b;
	t_fc	floor;
	t_fc	ceil;
	int		y;

	b = (t_bonus *)game->bonus;
	if (!b || !b->floor_tex.img_ptr || !b->ceil_tex.img_ptr)
		return (0);
	fc_tex_init(&floor, &b->floor_tex);
	fc_tex_init(&ceil, &b->ceil_tex);
	y = game->frame.height / 2 + 1;
	while (y < game->frame.height)
	{
		fc_row_setup(game, &floor, y);
		fc_row_setup(game, &ceil, y);
		fc_pixels(&floor, game, y, game->frame.width);
		fc_pixels(&ceil, game, game->frame.height - y, game->frame.width);
		y++;
	}
	fc_row_setup(game, &ceil, game->frame.height / 2 + 1);
	fc_pixels(&ceil, game, game->frame.height / 2, game->frame.width);
	return (1);
}
