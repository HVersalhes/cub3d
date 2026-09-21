#include "cub3d.h"

int	main(void)
{
  void  *mlx_ptr;
  void  *win_ptr;

  mlx_ptr = mlx_init();
  win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
  mlx_pixel_put(mlx_ptr, win_ptr, 100, 100, 0xFF0000);
  mlx_loop(mlx_ptr);
  return (0);
}
