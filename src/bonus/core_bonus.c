/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:10:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bonus_init(t_game *game)
{
	t_bonus	*b;

	b = ft_calloc(1, sizeof(t_bonus));
	if (!b)
		error_exit("Failed to allocate bonus state", game);
	b->initialized = 1;
	game->bonus = b;
}

void	bonus_update(t_game *game)
{
	(void)game;
}

void	bonus_render(t_game *game)
{
	bonus_render_minimap(game);
}

void	bonus_free(t_game *game)
{
	if (!game->bonus)
		return ;
	free(game->bonus);
	game->bonus = NULL;
}
