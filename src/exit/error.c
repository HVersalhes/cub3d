/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 00:06:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:06:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(const char *msg, t_game *game)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	if (game)
		free_game(game);
	exit(EXIT_FAILURE);
}
