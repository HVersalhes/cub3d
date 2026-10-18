/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:18:32 by hcosta            #+#    #+#             */
/*   Updated: 2025/07/02 17:25:52 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len)
	{
		i = 0;
		j = 0;
		while (haystack[i] == needle[j] && needle[j] && i < len)
		{
			i++;
			j++;
		}
		if (!needle[j])
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
