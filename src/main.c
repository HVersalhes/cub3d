/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 21:22:54 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 00:16:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./cub3d <map.cub>", NULL);
	init_game_data(&game);
	parse_cub_file(argv[1], &game);
	init_mlx(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_handler, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_release_handler, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	free_game(&game);
	return (0);
}
