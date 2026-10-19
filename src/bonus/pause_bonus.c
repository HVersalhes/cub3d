/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bonus_pause_btn_at(int x, int y)
{
	if (x < PAUSE_BTN_X || x > PAUSE_BTN_X + PAUSE_BTN_W)
		return (-1);
	if (y >= PAUSE_BTN_Y && y <= PAUSE_BTN_Y + PAUSE_BTN_H)
		return (0);
	if (y >= PAUSE_BTN_Y + 90 && y <= PAUSE_BTN_Y + 90 + PAUSE_BTN_H)
		return (1);
	if (y >= PAUSE_BTN_Y + 180 && y <= PAUSE_BTN_Y + 180 + PAUSE_BTN_H)
		return (2);
	return (-1);
}

void	bonus_pause_click(t_game *game, int x, int y)
{
	t_bonus	*b;
	int		btn;

	b = (t_bonus *)game->bonus;
	if (!b->menu_mode)
		return ;
	btn = bonus_pause_btn_at(x, y);
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
