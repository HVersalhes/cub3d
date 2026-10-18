/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:11:58 by hcosta            #+#    #+#             */
/*   Updated: 2025/06/24 16:42:31 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		uc;

	if (!s && n > 0)
		return (NULL);
	ptr = ((const unsigned char *)s);
	uc = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == uc)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
