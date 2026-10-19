/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_ray_bonus.c                                   :+:      :+:    :+:   */
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
	(void)game;
	(void)ray;
	return (1);
}

t_img	*bonus_door_texture(t_game *game, t_ray *ray)
{
	(void)game;
	ray->tex_offset = 0;
	return (NULL);
}
