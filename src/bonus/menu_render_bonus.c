/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Places every menu rectangle from the current framebuffer size, so the
** whole screen keeps working after a fullscreen toggle or a manual
** window resize.  Called on resize and once per rendered frame.
*/
void	menu_layout(t_bonus *b, int w, int h)
{
	t_menu	*m;

	m = &b->menu;
	m->row_w = MENU_ROW_W;
	m->row_h = MENU_ROW_H;
	m->row_x = (w - m->row_w) / 2;
	if (m->row_x < 20)
	{
		m->row_x = 20;
		m->row_w = w - 40;
	}
	m->row_y = (h - m->row_h * m->count) / 2 - 40;
	if (m->row_y < 120)
		m->row_y = 120;
	m->btn_y = h - MENU_BTN_H - 40;
	m->btn_x1 = w / 2 - MENU_BTN_W - 30;
	m->btn_x2 = w / 2 + 30;
}

static void	menu_button(t_game *game, t_menu *m, int idx)
{
	const int	cols[4] = {0x2E7D46, 0x3FA35C, 0x8A3038, 0xC84A52};
	t_rect		r;
	int			color;

	color = cols[idx * 2];
	if (m->btn_hover == idx)
		color = cols[idx * 2 + 1];
	r.x = m->btn_x1 + idx * (m->btn_x2 - m->btn_x1);
	r.y = m->btn_y;
	r.w = MENU_BTN_W;
	r.h = MENU_BTN_H;
	draw_rect(&game->frame, r, 0x05080A);
	r.x += 3;
	r.y += 3;
	r.w -= 6;
	r.h -= 6;
	draw_rect(&game->frame, r, color);
}

void	bonus_render_menu(t_game *game)
{
	t_bonus	*b;
	t_rect	r;
	int		i;

	b = (t_bonus *)game->bonus;
	menu_layout(b, game->frame.width, game->frame.height);
	r.x = 0;
	r.y = 0;
	r.w = game->frame.width;
	r.h = game->frame.height;
	draw_rect(&game->frame, r, 0x0B0F14);
	i = 0;
	while (i < b->menu.count)
	{
		r.x = b->menu.row_x;
		r.y = b->menu.row_y + i * b->menu.row_h;
		r.w = b->menu.row_w;
		r.h = b->menu.row_h - 6;
		draw_rect(&game->frame, r, menu_row_color(&b->menu, i));
		i++;
	}
	menu_button(game, &b->menu, 0);
	menu_button(game, &b->menu, 1);
}

void	bonus_menu_text(t_game *game)
{
	t_bonus	*b;
	char	*status;
	int		i;

	b = (t_bonus *)game->bonus;
	mlx_string_put(game->mlx_ptr, game->win_ptr, game->frame.width / 2 - 120,
		b->menu.row_y - 40, 0xE8F1FF, "CUB3D ARENA");
	i = 0;
	while (i < b->menu.count)
	{
		mlx_string_put(game->mlx_ptr, game->win_ptr, b->menu.row_x + 14,
			b->menu.row_y + i * b->menu.row_h + 20, 0xFFFFFF,
			(char *)b->menu.paths[i]);
		status = menu_status(&b->menu, i);
		mlx_string_put(game->mlx_ptr, game->win_ptr,
			b->menu.row_x + b->menu.row_w - 180,
			b->menu.row_y + i * b->menu.row_h + 20,
			menu_status_color(&b->menu, i), status);
		i++;
	}
	mlx_string_put(game->mlx_ptr, game->win_ptr, b->menu.btn_x1 + 70,
		b->menu.btn_y + 34, 0xFFFFFF, "PLAY");
	mlx_string_put(game->mlx_ptr, game->win_ptr, b->menu.btn_x2 + 70,
		b->menu.btn_y + 34, 0xFFFFFF, "QUIT");
}
