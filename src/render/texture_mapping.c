/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

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

/*
** Walks one clipped wall column.  The texture row is stepped in 16.16
** fixed point and every texel is written straight to the framebuffer
** memory: no per-pixel function call, no floating point, no bounds
** test (the column was already clipped by calculate_wall_projection).
** side == 1 columns are shaded to 3/4 with a mask/sub pair that keeps
** the three channels independent.
*/
static void	wall_col_run(t_wallcol *c)
{
	unsigned int	color;
	char			*col;
	int				tline;
	int				ty;

	col = c->tex + c->txoff;
	tline = c->tline;
	while (c->row < c->end)
	{
		ty = c->pos >> 16;
		if (c->hmask < 0)
			ty %= c->tex_h;
		else
			ty &= c->hmask;
		color = *(unsigned int *)(col + ty * tline);
		if (c->shade)
			color = (color & 0xFCFCFC) - ((color & 0xFCFCFC) >> 2);
		*(unsigned int *)c->row = color;
		c->row += c->line;
		c->pos += c->step;
	}
}

static void	draw_column_pixels(t_game *game, t_ray *ray, t_img *tex, int x)
{
	t_wallcol	c;

	c.tex = tex->data_addr;
	c.tline = tex->line_len;
	c.txoff = calculate_tex_x(game, ray, tex) * (tex->bpp >> 3);
	c.hmask = tex->height - 1;
	if ((tex->height & (tex->height - 1)) != 0)
		c.hmask = -1;
	c.tex_h = tex->height;
	c.line = game->frame.line_len;
	c.step = (tex->height << 16) / ray->line_height;
	c.pos = (ray->draw_start - game->frame.height / 2
			+ ray->line_height / 2) * c.step;
	c.row = game->frame.data_addr
		+ (long)ray->draw_start * game->frame.line_len
		+ (long)x * (game->frame.bpp >> 3);
	c.end = c.row + (long)(ray->draw_end - ray->draw_start + 1) * c.line;
	c.shade = (ray->side == 1);
	wall_col_run(&c);
}

void	draw_textured_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;

	tex = bonus_door_texture(game, ray);
	if (!tex)
		tex = &game->textures[get_wall_texture_index(ray)].img;
	draw_column_pixels(game, ray, tex, x);
}
