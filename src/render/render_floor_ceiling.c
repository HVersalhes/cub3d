/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:48:19 by hcuessec          #+#    #+#             */
/*   Updated: 2026/11/04 17:48:30 by hcuessec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*destination;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	destination = img->data_addr + y * img->line_len
		+ x * (img->bpp / 8);
	*(unsigned int *)destination = (unsigned int)color;
}

void	render_ceiling_floor(t_game *game)
{
	int	x;
	int	y;
	int	half_height;

	half_height = game->frame.height / 2;
	y = 0;
	while (y < game->frame.height)
	{
		x = 0;
		while (x < game->frame.width)
		{
			if (y < half_height)
				my_pixel_put(&game->frame, x, y,
					game->map.ceiling_color);
			else
				my_pixel_put(&game->frame, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}
