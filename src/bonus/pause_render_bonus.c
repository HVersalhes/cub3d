/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	pause_button(t_game *game, int idx, int hover)
{
	t_rect	r;

	r.x = PAUSE_BTN_X;
	r.y = PAUSE_BTN_Y + idx * 90;
	r.w = PAUSE_BTN_W;
	r.h = PAUSE_BTN_H;
	draw_rect(&game->frame, r, 0x05080A);
	r.x += 3;
	r.y += 3;
	r.w -= 6;
	r.h -= 6;
	if (hover)
		draw_rect(&game->frame, r, 0x3A5A7C);
	else
		draw_rect(&game->frame, r, 0x1E2C3A);
}

void	bonus_render_pause(t_game *game)
{
	t_bonus	*b;
	t_rect	r;

	b = (t_bonus *)game->bonus;
	r.x = PAUSE_BTN_X - 60;
	r.y = PAUSE_BTN_Y - 120;
	r.w = PAUSE_BTN_W + 120;
	r.h = 400;
	draw_rect(&game->frame, r, 0x07090C);
	r.x = PAUSE_BTN_X - 54;
	r.y = PAUSE_BTN_Y - 114;
	r.w = PAUSE_BTN_W + 108;
	r.h = 388;
	draw_rect(&game->frame, r, 0x111A24);
	if (!b->menu_mode)
		return ;
	pause_button(game, 0, b->pause_hover == 0);
	pause_button(game, 1, b->pause_hover == 1);
	pause_button(game, 2, b->pause_hover == 2);
}

static void	pause_text_direct(t_game *game, char *title)
{
	mlx_string_put(game->mlx_ptr, game->win_ptr, 545, 240, 0xFFE8E8, title);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 470, 578, 0xC8DCEF,
		"ESC quits the game");
}

static void	pause_text_menu(t_game *game, char *title, char *first)
{
	mlx_string_put(game->mlx_ptr, game->win_ptr, 545, 240, 0xFFE8E8, title);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 553, PAUSE_BTN_Y + 36,
		0xFFFFFF, first);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 553, PAUSE_BTN_Y + 126,
		0xFFFFFF, "MAIN MENU (M)");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 553, PAUSE_BTN_Y + 216,
		0xFFFFFF, "QUIT (Q)");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 470, 578, 0xC8DCEF,
		"ESC or M returns to the main menu");
}

void	bonus_pause_text(t_game *game)
{
	t_bonus	*b;
	char	*title;
	char	*first;

	b = (t_bonus *)game->bonus;
	title = "PAUSE";
	first = "RESUME (P)";
	if (b->state == STATE_DEAD)
	{
		title = "YOU DIED";
		first = "RESTART (R)";
	}
	if (!b->menu_mode)
		pause_text_direct(game, title);
	else
		pause_text_menu(game, title, first);
}
