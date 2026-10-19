/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:20:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	count_doors(t_game *game)
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
			if (game->map.grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	fill_doors(t_game *game, t_bonus *b)
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
			if (game->map.grid[y][x] == 'D')
			{
				b->doors[i].x = x;
				b->doors[i].y = y;
				b->doors[i].state = DOOR_CLOSED;
				b->doors[i].openness = 0.0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	bonus_init_doors(t_game *game, t_bonus *b)
{
	b->door_count = count_doors(game);
	if (b->door_count == 0)
		return ;
	b->doors = ft_calloc(b->door_count, sizeof(t_door));
	if (!b->doors)
		error_exit("Failed to allocate door state", game);
	fill_doors(game, b);
}

int	bonus_find_door(t_bonus *b, int x, int y)
{
	int	i;

	i = 0;
	while (i < b->door_count)
	{
		if (b->doors[i].x == x && b->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

int	bonus_door_solid(t_game *game, int x, int y)
{
	t_bonus	*b;
	int		idx;

	if (!game->bonus)
		return (1);
	b = (t_bonus *)game->bonus;
	idx = bonus_find_door(b, x, y);
	if (idx < 0)
		return (0);
	return (b->doors[idx].openness < 0.5);
}
