/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_free_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_set(t_game *game, t_img *set, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (set[i].img_ptr && game->mlx_ptr)
			mlx_destroy_image(game->mlx_ptr, set[i].img_ptr);
		set[i].img_ptr = NULL;
		set[i].data_addr = NULL;
		i++;
	}
}

void	bonus_free_assets(t_game *game, t_bonus *b)
{
	free_set(game, b->torch_tex, TORCH_FRAMES);
	free_set(game, b->enemy_tex[0], ENEMY_FRAMES);
	free_set(game, b->enemy_tex[1], ENEMY_FRAMES);
	free_set(game, b->weapon_tex, WEAPON_FRAMES);
	free_set(game, &b->door_tex, 1);
	free_set(game, &b->floor_tex, 1);
	free_set(game, &b->ceil_tex, 1);
}
