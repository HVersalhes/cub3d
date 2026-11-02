/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:23:35 by hcosta            #+#    #+#             */
/*   Updated: 2025/09/22 09:45:06 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	int		len;
	long	nbr;

	len = 0;
	nbr = (long)nb;
	if (nbr < 0)
	{
		len += ft_putchar('-');
		nbr = -nbr;
	}
	len += ft_putnbr_base((unsigned long long)nbr, "0123456789");
	return (len);
}
