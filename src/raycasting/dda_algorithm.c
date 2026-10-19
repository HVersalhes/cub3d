/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:24:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:24:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

static int	check_ray_hit(t_game *game, t_ray *ray)
{
	char	tile;

	tile = game->map.grid[ray->map_y][ray->map_x];
	if (tile == '1')
		return (1);
	if (tile == 'D' && bonus_door_blocks(game, ray))
	{
		ray->is_door = 1;
		return (1);
	}
	return (0);
}

void	execute_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.height
			|| ray->map_x < 0 || ray->map_x >= game->map.width)
			break ;
		if (check_ray_hit(game, ray))
			ray->hit = 1;
	}
}

void	calculate_wall_projection(t_game *game, t_ray *ray, int x)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
	game->z_buffer[x] = ray->perp_wall_dist;
	ray->line_height = (int)(game->frame.height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->frame.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->frame.height / 2;
	if (ray->draw_end >= game->frame.height)
		ray->draw_end = game->frame.height - 1;
}
