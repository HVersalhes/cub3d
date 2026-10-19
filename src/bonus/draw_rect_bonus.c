/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_rect(t_img *img, t_rect r, int color)
{
	int	x;
	int	y;

	y = r.y;
	while (y < r.y + r.h)
	{
		if (y >= 0 && y < img->height)
		{
			x = r.x;
			while (x < r.x + r.w)
			{
				if (x >= 0 && x < img->width)
					my_pixel_put(img, x, y, color);
				x++;
			}
		}
		y++;
	}
}
