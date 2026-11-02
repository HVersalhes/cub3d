/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:11:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** A line is considered empty when it has no printable content. Such
** lines are ignored before the map starts.
*/
static int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\0' || line[i] == '\n' || line[i] == '\r');
}

static void	validate_cub_extension(const char *path, t_game *game)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		error_exit("File name too short (must be *.cub)", game);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension (must be .cub)", game);
	if (path[len - 5] == '/')
		error_exit("File name cannot be only .cub", game);
}

/*
** Parses one non-empty line before the map. The current line is stored
** in the game so that error_exit can free it if a parser reports an error.
*/
static void	handle_header_line(char *line, int fd, t_game *game)
{
	game->current_line = line;
	if (!parse_texture_line(line, game) && !parse_color_line(line, game))
	{
		game->current_line = NULL;
		free(line);
		close(fd);
		error_exit("Invalid element or map placed before headers", game);
	}
	game->current_line = NULL;
}

/*
** Reads the file line by line. Texture and color lines come first. Once
** all six headers exist, the next non-empty line starts the map.
*/
static void	process_scene_lines(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (game->map.no_path && game->map.so_path && game->map.we_path
			&& game->map.ea_path && game->map.floor_color >= 0
			&& game->map.ceiling_color >= 0)
		{
			parse_map(fd, line, game);
			return ;
		}
		handle_header_line(line, fd, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	error_exit("Incomplete scene file: map not found", game);
}

void	parse_cub_file(const char *file_path, t_game *game)
{
	int	fd;

	validate_cub_extension(file_path, game);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open .cub file", game);
	process_scene_lines(fd, game);
	close(fd);
	validate_map(game);
}
