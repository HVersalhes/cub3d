/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_grid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	bv_grid_setup(char **lines, t_bvgrid *g)
{
	int	i;

	i = 0;
	while (lines[i] && (!lines[i][0] || bv_key(lines[i])))
		i++;
	g->lines = lines;
	g->start = i;
	g->height = 0;
	while (lines[i + g->height])
		g->height++;
	g->width = 0;
	i = 0;
	while (i < g->height)
	{
		if ((int)ft_strlen(lines[g->start + i]) > g->width)
			g->width = ft_strlen(lines[g->start + i]);
		i++;
	}
	return (g->width >= 3 && g->height >= 3);
}

char	bonus_validate_tile(t_bvgrid *g, int x, int y)
{
	int	len;

	if (x < 0 || y < 0 || x >= g->width || y >= g->height)
		return (' ');
	len = ft_strlen(g->lines[g->start + y]);
	if (x >= len)
		return (' ');
	return (g->lines[g->start + y][x]);
}

const char	*bonus_validate_chars(t_bvgrid *g)
{
	int		players;
	int		x;
	int		y;
	char	c;

	players = 0;
	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			c = bonus_validate_tile(g, x, y);
			if (!ft_strchr(" 01NSEWDT", c))
				return ("Invalid character in map");
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				players++;
			x++;
		}
		y++;
	}
	if (players != 1)
		return ("Map must contain exactly one player");
	return (NULL);
}

const char	*bonus_validate_map(const char *path)
{
	t_bvgrid	g;
	const char	*err;
	char		**lines;

	lines = bv_collect_lines(path);
	if (!lines)
		return ("Cannot open .cub file");
	err = bonus_validate_header(lines);
	if (!err && !bv_grid_setup(lines, &g))
		err = "Map is too small or missing";
	if (!err)
		err = bonus_validate_chars(&g);
	if (!err)
		err = bonus_validate_closed(&g);
	free_tab(lines);
	return (err);
}
