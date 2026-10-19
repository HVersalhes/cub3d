/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:31:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	src = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}

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

static int	calculate_tex_x(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	tex_x += ray->tex_offset;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_column_pixels(t_game *game, t_ray *ray, t_img *tex, int x)
{
	double	step;
	double	tex_pos;
	int		tex_x;
	int		y;
	int		color;

	tex_x = calculate_tex_x(game, ray, tex);
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		color = get_texture_pixel(tex, tex_x, (int)tex_pos & (tex->height - 1));
		if (ray->side == 1)
			color = (((color >> 16) & 0xFF) * 3 / 4 << 16)
				| (((color >> 8) & 0xFF) * 3 / 4 << 8)
				| ((color & 0xFF) * 3 / 4);
		my_pixel_put(&game->frame, x, y++, color);
		tex_pos += step;
	}
}

void	draw_textured_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;

	tex = bonus_door_texture(game, ray);
	if (!tex)
		tex = &game->textures[get_wall_texture_index(ray)].img;
	draw_column_pixels(game, ray, tex, x);
}
