/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_list_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	build_draw_list(t_game *game, t_bonus *b)
{
	int	i;

	i = 0;
	while (i < b->sprite_count && i < SPRITE_MAX)
	{
		b->draw_list[i] = b->sprites[i];
		b->draw_list[i].tex = &b->torch_tex[b->sprite_frame];
		i++;
	}
	bonus_append_enemy_sprites(game, &i);
	return (i);
}

void	bonus_render_sprites(t_game *game)
{
	t_bonus	*b;
	int		i;

	if (!game->bonus)
		return ;
	b = (t_bonus *)game->bonus;
	b->draw_count = build_draw_list(game, b);
	if (b->draw_count == 0)
		return ;
	bonus_sort_sprites(b->draw_list, b->draw_count, &game->player);
	i = 0;
	while (i < b->draw_count)
	{
		draw_sprite(game, &b->draw_list[i]);
		i++;
	}
}
