/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:45:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_wall(t_game *game, int x, int y)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (0);
	c = game->map.grid[y][x];
	return (c == '1' || c == 'D');
}

int	count_sprites(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'T')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	torch_defaults(t_sprite *s, int x, int y)
{
	s->x = x + 0.5;
	s->y = y + 0.5;
	s->dist = 0.0;
	s->height = 0.75;
	s->center_z = 0.375;
	s->tex = NULL;
}

static void	offset_torch(t_game *game, t_sprite *s, int x, int y)
{
	if (is_wall(game, x - 1, y))
		s->x -= 0.34;
	else if (is_wall(game, x + 1, y))
		s->x += 0.34;
	else if (is_wall(game, x, y - 1))
		s->y -= 0.34;
	else if (is_wall(game, x, y + 1))
		s->y += 0.34;
}

void	fill_sprites(t_bonus *b, t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'T')
			{
				torch_defaults(&b->sprites[i], x, y);
				offset_torch(game, &b->sprites[i], x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}
