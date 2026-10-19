/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static unsigned int	pack_tint(unsigned int old, double dark, int tint)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(((old >> 16) & 0xFF) * (1.0 - dark)
			+ ((tint >> 16) & 0xFF) * dark);
	g = (unsigned int)(((old >> 8) & 0xFF) * (1.0 - dark)
			+ ((tint >> 8) & 0xFF) * dark);
	b = (unsigned int)((old & 0xFF) * (1.0 - dark)
			+ (tint & 0xFF) * dark);
	return ((r << 16) | (g << 8) | b);
}

void	bonus_tint_frame(t_game *game, double dark, int tint)
{
	char			*dst;
	unsigned int	old;
	int				i;

	if (!game->frame.data_addr)
		return ;
	dst = game->frame.data_addr;
	i = 0;
	while (i < game->frame.line_len * game->frame.height)
	{
		old = *(unsigned int *)(dst + i);
		*(unsigned int *)(dst + i) = pack_tint(old, dark, tint);
		i += game->frame.bpp / 8;
	}
}

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
	mlx_string_put(game->mlx_ptr, game->win_ptr, 20, 778, 0xC8DCEF,
		"WASD move | mouse look | LMB shoot | E door");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 20, 792, 0xC8DCEF,
		"F fullscreen | P pause");
}
