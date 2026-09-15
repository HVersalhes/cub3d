#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

typedef struct	s_image
{
	void	*img;
	void	*addr;
	int	bbp;
	int	line_len;
	int	endian;
}	t_image;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_image	img;
}	t_game;

void	error_exit(const char *msg);
int		init_mlx(t_game *game);

#endif

