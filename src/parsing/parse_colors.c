/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_spaces(char *str, int *index)
{
	while (str[*index] == ' ' || str[*index] == '\t')
		(*index)++;
}

static int	parse_channel(char *str, int *index)
{
	int	value;

	skip_spaces(str, index);
	if (!ft_isdigit(str[*index]))
		return (-1);
	value = 0;
	while (ft_isdigit(str[*index]))
	{
		value = value * 10 + (str[*index] - '0');
		if (value > 255)
			return (-1);
		(*index)++;
	}
	skip_spaces(str, index);
	return (value);
}

static int	parse_rgb_color(char *line)
{
	int	index;
	int	red;
	int	green;
	int	blue;

	index = 0;
	red = parse_channel(line, &index);
	if (red < 0 || line[index] != ',')
		return (-1);
	index++;
	green = parse_channel(line, &index);
	if (green < 0 || line[index] != ',')
		return (-1);
	index++;
	blue = parse_channel(line, &index);
	if (blue < 0)
		return (-1);
	skip_spaces(line, &index);
	if (line[index] != '\0' && line[index] != '\n' && line[index] != '\r')
		return (-1);
	return ((red << 16) | (green << 8) | blue);
}

static void	store_color(char type, char *line, t_game *game)
{
	int	color;

	color = parse_rgb_color(line);
	if (color < 0)
		error_exit("Invalid color format [0-255,0-255,0-255]", game);
	if (type == 'F')
	{
		if (game->map.floor_color != -1)
			error_exit("Duplicate floor color identifier", game);
		game->map.floor_color = color;
	}
	else
	{
		if (game->map.ceiling_color != -1)
			error_exit("Duplicate ceiling color identifier", game);
		game->map.ceiling_color = color;
	}
}

int	parse_color_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		store_color('F', line + i + 1, game);
		return (1);
	}
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		store_color('C', line + i + 1, game);
		return (1);
	}
	return (0);
}
