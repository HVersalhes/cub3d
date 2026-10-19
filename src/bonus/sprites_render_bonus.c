/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:50:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** One sprite stripe.  The texture row is stepped in 16.16 fixed point
** and written directly to the framebuffer; magenta pixels are left
** untouched (transparency key).  Both loops are already clipped.
*/
static void	draw_sprite_stripe(t_game *game, t_sprite_draw *d, int x,
		int tex_x)
{
	char	*src;
	char	*dst;
	int		pos;
	int		color;

	src = d->tex->data_addr + (long)tex_x * (d->tex->bpp >> 3);
	dst = game->frame.data_addr + (long)d->start_y * game->frame.line_len
		+ (long)x * (game->frame.bpp >> 3);
	pos = d->ty0;
	while (dst < d->dst_end)
	{
		color = *(unsigned int *)(src + (pos >> 16) * d->tex->line_len);
		if ((color & 0xFFFFFF) != SPRITE_MAGENTA)
			*(unsigned int *)dst = color;
		pos += d->ty_step;
		dst += game->frame.line_len;
	}
}

static void	draw_sprite_columns(t_game *game, t_sprite_draw *d)
{
	int	x;
	int	tex_x;

	d->ty_step = (d->tex->height << 16) / d->height;
	d->ty0 = 0;
	if (d->start_y < 0)
	{
		d->ty0 = -d->start_y * d->ty_step;
		d->start_y = 0;
	}
	if (d->end_y > game->frame.height)
		d->end_y = game->frame.height;
	d->dst_end = game->frame.data_addr
		+ (long)d->end_y * game->frame.line_len;
	x = d->start_x;
	while (x < d->end_x)
	{
		if (x >= 0 && x < game->frame.width
			&& d->transform_y < game->z_buffer[x])
		{
			tex_x = (x - d->start_x) * d->tex->width / d->width;
			draw_sprite_stripe(game, d, x, tex_x);
		}
		x++;
	}
}

static void	compute_sprite_rect(t_sprite_draw *d, t_sprite *sprite,
		t_game *game)
{
	d->screen_x = (int)(game->frame.width / 2.0
			* (1.0 + d->transform_x / d->transform_y));
	d->height = (int)(game->frame.height / d->transform_y);
	if (d->height < 1)
		d->height = 1;
	d->width = d->height * d->tex->width / d->tex->height;
	if (d->width < 1)
		d->width = 1;
	d->start_x = d->screen_x - d->width / 2;
	d->end_x = d->start_x + d->width;
	d->start_y = (int)(game->frame.height / 2.0 - (sprite->center_z - 0.5)
			* game->frame.height / d->transform_y) - d->height / 2;
	d->end_y = d->start_y + d->height;
}

static void	draw_sprite_hp(t_game *game, t_sprite *sprite, t_sprite_draw *d)
{
	t_rect	r;
	int		bar_w;

	bar_w = d->width / 2;
	if (bar_w < 14)
		bar_w = 14;
	if (bar_w > 120)
		bar_w = 120;
	r.x = d->start_x + (d->width - bar_w) / 2;
	r.y = d->start_y - 9;
	r.w = bar_w;
	r.h = 5;
	draw_rect(&game->frame, r, MM_HP_BAR_BG);
	r.x += 1;
	r.y += 1;
	r.w = (bar_w - 2) * sprite->hp / sprite->hp_max;
	if (r.w < 1)
		r.w = 1;
	r.h = 3;
	draw_rect(&game->frame, r, MM_HP_BAR_FILL);
}

void	draw_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_draw	d;
	double			sx;
	double			sy;
	double			inv_det;

	sx = sprite->x - game->player.pos_x;
	sy = sprite->y - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	d.transform_x = inv_det * (game->player.dir_y * sx
			- game->player.dir_x * sy);
	d.transform_y = inv_det * (-game->player.plane_y * sx
			+ game->player.plane_x * sy);
	if (d.transform_y <= 0.15 || !sprite->tex || !sprite->tex->img_ptr)
		return ;
	d.tex = sprite->tex;
	compute_sprite_rect(&d, sprite, game);
	draw_sprite_columns(game, &d);
	if (sprite->hp_max > 0 && sprite->hp > 0 && sprite->hp < sprite->hp_max)
		draw_sprite_hp(game, sprite, &d);
}
