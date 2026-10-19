/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_closed_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	bv_enclosed(t_bvgrid *g, int x, int y)
{
	int		dx;
	int		dy;
	char	c;

	if (x == 0 || y == 0 || x == g->width - 1 || y == g->height - 1)
		return (0);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			c = bonus_validate_tile(g, x + dx, y + dy);
			if (c == ' ' || c == '\0')
				return (0);
			dx++;
		}
		dy++;
	}
	return (1);
}

const char	*bonus_validate_closed(t_bvgrid *g)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			c = bonus_validate_tile(g, x, y);
			if (c == '0' || c == 'D' || c == 'T'
				|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!bv_enclosed(g, x, y))
					return ("Map is not closed");
			}
			x++;
		}
		y++;
	}
	return (NULL);
}
