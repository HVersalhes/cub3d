#include "cub3d.h"

int	main(void)
{
	t_game	game;

	game.mlx = NULL;
	game.win = NULL;
	if (init_mlx(&game) != 0)
		return (1);
	mlx_loop(game.mlx);
	return (0);
}
