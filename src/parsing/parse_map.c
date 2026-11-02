/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:11:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/11/02 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_nodes(t_map_node *head)
{
	t_map_node	*next;

	while (head)
	{
		next = head->next;
		if (head->line)
			free(head->line);
		free(head);
		head = next;
	}
}

/*
** Removes the line ending and appends the line to the linked list.
** The first line of the map is passed by the caller and is already owned
** by this function.
*/
static void	append_map_node(t_map_node **head, char *line, t_game *game)
{
	t_map_node	*new_node;
	t_map_node	*current;
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
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/*
** Reads every remaining line as part of the map. A blank line marks the
** end of the map, so any non-empty line after it is an error.
*/
static void	read_all_map_lines(int fd, char *first_line, t_map_node **head,
	t_game *game)
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

/*
** Builds the rectangular grid used by the game. Shorter lines are padded
** with spaces, which are treated as solid cells outside the walkable area.
*/
static void	build_rectangular_grid(t_map_node *head, t_game *game,
	int count, int max_width)
{
	int			i;

	game->map.grid = ft_calloc(count + 1, sizeof(char *));
	if (!game->map.grid)
	{
		free_map_nodes(head);
		error_exit("Allocation failed for map grid", game);
	}
	i = 0;
	while (i < count && head)
	{
		game->map.grid[i] = malloc(sizeof(char) * (max_width + 1));
		if (!game->map.grid[i])
		{
			free_map_nodes(head);
			error_exit("Allocation failed for map line", game);
		}
		ft_memset(game->map.grid[i], ' ', max_width);
		ft_memcpy(game->map.grid[i], head->line, ft_strlen(head->line));
		game->map.grid[i][max_width] = '\0';
		head = head->next;
		i++;
	}
}

void	parse_map(int fd, char *first_line, t_game *game)
{
	t_map_node	*head;
	t_map_node	*current;
	int			count;
	int			max_width;
	int			len;

	head = NULL;
	read_all_map_lines(fd, first_line, &head, game);
	count = 0;
	max_width = 0;
	current = head;
	while (current)
	{
		len = ft_strlen(current->line);
		if (len > max_width)
			max_width = len;
		count++;
		current = current->next;
	}
	game->map.height = count;
	game->map.width = max_width;
	build_rectangular_grid(head, game, count, max_width);
	free_map_nodes(head);
}
