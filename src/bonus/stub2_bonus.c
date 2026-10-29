/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bonus_menu_mode(t_game *game, const char *arg)
{
	(void)game;
	(void)arg;
	return (0);
}

int	bonus_world_active(t_game *game)
{
	(void)game;
	return (1);
}

int	bonus_render_floor_ceiling(t_game *game)
{
	(void)game;
	return (0);
}

void	bonus_render_text(t_game *game)
{
	(void)game;
}

int	bonus_mouse_hook(int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	(void)game;
	return (0);
}
