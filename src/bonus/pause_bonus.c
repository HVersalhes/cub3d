/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Geometry of the pause/death overlay, derived from the framebuffer
** size so the buttons stay centred after a fullscreen toggle.
*/
void	bonus_pause_btn_rect(t_game *game, int idx, t_rect *r)
{
	r->w = PAUSE_BTN_W;
	r->h = PAUSE_BTN_H;
	r->x = (game->frame.width - r->w) / 2;
	r->y = game->frame.height / 2 - 120 + idx * 90;
}

int	bonus_pause_btn_at(t_game *game, int x, int y)
{
	t_rect	r;
	int		idx;

	idx = 0;
	while (idx < 3)
	{
		bonus_pause_btn_rect(game, idx, &r);
		if (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h)
			return (idx);
		idx++;
	}
	return (-1);
}

void	bonus_pause_click(t_game *game, int x, int y)
{
	t_bonus	*b;
	int		btn;

	b = (t_bonus *)game->bonus;
	if (!b->menu_mode)
		return ;
	btn = bonus_pause_btn_at(game, x, y);
	if (btn == 0)
	{
		if (b->state == STATE_DEAD)
			bonus_restart_level(game);
		else
			bonus_enter_overlay(game, STATE_PLAYING);
	}
	else if (btn == 1)
		bonus_back_to_menu(game);
	else if (btn == 2)
		close_game(game);
}

static void	menu_pause_key(t_game *game, int keycode)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (keycode == KEY_M || keycode == KEY_ESC)
		bonus_back_to_menu(game);
	else if (keycode == KEY_R)
		bonus_restart_level(game);
	else if (keycode == KEY_Q)
		close_game(game);
	else if (keycode == KEY_F)
		bonus_toggle_fullscreen(game);
	else if (b->state == STATE_PAUSED && (keycode == KEY_P
			|| keycode == KEY_ENTER || keycode == KEY_SPACE))
		bonus_enter_overlay(game, STATE_PLAYING);
}

void	bonus_pause_key(t_game *game, int keycode)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b->menu_mode)
	{
		if (keycode == KEY_ESC)
			close_game(game);
		return ;
	}
	menu_pause_key(game, keycode);
}
