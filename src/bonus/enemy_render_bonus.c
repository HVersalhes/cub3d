/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*enemy_texture(t_bonus *b, t_enemy *e)
{
	int	idx;

	if (e->state == ENEMY_ATTACK)
		idx = 4 + (e->frame % 2);
	else if (e->state == ENEMY_HURT)
		idx = ENEMY_HURT_TEX;
	else if (e->state == ENEMY_DIE)
	{
		idx = ENEMY_DIE_TEX + e->frame;
		if (idx >= ENEMY_FRAMES)
			idx = ENEMY_FRAMES - 1;
	}
	else
		idx = e->frame % 4;
	return (&b->enemy_tex[e->type][idx]);
}

static double	sprite_distance(t_game *game, t_enemy *e)
{
	double	dx;
	double	dy;

	dx = e->x - game->player.pos_x;
	dy = e->y - game->player.pos_y;
	return (dx * dx + dy * dy);
}

static void	fill_enemy_sprite(t_game *game, t_bonus *b, t_sprite *s,
		t_enemy *e)
{
	s->x = e->x;
	s->y = e->y;
	s->dist = sprite_distance(game, e);
	if (e->type == ENEMY_ZOMBIE)
	{
		s->height = 1.05;
		s->hp_max = ENEMY_ZOMBIE_HP;
	}
	else
	{
		s->height = 0.6;
		s->hp_max = ENEMY_SPIDER_HP;
	}
	s->center_z = s->height / 2.0;
	s->hp = e->hp;
	s->tex = enemy_texture(b, e);
}

/*
** Only enemies still on the field become sprites: a corpse keeps its
** alive flag while the death frames play and drops out right after
** them, so it leaves both the world and the minimap.
*/
void	bonus_append_enemy_sprites(t_game *game, int *n)
{
	t_bonus		*b;
	int			i;

	b = (t_bonus *)game->bonus;
	i = 0;
	while (i < b->enemy_count && *n < SPRITE_MAX)
	{
		if (b->enemies[i].alive)
		{
			fill_enemy_sprite(game, b, &b->draw_list[*n], &b->enemies[i]);
			(*n)++;
		}
		i++;
	}
}
