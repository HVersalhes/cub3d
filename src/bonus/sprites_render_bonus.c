/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:45:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:50:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	compute_sprite_rect(t_sprite_draw *d)
{
	d->screen_x = (int)((WIN_WIDTH / 2)
			* (1.0 + d->transform_x / d->transform_y));
	d->height = abs((int)(WIN_HEIGHT / d->transform_y));
	if (d->height < 1)
		d->height = 1;
	d->width = d->height;
	d->start_x = -d->width / 2 + d->screen_x;
	d->end_x = d->width / 2 + d->screen_x;
	d->start_y = -d->height / 2 + WIN_HEIGHT / 2;
	d->end_y = d->height / 2 + WIN_HEIGHT / 2;
	if (d->start_x < 0)
		d->start_x = 0;
	if (d->end_x > WIN_WIDTH)
		d->end_x = WIN_WIDTH;
	if (d->start_y < 0)
		d->start_y = 0;
	if (d->end_y > WIN_HEIGHT)
		d->end_y = WIN_HEIGHT;
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *d, int x,
		int tex_x)
{
	int	y;
	int	tex_y;
	int	color;

	y = d->start_y;
	while (y < d->end_y)
	{
		tex_y = (y - WIN_HEIGHT / 2 + d->height / 2)
			* d->tex->height / d->height;
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
		if (d->transform_y < game->z_buffer[x])
		{
			tex_x = (x - d->screen_x + d->width / 2)
				* d->tex->width / d->width;
			draw_sprite_stripe(game, d, x, tex_x);
		}
		x++;
	}
}

static void	draw_sprite(t_game *game, t_sprite *sprite, int frame)
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
	if (d.transform_y <= 0.1)
		return ;
	d.tex = &((t_bonus *)game->bonus)->sprite_tex[frame];
	compute_sprite_rect(&d);
	draw_sprite_columns(game, &d);
}

void	bonus_render_sprites(t_game *game)
{
	t_bonus	*b;
	int		i;

	if (!game->bonus)
		return ;
	b = (t_bonus *)game->bonus;
	if (b->sprite_count == 0)
		return ;
	bonus_sort_sprites(b, &game->player);
	i = 0;
	while (i < b->sprite_count)
	{
		draw_sprite(game, &b->sprites[i], b->sprite_frame);
		i++;
	}
}
