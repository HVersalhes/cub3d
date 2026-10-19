/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

void	bonus_update_weapon(t_game *game, double dt)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	if (b->weapon.cooldown > 0.0)
		b->weapon.cooldown -= dt;
	if (b->weapon.cooldown < 0.0)
		b->weapon.cooldown = 0.0;
	if (b->weapon.frame == 0)
		return ;
	b->weapon.timer -= dt;
	if (b->weapon.timer > 0.0)
		return ;
	if (b->weapon.frame == 1)
	{
		b->weapon.frame = 2;
		b->weapon.timer = 0.1;
	}
	else
		b->weapon.frame = 0;
}

void	bonus_fire_weapon(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b || b->state != STATE_PLAYING)
		return ;
	if (b->weapon.cooldown > 0.0)
		return ;
	ft_printf("[shot] fired\n");
	b->weapon.frame = 1;
	b->weapon.timer = WEAPON_FIRE_TIME;
	b->weapon.cooldown = WEAPON_COOLDOWN;
	bonus_hitscan(game);
}

/*
** Scales one weapon row: the source column is stepped in 16.16 fixed
** point and magenta texels are skipped (transparency key).
*/
static void	weapon_row(t_img *tex, char *src, unsigned int *dst, int w)
{
	int	pos;
	int	step;
	int	x;
	int	color;

	step = tex->width * 65536 / w;
	pos = 0;
	x = 0;
	while (x < w)
	{
		color = *(unsigned int *)(src + ((pos >> 16) * 4));
		if ((color & 0xFFFFFF) != SPRITE_MAGENTA)
			dst[x] = color;
		pos += step;
		x++;
	}
}

static void	weapon_blit(t_game *game, t_img *tex, t_rect d)
{
	char	*src;
	int		dy;
	int		end;

	end = d.y + d.h;
	if (end > game->frame.height)
		end = game->frame.height;
	dy = d.y;
	if (dy < 0)
		dy = 0;
	while (dy < end)
	{
		src = tex->data_addr
			+ (long)((dy - d.y) * tex->height / d.h) * tex->line_len;
		weapon_row(tex, src, (unsigned int *)(game->frame.data_addr
				+ (long)dy * game->frame.line_len) + d.x, d.w);
		dy++;
	}
}

void	bonus_render_weapon(t_game *game)
{
	t_bonus	*b;
	t_rect	d;

	b = (t_bonus *)game->bonus;
	if (!b || !b->weapon_tex[b->weapon.frame].img_ptr)
		return ;
	d.w = game->frame.width / 2;
	d.h = game->frame.height / 2;
	d.x = (game->frame.width - d.w) / 2;
	d.y = game->frame.height - d.h + game->frame.height / 20;
	weapon_blit(game, &b->weapon_tex[b->weapon.frame], d);
}
