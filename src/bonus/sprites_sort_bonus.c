/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:50:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	sprite_dist(t_sprite *sprite, t_player *player)
{
	double	dx;
	double	dy;

	dx = sprite->x - player->pos_x;
	dy = sprite->y - player->pos_y;
	return (dx * dx + dy * dy);
}

void	bonus_sort_sprites(t_sprite *list, int count, t_player *p)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < count)
	{
		list[i].dist = sprite_dist(&list[i], p);
		i++;
	}
	i = 1;
	while (i < count)
	{
		tmp = list[i];
		j = i - 1;
		while (j >= 0 && list[j].dist < tmp.dist)
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = tmp;
		i++;
	}
}
