/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcuessec <hcuessec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:44:10 by hcuessec          #+#    #+#             */
/*   Updated: 2026/11/04 18:41:32 by hcuessec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_key_state(bool *state, bool pressed, const char *action)
{
	if (*state == pressed)
		return ;
	*state = pressed;
	if (pressed)
		ft_printf("[cub3D] %s\n", action);
}

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		ft_printf("[cub3D] exit (ESC)\n");
		quit_game(game);
	}
	else if (keycode == KEY_W)
		update_key_state(&game->keys.w, true, "move forward");
	else if (keycode == KEY_S)
		update_key_state(&game->keys.s, true, "move backward");
	else if (keycode == KEY_A)
		update_key_state(&game->keys.a, true, "strafe left");
	else if (keycode == KEY_D)
		update_key_state(&game->keys.d, true, "strafe right");
	else if (keycode == KEY_LEFT)
		update_key_state(&game->keys.rot_left, true, "rotate left");
	else if (keycode == KEY_RIGHT)
		update_key_state(&game->keys.rot_right, true, "rotate right");
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		update_key_state(&game->keys.w, false, "move forward");
	else if (keycode == KEY_S)
		update_key_state(&game->keys.s, false, "move backward");
	else if (keycode == KEY_A)
		update_key_state(&game->keys.a, false, "strafe left");
	else if (keycode == KEY_D)
		update_key_state(&game->keys.d, false, "strafe right");
	else if (keycode == KEY_LEFT)
		update_key_state(&game->keys.rot_left, false, "rotate left");
	else if (keycode == KEY_RIGHT)
		update_key_state(&game->keys.rot_right, false, "rotate right");
	return (0);
}
