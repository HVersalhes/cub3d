/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ring_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	mm_span(t_game *game, int x, int y, int len)
{
	t_rect	r;

	r.x = x;
	r.y = y;
	r.w = len;
	r.h = 1;
	img_fill(&game->frame, r, MM_COLOR_RING);
}

/*
** The round border is an annulus, so every scanline holds two
** symmetric spans: painting them with img_fill replaces the previous
** per-pixel test of the whole minimap box.
*/
void	mm_ring(t_game *game)
{
	t_bonus	*b;
	int		dy;
	int		outer;
	int		inner;

	b = (t_bonus *)game->bonus;
	dy = -MINIMAP_HEIGHT / 2;
	while (dy < MINIMAP_HEIGHT / 2)
	{
		if ((int)MM_RADIUS2 - dy * dy >= 0)
		{
			inner = ring_inner((int)MM_RADIUS_IN2, dy);
			outer = ring_edge((int)MM_RADIUS2, dy);
			mm_span(game, b->mm_x + MINIMAP_WIDTH / 2 - outer,
				b->mm_y + MINIMAP_HEIGHT / 2 + dy, outer - inner + 1);
			mm_span(game, b->mm_x + MINIMAP_WIDTH / 2 + inner,
				b->mm_y + MINIMAP_HEIGHT / 2 + dy, outer - inner + 1);
		}
		dy++;
	}
}

/*
** Player arrow: apex 7 pixels above the centre, base 5 pixels below,
** drawn as one span per row instead of one test per minimap pixel.
*/
void	mm_player_marker(t_game *game)
{
	t_bonus	*b;
	t_rect	r;
	int		k;

	b = (t_bonus *)game->bonus;
	k = 7;
	r.h = 1;
	while (k >= -5)
	{
		r.w = ((7 - k) * 4162 / 10000) * 2 + 1;
		r.x = b->mm_x + MINIMAP_WIDTH / 2 - ((7 - k) * 4162 / 10000);
		r.y = b->mm_y + MINIMAP_HEIGHT / 2 - k;
		img_fill(&game->frame, r, MM_COLOR_PLAYER);
		k--;
	}
}
