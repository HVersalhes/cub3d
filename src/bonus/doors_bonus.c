/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:20:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 01:20:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	load_door_texture(t_game *game, t_bonus *b)
{
	b->door_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/door.xpm", &b->door_tex.width, &b->door_tex.height);
	if (!b->door_tex.img_ptr)
		error_exit("Failed to load door texture", game);
	b->door_tex.data_addr = mlx_get_data_addr(b->door_tex.img_ptr,
			&b->door_tex.bpp, &b->door_tex.line_len, &b->door_tex.endian);
	if (!b->door_tex.data_addr)
		error_exit("Failed to get door texture data", game);
}

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
	load_door_texture(game, b);
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
