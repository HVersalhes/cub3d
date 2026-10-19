/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	mm_outside(int x, int y)
{
	int	dx;
	int	dy;

	dx = x - MINIMAP_WIDTH / 2;
	dy = y - MINIMAP_HEIGHT / 2;
	return (dx * dx + dy * dy > (int)MM_RADIUS2);
}

/*
** Builds the radar basis once per frame: forward/right unit vectors,
** their increments for one pixel to the right and for one line down,
** plus the world position of the first pixel.  Every sample of the
** minimap is then just two adds.
*/
static void	mm_view_init(t_game *game, t_mm_view *view)
{
	double	plen;

	plen = sqrt(game->player.plane_x * game->player.plane_x
			+ game->player.plane_y * game->player.plane_y);
	view->fx = game->player.dir_x;
	view->fy = game->player.dir_y;
	view->rx = game->player.plane_x / plen;
	view->ry = game->player.plane_y / plen;
	view->sx = view->rx / MINIMAP_SCALE;
	view->sy = view->ry / MINIMAP_SCALE;
	view->gx = view->fx / MINIMAP_SCALE;
	view->gy = view->fy / MINIMAP_SCALE;
	view->wx0 = game->player.pos_x - view->sx * (MINIMAP_WIDTH / 2)
		+ view->gx * (MINIMAP_HEIGHT / 2);
	view->wy0 = game->player.pos_y - view->sy * (MINIMAP_WIDTH / 2)
		+ view->gy * (MINIMAP_HEIGHT / 2);
}

void	mm_plot(t_game *game, int x, int y, unsigned int packed)
{
	t_bonus	*b;

	if (packed == 0 || mm_outside(x, y))
		return ;
	b = (t_bonus *)game->bonus;
	mm_blend(&game->frame, (b->mm_y + y) * game->frame.line_len
		+ (b->mm_x + x) * 4, packed & 0xFFFFFF, (int)(packed >> 24));
}

static void	mm_row(t_game *game, t_mm_view *view, int y)
{
	double	wx;
	double	wy;
	int		x;

	wx = view->wx0;
	wy = view->wy0;
	x = 0;
	while (x < MINIMAP_WIDTH)
	{
		mm_plot(game, x, y, mm_tile_color(game, wx, wy));
		wx += view->sx;
		wy += view->sy;
		x++;
	}
}

void	bonus_render_minimap(t_game *game)
{
	t_bonus		*b;
	t_mm_view	view;
	int			y;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	b->mm_x = MINIMAP_MARGIN;
	b->mm_y = game->frame.height - MINIMAP_HEIGHT - MINIMAP_MARGIN;
	mm_view_init(game, &view);
	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		mm_row(game, &view, y);
		view.wx0 -= view.gx;
		view.wy0 -= view.gy;
		y++;
	}
	mm_enemies(game, &view);
	mm_player_marker(game);
	mm_ring(game);
}
