/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Chooses the texture that faces the player. A vertical wall hit while
** moving east shows its west face, and so on.
*/
int	get_wall_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (2);
		return (3);
	}
	if (ray->ray_dir_y > 0)
		return (0);
	return (1);
}

/*
** Finds where the ray hit the wall (0.0 = left edge, 1.0 = right edge)
** and converts that position into an X coordinate in the texture.
*/
static int	calculate_texture_x(t_game *game, t_ray *ray, t_img *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

/*
** Darkens the side walls a little so corners are easier to see. Each
** color channel is multiplied by 3/4.
*/
static int	shade_color(int color)
{
	int	red;
	int	green;
	int	blue;

	red = ((color >> 16) & 0xFF) * 3 / 4;
	green = ((color >> 8) & 0xFF) * 3 / 4;
	blue = (color & 0xFF) * 3 / 4;
	return ((red << 16) | (green << 8) | blue);
}

/*
** Draws one vertical slice. tex_pos is a floating-point position inside
** the texture; it advances by "step" for every screen pixel.
*/
static void	draw_column_pixels(t_game *game, t_ray *ray,
	t_img *texture, int x)
{
	double	step;
	double	tex_pos;
	int		tex_x;
	int		y;
	int		color;

	tex_x = calculate_texture_x(game, ray, texture);
	step = (double)texture->height / ray->line_height;
	tex_pos = (ray->draw_start - game->frame.height / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		color = *(unsigned int *)(texture->data_addr
				+ ((int)tex_pos % texture->height) * texture->line_len
				+ tex_x * (texture->bpp / 8));
		if (ray->side == 1)
			color = shade_color(color);
		my_pixel_put(&game->frame, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_textured_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img	*texture;

	texture = &game->textures[get_wall_texture_index(ray)];
	draw_column_pixels(game, ray, texture, x);
}
