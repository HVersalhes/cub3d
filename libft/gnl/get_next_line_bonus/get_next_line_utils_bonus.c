/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                         +:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:30:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/09/25 22:18:48 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	new = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[i])
		new[j++] = s1[i++];
	while (s2 && *s2)
		new[j++] = *s2++;
	new[j] = '\0';
	free(s1);
	return (new);
}

t_stash	*ft_stash_get(t_stash **stash, int fd)
{
	t_stash	*node;

	node = *stash;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_stash));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->buf = NULL;
	node->next = *stash;
	*stash = node;
	return (node);
}

void	ft_stash_del(t_stash **stash, int fd)
{
	t_stash	*node;
	t_stash	*prev;

	node = *stash;
	prev = NULL;
	while (node && node->fd != fd)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return ;
	if (prev)
		prev->next = node->next;
	else
		*stash = node->next;
	free(node->buf);
	free(node);
}
