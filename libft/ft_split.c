/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:13:03 by hcosta            #+#    #+#             */
/*   Updated: 2025/07/03 18:13:22 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	ft_countwords(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	ft_fillword(const char *s, char c, char **split, int i)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	split[i] = ft_substr(s, 0, len);
	if (!split[i])
		return (0);
	return (len);
}

static char	**ft_fillsplit(const char *s, char c, char **split, int words)
{
	int	i;
	int	len;

	i = 0;
	while (*s && i < words)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			len = ft_fillword(s, c, split, i);
			if (!len)
			{
				ft_freesplit(split);
				return (NULL);
			}
			s += len;
			i++;
		}
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	if (!ft_fillsplit(s, c, split, words))
		return (NULL);
	return (split);
}
