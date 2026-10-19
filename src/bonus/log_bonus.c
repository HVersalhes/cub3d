/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static const char	*key_label(int keycode)
{
	static const t_keylabel	table[] = {
	{KEY_W, "W"}, {KEY_A, "A"}, {KEY_S, "S"}, {KEY_D, "D"},
	{KEY_E, "E"}, {KEY_LEFT, "LEFT"}, {KEY_RIGHT, "RIGHT"},
	{KEY_UP, "UP"}, {KEY_DOWN, "DOWN"}, {KEY_ESC, "ESC"},
	{KEY_SPACE, "SPACE"}, {KEY_F, "F"}, {KEY_P, "P"},
	{KEY_M, "M"}, {KEY_R, "R"}, {KEY_Q, "Q"},
	{KEY_ENTER, "ENTER"}, {0, NULL}};
	int						i;

	i = 0;
	while (table[i].label)
	{
		if (table[i].code == keycode)
			return (table[i].label);
		i++;
	}
	return ("?");
}

void	bonus_log_key(int keycode)
{
	ft_printf("[input] key press: %s (%d)\n", key_label(keycode), keycode);
}

void	bonus_log_mouse(int button, int x, int y)
{
	ft_printf("[input] mouse button %d at %d,%d\n", button, x, y);
}

void	bonus_log_map_ok(const char *path)
{
	ft_printf("[map] valid map selected: %s\n", path);
}

void	bonus_log_map_err(const char *path, const char *err)
{
	if (!err)
		err = "unknown error";
	ft_printf("[map] error in %s: %s\n", path, err);
}
