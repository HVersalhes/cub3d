/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	playing_key(int keycode, t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b->menu_mode)
		return (0);
	if (keycode == KEY_P || keycode == KEY_ESC)
	{
		bonus_enter_overlay(game, STATE_PAUSED);
		return (1);
	}
	if (keycode == KEY_F)
	{
		bonus_toggle_fullscreen(game);
		return (1);
	}
	return (0);
}

static void	menu_key(t_game *game, int keycode)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		if (keycode == KEY_UP)
			b->menu.selected--;
		else
			b->menu.selected++;
		if (b->menu.selected < 0)
			b->menu.selected = b->menu.count - 1;
		if (b->menu.selected >= b->menu.count)
			b->menu.selected = 0;
	}
	else if (keycode == KEY_ENTER)
		bonus_load_selected(game);
	else if (keycode == KEY_F)
		bonus_toggle_fullscreen(game);
	else if (keycode == KEY_ESC)
		close_game(game);
}

int	bonus_key_press(int keycode, t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return (0);
	bonus_log_key(keycode);
	if (b->state == STATE_MENU)
	{
		menu_key(game, keycode);
		return (1);
	}
	if (b->state == STATE_PAUSED || b->state == STATE_DEAD)
	{
		bonus_pause_key(game, keycode);
		return (1);
	}
	return (playing_key(keycode, game));
}

int	bonus_mouse_hook(int x, int y, t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return (0);
	b->mouse_x = x;
	b->mouse_y = y;
	if (b->state == STATE_MENU)
	{
		b->menu.row_hover = bonus_menu_row_at(b, x, y);
		b->menu.btn_hover = bonus_menu_btn_at(b, x, y);
	}
	else if ((b->state == STATE_PAUSED || b->state == STATE_DEAD)
		&& b->menu_mode)
		b->pause_hover = bonus_pause_btn_at(game, x, y);
	return (0);
}

int	bonus_mouse_button(int button, int x, int y, t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return (0);
	bonus_log_mouse(button, x, y);
	if (b->state == STATE_PLAYING)
	{
		if (button == MOUSE_LEFT)
			bonus_fire_weapon(game);
	}
	else if (b->state == STATE_MENU)
		bonus_menu_click(game, x, y);
	else if (b->menu_mode)
		bonus_pause_click(game, x, y);
	return (0);
}
