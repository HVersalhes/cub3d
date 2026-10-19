/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 11:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:40:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	src = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}

/*
** One clipped horizontal span of a solid colour.  Every MiniLibX image
** on this platform is 32bpp (four bytes per pixel), so two pixels are
** written with a single 64-bit store.
*/
static void	fill_row(t_img *img, t_rect r, int color)
{
	unsigned long long	pair;
	unsigned int		*px;
	unsigned int		col;
	int					i;

	if (r.y < 0 || r.y >= img->height || (img->bpp >> 3) != 4)
		return ;
	px = (unsigned int *)(img->data_addr + (long)r.y * img->line_len
			+ (long)r.x * 4);
	col = (unsigned int)color;
	pair = ((unsigned long long)col << 32) | col;
	i = 0;
	while (i + 2 <= r.w)
	{
		*(unsigned long long *)(px + i) = pair;
		i += 2;
	}
	if (i < r.w)
		px[i] = col;
}

void	img_fill(t_img *img, t_rect r, int color)
{
	int	y;
	int	end;

	if (r.x < 0)
	{
		r.w += r.x;
		r.x = 0;
	}
	if (r.x + r.w > img->width)
		r.w = img->width - r.x;
	end = r.y + r.h;
	y = r.y;
	if (y < 0)
		y = 0;
	if (end > img->height)
		end = img->height;
	while (y < end && r.w > 0)
	{
		r.y = y;
		fill_row(img, r, color);
		y++;
	}
}
