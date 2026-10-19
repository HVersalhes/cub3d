/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:20:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:20:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bonus_door_blocks(t_game *game, t_ray *ray)
{
	t_bonus	*b;
	int		idx;
	double	perp;
	double	hit;

	if (!game->bonus)
		return (1);
	b = (t_bonus *)game->bonus;
	idx = bonus_find_door(b, ray->map_x, ray->map_y);
	if (idx < 0 || b->doors[idx].openness <= 0.0)
		return (1);
	if (b->doors[idx].openness >= 1.0)
		return (0);
	if (ray->side == 0)
		perp = ray->side_dist_x - ray->delta_dist_x;
	else
		perp = ray->side_dist_y - ray->delta_dist_y;
	if (ray->side == 0)
		hit = game->player.pos_y + perp * ray->ray_dir_y;
	else
		hit = game->player.pos_x + perp * ray->ray_dir_x;
	hit -= floor(hit);
	return (hit < 1.0 - b->doors[idx].openness);
}

t_img	*bonus_door_texture(t_game *game, t_ray *ray)
{
	t_bonus	*b;
	int		idx;

	ray->tex_offset = 0;
	if (!ray->is_door || !game->bonus)
		return (NULL);
	b = (t_bonus *)game->bonus;
	idx = bonus_find_door(b, ray->map_x, ray->map_y);
	if (idx < 0)
		return (NULL);
	ray->tex_offset = (int)(b->doors[idx].openness * b->door_tex.width);
	return (&b->door_tex);
}
