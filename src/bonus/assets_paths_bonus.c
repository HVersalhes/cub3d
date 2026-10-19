/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_paths_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** Enemy animation sheets: the file names are not numbered end to end
** (walk, attack, hurt, die), so each set is listed once per loader in
** a local table instead of a global one.
*/
static void	load_spiders(t_game *game, t_bonus *b)
{
	const char	*paths[ENEMY_FRAMES];

	paths[0] = "textures/bonus/spider_walk1.xpm";
	paths[1] = "textures/bonus/spider_walk2.xpm";
	paths[2] = "textures/bonus/spider_walk3.xpm";
	paths[3] = "textures/bonus/spider_walk4.xpm";
	paths[4] = "textures/bonus/spider_attack1.xpm";
	paths[5] = "textures/bonus/spider_attack2.xpm";
	paths[6] = "textures/bonus/spider_hurt.xpm";
	paths[7] = "textures/bonus/spider_die1.xpm";
	paths[8] = "textures/bonus/spider_die2.xpm";
	paths[9] = "textures/bonus/spider_die3.xpm";
	bonus_load_set(game, b->enemy_tex[0], paths, ENEMY_FRAMES);
}

static void	load_zombies(t_game *game, t_bonus *b)
{
	const char	*paths[ENEMY_FRAMES];

	paths[0] = "textures/bonus/zombie_walk1.xpm";
	paths[1] = "textures/bonus/zombie_walk2.xpm";
	paths[2] = "textures/bonus/zombie_walk3.xpm";
	paths[3] = "textures/bonus/zombie_walk4.xpm";
	paths[4] = "textures/bonus/zombie_attack1.xpm";
	paths[5] = "textures/bonus/zombie_attack2.xpm";
	paths[6] = "textures/bonus/zombie_hurt.xpm";
	paths[7] = "textures/bonus/zombie_die1.xpm";
	paths[8] = "textures/bonus/zombie_die2.xpm";
	paths[9] = "textures/bonus/zombie_die3.xpm";
	bonus_load_set(game, b->enemy_tex[1], paths, ENEMY_FRAMES);
}

void	bonus_load_enemies(t_game *game, t_bonus *b)
{
	load_spiders(game, b);
	load_zombies(game, b);
}
