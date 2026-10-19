/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:16:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:16:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

int	key_press_handler(int keycode, t_game *game)
{
	if (bonus_key_press(keycode, game))
		return (0);
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		game->keys.w = true;
	else if (keycode == KEY_S)
		game->keys.s = true;
	else if (keycode == KEY_A)
		game->keys.a = true;
	else if (keycode == KEY_D)
		game->keys.d = true;
	else if (keycode == KEY_LEFT)
		game->keys.rot_left = true;
	else if (keycode == KEY_RIGHT)
		game->keys.rot_right = true;
	else if (keycode == KEY_E || keycode == KEY_SPACE)
	{
		if (!game->keys.door_interact_held)
		{
			game->keys.door_interact = true;
			game->keys.door_interact_held = true;
		}
	}
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = false;
	else if (keycode == KEY_S)
		game->keys.s = false;
	else if (keycode == KEY_A)
		game->keys.a = false;
	else if (keycode == KEY_D)
		game->keys.d = false;
	else if (keycode == KEY_LEFT)
		game->keys.rot_left = false;
	else if (keycode == KEY_RIGHT)
		game->keys.rot_right = false;
	else if (keycode == KEY_E || keycode == KEY_SPACE)
		game->keys.door_interact_held = false;
	return (0);
}
