/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:56:26 by hcosta            #+#    #+#             */
/*   Updated: 2025/07/02 17:20:48 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	if (!s && n > 0)
		return (NULL);
	ptr = ((unsigned char *)s);
	while (n > 0)
	{
		*ptr = ((unsigned char)c);
		ptr++;
		n--;
	}
	return (s);
}
