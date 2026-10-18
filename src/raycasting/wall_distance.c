/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:24:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:24:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_wall_color(t_ray *ray)
{
	int	color;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			color = 0xFFFF00;
		else
			color = 0x0000FF;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			color = 0xFF0000;
		else
			color = 0x00FF00;
	}
	if (ray->side == 1)
		color = (((color >> 16) & 0xFF) * 3 / 4 << 16)
			| (((color >> 8) & 0xFF) * 3 / 4 << 8)
			| ((color & 0xFF) * 3 / 4);
	return (color);
}

static void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	color;

	color = get_wall_color(ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		my_pixel_put(&game->frame, x, y, color);
		y++;
	}
}

void	perform_raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_ray_vector(game, &ray, x);
		init_ray_step(game, &ray);
		execute_dda(game, &ray);
		calculate_wall_projection(game, &ray, x);
		draw_wall_slice(game, &ray, x);
		x++;
	}
}
