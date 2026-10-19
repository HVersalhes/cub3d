/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	menu_row_color(t_menu *m, int i)
{
	if (m->valid[i])
	{
		if (m->selected == i || m->row_hover == i)
			return (0x2E5B8A);
		return (0x1A2836);
	}
	if (m->selected == i || m->row_hover == i)
		return (0x8A3038);
	return (0x33202A);
}

static void	menu_button(t_game *game, t_menu *m, int idx)
{
	const int	cols[4] = {0x2E7D46, 0x3FA35C, 0x8A3038, 0xC84A52};
	t_rect		r;
	int			color;

	color = cols[idx * 2];
	if (m->btn_hover == idx)
		color = cols[idx * 2 + 1];
	r.x = MENU_BTN1_X + idx * (MENU_BTN2_X - MENU_BTN1_X);
	r.y = MENU_BTN_Y;
	r.w = MENU_BTN_W;
	r.h = MENU_BTN_H;
	draw_rect(&game->frame, r, 0x05080A);
	r.x += 3;
	r.y += 3;
	r.w -= 6;
	r.h -= 6;
	draw_rect(&game->frame, r, color);
}

static char	*menu_status(t_menu *m, int i)
{
	if (m->valid[i])
		return ("VALID");
	if (m->errors[i])
		return ("INVALID - see terminal");
	return ("INVALID");
}

void	bonus_render_menu(t_game *game)
{
	t_bonus	*b;
	t_rect	r;
	int		i;

	b = (t_bonus *)game->bonus;
	r.x = 0;
	r.y = 0;
	r.w = WIN_WIDTH;
	r.h = WIN_HEIGHT;
	draw_rect(&game->frame, r, 0x0B0F14);
	i = 0;
	while (i < b->menu.count)
	{
		r.x = MENU_ROW_X;
		r.y = MENU_ROW_Y + i * MENU_ROW_H;
		r.w = MENU_ROW_W;
		r.h = MENU_ROW_H - 6;
		draw_rect(&game->frame, r, menu_row_color(&b->menu, i));
		i++;
	}
	menu_button(game, &b->menu, 0);
	menu_button(game, &b->menu, 1);
}

void	bonus_menu_text(t_game *game)
{
	t_bonus	*b;
	int		i;
	int		col;

	b = (t_bonus *)game->bonus;
	mlx_string_put(game->mlx_ptr, game->win_ptr, 480, 100, 0xE8F1FF,
		"CUB3D ARENA");
	i = 0;
	while (i < b->menu.count)
	{
		mlx_string_put(game->mlx_ptr, game->win_ptr, MENU_ROW_X + 14,
			MENU_ROW_Y + i * MENU_ROW_H + 20, 0xFFFFFF,
			(char *)b->menu.paths[i]);
		col = 0xF08C8C;
		if (b->menu.valid[i])
			col = 0x8CF0A8;
		mlx_string_put(game->mlx_ptr, game->win_ptr, MENU_ROW_X + 520,
			MENU_ROW_Y + i * MENU_ROW_H + 20, col, menu_status(&b->menu, i));
		i++;
	}
	mlx_string_put(game->mlx_ptr, game->win_ptr, MENU_BTN1_X + 70,
		MENU_BTN_Y + 34, 0xFFFFFF, "PLAY");
	mlx_string_put(game->mlx_ptr, game->win_ptr, MENU_BTN2_X + 70,
		MENU_BTN_Y + 34, 0xFFFFFF, "QUIT");
}
