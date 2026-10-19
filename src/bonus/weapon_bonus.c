/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
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

static void	weapon_blit(t_game *game, t_img *tex, t_rect d)
{
	int	dx;
	int	dy;
	int	color;

	dy = 0;
	while (dy < d.h)
	{
		dx = 0;
		while (dx < d.w)
		{
			color = get_texture_pixel(tex, dx * tex->width / d.w,
					dy * tex->height / d.h);
			if ((color & 0xFFFFFF) != SPRITE_MAGENTA)
				my_pixel_put(&game->frame, d.x + dx, d.y + dy, color);
			dx++;
		}
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
	d.w = WIN_WIDTH / 2;
	d.h = WIN_HEIGHT / 2;
	d.x = (WIN_WIDTH - d.w) / 2;
	d.y = WIN_HEIGHT - d.h + 40;
	weapon_blit(game, &b->weapon_tex[b->weapon.frame], d);
}
