/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:24:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->frame.width)
	{
		calculate_ray_vector(game, &ray, x);
		init_ray_step(game, &ray);
		execute_dda(game, &ray);
		calculate_wall_projection(game, &ray, x);
		draw_textured_wall_slice(game, &ray, x);
		x++;
	}
}
