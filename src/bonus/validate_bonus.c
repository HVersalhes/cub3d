/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bv_key(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (4);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (8);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (16);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (32);
	return (0);
}

static int	bv_tex(char *path)
{
	int	fd;

	while (*path == ' ' || *path == '\t')
		path++;
	if (!*path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	bv_color(char *s)
{
	char	**parts;
	char	*num;
	int		i;
	int		ok;

	parts = ft_split(s, ',');
	if (!parts)
		return (0);
	i = 0;
	ok = 1;
	while (i < 3 && parts[i] && ok)
	{
		num = parts[i];
		while (*num == ' ' || *num == '\t')
			num++;
		if (!ft_isdigit(num[0]) || ft_atoi(num) > 255
			|| ft_strlen(num) > 3)
			ok = 0;
		i++;
	}
	if (parts[3] || i != 3)
		ok = 0;
	free_tab(parts);
	return (ok);
}

static int	bv_line_ok(char *line, int key)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (key >= 16)
		return (bv_color(line + 1));
	return (bv_tex(line + 2));
}

const char	*bonus_validate_header(char **lines)
{
	int	seen;
	int	key;
	int	i;

	seen = 0;
	i = 0;
	while (lines[i])
	{
		key = bv_key(lines[i]);
		if (key)
		{
			if (!bv_line_ok(lines[i], key))
				return ("Invalid texture path or color in scene file");
			if (seen & key)
				return ("Duplicate texture or color identifier");
			seen |= key;
		}
		i++;
	}
	if (seen != 63)
		return ("Missing texture or color identifier in scene file");
	return (NULL);
}
