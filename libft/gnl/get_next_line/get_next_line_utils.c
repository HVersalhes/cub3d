/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 18:35:46 by hcosta            #+#    #+#             */
/*   Updated: 2026/09/21 18:35:49 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
