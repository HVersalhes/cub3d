/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_lines_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*bv_clean(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	len = 0;
	while (line[len])
	{
		if (line[len] == '\r')
			line[len] = ' ';
		len++;
	}
	return (line);
}

static char	**bv_push(char **lines, int count, char *line)
{
	char	**next;
	int		i;

	next = ft_calloc(count + 2, sizeof(char *));
	if (!next)
	{
		free(line);
		free_tab(lines);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		next[i] = lines[i];
		i++;
	}
	next[count] = bv_clean(line);
	free(lines);
	return (next);
}

char	**bv_collect_lines(const char *path)
{
	char	**lines;
	char	*line;
	int		fd;
	int		count;

	lines = NULL;
	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		lines = bv_push(lines, count, line);
		if (!lines)
			break ;
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}
