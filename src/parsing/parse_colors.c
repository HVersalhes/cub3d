/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:13:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_comma_count(const char *str)
{
	int	commas;
	int	i;

	commas = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	return (commas == 2);
}

static int	parse_single_channel(char *str, int *idx)
{
	int	val;
	int	has_digits;

	while (str[*idx] == ' ' || str[*idx] == '\t')
		(*idx)++;
	if (!ft_isdigit(str[*idx]))
		return (-1);
	val = 0;
	has_digits = 0;
	while (ft_isdigit(str[*idx]))
	{
		val = val * 10 + (str[*idx] - '0');
		if (val > 255)
			return (-1);
		has_digits = 1;
		(*idx)++;
	}
	while (str[*idx] == ' ' || str[*idx] == '\t')
		(*idx)++;
	if (!has_digits)
		return (-1);
	return (val);
}

static int	extract_rgb_color(char *line)
{
	int	idx;
	int	r;
	int	g;
	int	b;

	if (!validate_comma_count(line))
		return (-1);
	idx = 0;
	r = parse_single_channel(line, &idx);
	if (r < 0 || line[idx] != ',')
		return (-1);
	idx++;
	g = parse_single_channel(line, &idx);
	if (g < 0 || line[idx] != ',')
		return (-1);
	idx++;
	b = parse_single_channel(line, &idx);
	if (b < 0)
		return (-1);
	while (line[idx] == ' ' || line[idx] == '\t')
		idx++;
	if (line[idx] != '\0' && line[idx] != '\n' && line[idx] != '\r')
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	parse_floor_or_ceiling(char type, char *line, t_game *game)
{
	int	color;

	color = extract_rgb_color(line);
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
	return (1);
}

int	parse_color_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (parse_floor_or_ceiling('F', line + i + 1, game));
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (parse_floor_or_ceiling('C', line + i + 1, game));
	return (0);
}
