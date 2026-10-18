/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:11:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:13:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_nodes(t_map_node *head)
{
	t_map_node	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->line)
			free(head->line);
		free(head);
		head = tmp;
	}
}

static void	append_map_node(t_map_node **head, char *line, t_game *game)
{
	t_map_node	*new_node;
	t_map_node	*curr;
	int			len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	new_node = malloc(sizeof(t_map_node));
	if (!new_node)
	{
		free(line);
		free_map_nodes(*head);
		error_exit("Memory allocation error while reading map", game);
	}
	new_node->line = line;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

static void	read_all_map_lines(int fd, char *first_line,
	t_map_node **head, t_game *game)
{
	char	*line;
	int		map_ended;

	append_map_node(head, first_line, game);
	map_ended = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
		{
			map_ended = 1;
			free(line);
		}
		else
		{
			if (map_ended)
			{
				free(line);
				free_map_nodes(*head);
				error_exit("Empty line detected inside map grid", game);
			}
			append_map_node(head, line, game);
		}
		line = get_next_line(fd);
	}
}

static void	build_rectangular_grid(t_map_node *head, t_game *game,
	int count, int max_w)
{
	t_map_node	*curr;
	int			i;
	int			j;

	game->map.grid = ft_calloc(count + 1, sizeof(char *));
	if (!game->map.grid)
	{
		free_map_nodes(head);
		error_exit("Allocation failed for map grid", game);
	}
	curr = head;
	i = -1;
	while (++i < count && curr)
	{
		game->map.grid[i] = malloc(sizeof(char) * (max_w + 1));
		if (!game->map.grid[i])
			error_exit("Allocation failed for map line", game);
		j = -1;
		while (curr->line[++j])
			game->map.grid[i][j] = curr->line[j];
		while (j < max_w)
			game->map.grid[i][j++] = ' ';
		game->map.grid[i][max_w] = '\0';
		curr = curr->next;
	}
}

void	parse_map(int fd, char *first_line, t_game *game)
{
	t_map_node	*head;
	t_map_node	*curr;
	int			count;
	int			max_w;
	int			len;

	head = NULL;
	read_all_map_lines(fd, first_line, &head, game);
	count = 0;
	max_w = 0;
	curr = head;
	while (curr)
	{
		len = ft_strlen(curr->line);
		if (len > max_w)
			max_w = len;
		count++;
		curr = curr->next;
	}
	game->map.height = count;
	game->map.width = max_w;
	build_rectangular_grid(head, game, count, max_w);
	free_map_nodes(head);
}
