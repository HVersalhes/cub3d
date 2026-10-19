/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_enemy_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 11:40:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:40:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Radar blip: a small prism (diamond) with a dark outline and a blue
** core, so a spider reads as well over the dark floor as over a wall.
** Both diamonds are painted pixel by pixel, already clipped to the
** round radar by mm_plot.
*/
static void	mm_blip(t_game *game, int cx, int cy)
{
	int				size;
	int				dy;
	int				w;
	int				x;
	unsigned int	packed;

	size = 5;
	packed = MM_ENEMY_EDGE_PACKED;
	while (size >= 3)
	{
		dy = -(size / 2);
		while (dy <= size / 2)
		{
			w = size - 2 * (int)fabs((double)dy);
			x = -w / 2;
			while (x <= w / 2)
			{
				mm_plot(game, cx + x, cy + dy, packed);
				x++;
			}
			dy++;
		}
		size -= 2;
		packed = MM_ENEMY_PACKED;
	}
}

void	mm_enemies(t_game *game, t_mm_view *view)
{
	t_bonus	*b;
	t_enemy	*e;
	int		i;
	int		px;
	int		py;

	b = (t_bonus *)game->bonus;
	i = 0;
	while (i < b->enemy_count)
	{
		e = &b->enemies[i];
		if (e->alive && e->state != ENEMY_DIE)
		{
			px = (int)(((e->x - game->player.pos_x) * view->rx
						+ (e->y - game->player.pos_y) * view->ry)
					* MINIMAP_SCALE);
			py = (int)(((e->x - game->player.pos_x) * view->fx
						+ (e->y - game->player.pos_y) * view->fy)
					* MINIMAP_SCALE);
			mm_blip(game, MINIMAP_WIDTH / 2 + px,
				MINIMAP_HEIGHT / 2 - py);
		}
		i++;
	}
}
