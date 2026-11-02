/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Writes one pixel in the framebuffer. The address of a pixel is:
** data_addr + y * line_len + x * (bits_per_pixel / 8).
*/
void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*destination;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	destination = img->data_addr + y * img->line_len
		+ x * (img->bpp / 8);
	*(unsigned int *)destination = (unsigned int)color;
}

/*
** The top half of the screen is the ceiling and the bottom half is the
** floor. Walls are drawn later on top of these colors.
*/
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
