/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_update_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:45:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bonus_update_sprites(t_bonus *b, double dt)
{
	if (b->sprite_count == 0)
		return ;
	b->sprite_timer += dt;
	if (b->sprite_timer < TORCH_FRAME_TIME)
		return ;
	b->sprite_timer -= TORCH_FRAME_TIME;
	b->sprite_frame = (b->sprite_frame + 1) % TORCH_FRAMES;
}
