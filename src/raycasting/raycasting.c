/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:43:39 by hcuessec          #+#    #+#             */
/*   Updated: 2026/11/04 17:43:42 by hcuessec         ###   ########.fr       */
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
		calculate_wall_projection(game, &ray);
		draw_textured_wall_slice(game, &ray, x);
		x++;
	}
}
