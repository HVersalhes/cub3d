/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 11:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	hud_bar(t_game *game, t_bonus *b)
{
	t_rect	r;

	r.x = 20;
	r.y = 20;
	r.w = 260;
	r.h = 26;
	draw_rect(&game->frame, r, 0x101418);
	r.x = 24;
	r.y = 24;
	r.w = 252 * b->health / PLAYER_HP;
	r.h = 18;
	if (b->health > 60)
		draw_rect(&game->frame, r, 0x35C759);
	else if (b->health > 30)
		draw_rect(&game->frame, r, 0xFFCC00);
	else
		draw_rect(&game->frame, r, 0xFF3B30);
}

/*
** Blends one scanline towards a tint colour with pure integer maths
** (weight 0..255).  Used for the damage flash and the pause/death
** darkening, so it must stay cheap even on a fullscreen framebuffer.
*/
static void	tint_row(unsigned int *row, int len, int k, int tint)
{
	unsigned int	old;
	int				r;
	int				g;
	int				b;
	int				i;

	i = 0;
	while (i < len)
	{
		old = row[i];
		r = (int)((old >> 16) & 0xFF);
		g = (int)((old >> 8) & 0xFF);
		b = (int)(old & 0xFF);
		r += (((((tint >> 16) & 0xFF) - r) * k) >> 8);
		g += (((((tint >> 8) & 0xFF) - g) * k) >> 8);
		b += ((((tint & 0xFF) - b) * k) >> 8);
		row[i] = (unsigned int)((r << 16) | (g << 8) | b);
		i++;
	}
}

void	bonus_tint_frame(t_game *game, double dark, int tint)
{
	unsigned int	*row;
	int				y;
	int				k;

	if (!game->frame.data_addr)
		return ;
	k = (int)(dark * 256.0);
	y = 0;
	while (y < game->frame.height)
	{
		row = (unsigned int *)(game->frame.data_addr
				+ (long)y * game->frame.line_len);
		tint_row(row, game->frame.line_len / 4, k, tint);
		y++;
	}
}

void	bonus_render_hud(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	hud_bar(game, b);
	if (b->damage_flash > 0.0)
		bonus_tint_frame(game, b->damage_flash * 0.35, 0xFF0000);
}

void	bonus_hud_text(t_game *game)
{
	t_bonus	*b;
	char	*num;

	b = (t_bonus *)game->bonus;
	num = ft_itoa(b->health);
	if (!num)
		return ;
	mlx_string_put(game->mlx_ptr, game->win_ptr, 30, 42, 0xFFFFFF, "HP");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 62, 42, 0xFFFFFF, num);
	free(num);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 20,
		game->frame.height - 22, 0xC8DCEF,
		"WASD move | mouse look | LMB shoot | E door");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 20,
		game->frame.height - 8, 0xC8DCEF,
		"F fullscreen | P pause");
}
