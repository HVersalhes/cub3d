/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:10:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_path(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	len = ft_strlen(line + i);
	while (len > 0 && (line[i + len - 1] == ' ' || line[i + len - 1] == '\t'
			|| line[i + len - 1] == '\n' || line[i + len - 1] == '\r'))
		len--;
	if (len <= 0)
		return (NULL);
	path = ft_substr(line, i, len);
	return (path);
}

static int	verify_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	set_texture_path(char **dest, char *line, t_game *game)
{
	char	*path;

	if (*dest != NULL)
		error_exit("Duplicate texture identifier in scene file", game);
	path = extract_path(line);
	if (!path)
		error_exit("Invalid texture path format", game);
	if (!verify_texture_file(path))
	{
		free(path);
		error_exit("Cannot open texture file", game);
	}
	*dest = path;
	return (1);
}

int	parse_texture_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture_path(&game->map.no_path, line + i + 2, game));
	if (line[i] == 'S' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture_path(&game->map.so_path, line + i + 2, game));
	if (line[i] == 'W' && line[i + 1] == 'E'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture_path(&game->map.we_path, line + i + 2, game));
	if (line[i] == 'E' && line[i + 1] == 'A'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture_path(&game->map.ea_path, line + i + 2, game));
	return (0);
}
