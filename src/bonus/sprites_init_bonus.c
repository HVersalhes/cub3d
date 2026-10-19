/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bonus_init_sprites(t_game *game, t_bonus *b)
{
	b->sprite_count = count_sprites(game);
	if (b->sprite_count == 0)
		return ;
	b->sprites = ft_calloc(b->sprite_count, sizeof(t_sprite));
	b->draw_list = ft_calloc(SPRITE_MAX, sizeof(t_sprite));
	if (!b->sprites || !b->draw_list)
		error_exit("Failed to allocate sprite state", game);
	fill_sprites(b, game);
}

void	bonus_free_sprites(t_game *game, t_bonus *b)
{
	(void)game;
	if (b->sprites)
		free(b->sprites);
	b->sprites = NULL;
	b->sprite_count = 0;
	if (b->draw_list)
		free(b->draw_list);
	b->draw_list = NULL;
	b->draw_count = 0;
}
