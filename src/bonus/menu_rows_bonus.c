/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_rows_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	menu_row_color(t_menu *m, int i)
{
	if (m->valid[i])
	{
		if (m->selected == i || m->row_hover == i)
			return (0x2E5B8A);
		return (0x1A2836);
	}
	if (m->selected == i || m->row_hover == i)
		return (0x8A3038);
	return (0x33202A);
}

int	menu_status_color(t_menu *m, int i)
{
	if (m->valid[i])
		return (0x8CF0A8);
	return (0xF08C8C);
}

char	*menu_status(t_menu *m, int i)
{
	if (m->valid[i])
		return ("VALID");
	if (m->errors[i])
		return ("INVALID - see terminal");
	return ("INVALID");
}
