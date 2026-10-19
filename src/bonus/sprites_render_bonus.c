/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:50:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *d, int x,
		int tex_x)
{
	int	y;
	int	tex_y;
	int	color;

	y = d->start_y;
	while (y < d->end_y)
	{
		tex_y = (y - d->start_y) * d->tex->height / d->height;
		color = get_texture_pixel(d->tex, tex_x, tex_y);
		if ((color & 0xFFFFFF) != SPRITE_MAGENTA)
			my_pixel_put(&game->frame, x, y, color);
		y++;
	}
}

static void	draw_sprite_columns(t_game *game, t_sprite_draw *d)
{
	int	x;
	int	tex_x;

	x = d->start_x;
	while (x < d->end_x)
	{
		if (x >= 0 && x < WIN_WIDTH && d->transform_y < game->z_buffer[x])
		{
			tex_x = (x - d->start_x) * d->tex->width / d->width;
			draw_sprite_stripe(game, d, x, tex_x);
		}
		x++;
	}
}

static void	compute_sprite_rect(t_sprite_draw *d, t_sprite *sprite)
{
	d->screen_x = (int)(WIN_WIDTH / 2.0
			* (1.0 + d->transform_x / d->transform_y));
	d->height = (int)(sprite->height * WIN_HEIGHT / d->transform_y);
	if (d->height < 1)
		d->height = 1;
	d->width = d->height * d->tex->width / d->tex->height;
	if (d->width < 1)
		d->width = 1;
	d->start_x = d->screen_x - d->width / 2;
	d->end_x = d->start_x + d->width;
	d->start_y = (int)(WIN_HEIGHT / 2.0 - (sprite->center_z - 0.5)
			* WIN_HEIGHT / d->transform_y) - d->height / 2;
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
	compute_sprite_rect(&d, sprite);
	draw_sprite_columns(game, &d);
	if (sprite->hp_max > 0 && sprite->hp > 0 && sprite->hp < sprite->hp_max)
		draw_sprite_hp(game, sprite, &d);
}
