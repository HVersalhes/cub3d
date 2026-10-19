/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bonus_world_active(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	return (b && b->state == STATE_PLAYING);
}

void	bonus_render(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	if (b->state == STATE_MENU)
		bonus_render_menu(game);
	else if (b->state == STATE_PAUSED || b->state == STATE_DEAD)
		bonus_render_pause(game);
	else
	{
		bonus_render_sprites(game);
		bonus_render_weapon(game);
		bonus_render_hud(game);
		bonus_render_minimap(game);
	}
}

void	bonus_render_text(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	if (b->state == STATE_MENU)
		bonus_menu_text(game);
	else if (b->state == STATE_PAUSED || b->state == STATE_DEAD)
		bonus_pause_text(game);
	else
		bonus_hud_text(game);
}
