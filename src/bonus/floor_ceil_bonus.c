/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	fc_row_setup(t_game *game, t_fc_row *row, int y)
{
	double	rx0;
	double	ry0;
	double	rx1;
	double	ry1;

	row->dist = (0.5 * WIN_HEIGHT) / (y - WIN_HEIGHT / 2);
	rx0 = game->player.dir_x - game->player.plane_x;
	ry0 = game->player.dir_y - game->player.plane_y;
	rx1 = game->player.dir_x + game->player.plane_x;
	ry1 = game->player.dir_y + game->player.plane_y;
	row->step_x = row->dist * (rx1 - rx0) / WIN_WIDTH;
	row->step_y = row->dist * (ry1 - ry0) / WIN_WIDTH;
	row->fx = game->player.pos_x + row->dist * rx0;
	row->fy = game->player.pos_y + row->dist * ry0;
}

static void	fc_row_draw(t_game *game, t_fc_row *row, int y, t_img *tex)
{
	double	fx;
	double	fy;
	int		x;
	int		tx;
	int		ty;

	fx = row->fx;
	fy = row->fy;
	x = 0;
	while (x < WIN_WIDTH)
	{
		tx = (int)(tex->width * (fx - floor(fx)));
		ty = (int)(tex->height * (fy - floor(fy)));
		my_pixel_put(&game->frame, x, y, get_texture_pixel(tex, tx, ty));
		fx += row->step_x;
		fy += row->step_y;
		x++;
	}
}

int	bonus_render_floor_ceiling(t_game *game)
{
	t_bonus		*b;
	t_fc_row	row;
	int			y;

	b = (t_bonus *)game->bonus;
	if (!b || !b->floor_tex.img_ptr || !b->ceil_tex.img_ptr)
		return (0);
	y = WIN_HEIGHT / 2 + 1;
	while (y < WIN_HEIGHT)
	{
		fc_row_setup(game, &row, y);
		fc_row_draw(game, &row, y, &b->floor_tex);
		fc_row_draw(game, &row, WIN_HEIGHT - y, &b->ceil_tex);
		y++;
	}
	fc_row_setup(game, &row, WIN_HEIGHT / 2 + 1);
	fc_row_draw(game, &row, WIN_HEIGHT / 2, &b->ceil_tex);
	return (1);
}
