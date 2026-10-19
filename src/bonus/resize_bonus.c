/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:30:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static int	resize_zbuffer(t_game *game, int w)
{
	double	*fresh;
	int		i;

	fresh = malloc(sizeof(double) * w);
	if (!fresh)
		return (0);
	i = 0;
	while (i < w)
	{
		fresh[i] = 1e30;
		i++;
	}
	if (game->z_buffer)
		free(game->z_buffer);
	game->z_buffer = fresh;
	return (1);
}

static void	swap_frame(t_game *game, void *img, int w, int h)
{
	if (game->frame.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->frame.img_ptr);
	game->frame.img_ptr = img;
	game->frame.data_addr = mlx_get_data_addr(img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->frame.width = w;
	game->frame.height = h;
}

/*
** Rebuilds the framebuffer (and the per-column depth buffer) at the
** real window size.  From now on the game renders at that resolution,
** so a fullscreen window really fills the screen instead of showing
** a 1200x800 picture with black bars around it.
*/
void	bonus_resize_frame(t_game *game, int w, int h)
{
	t_bonus	*b;
	void	*img;

	if (w < 1 || h < 1 || (w == game->frame.width && h == game->frame.height))
		return ;
	img = mlx_new_image(game->mlx_ptr, w, h);
	if (!img || !resize_zbuffer(game, w))
	{
		if (img)
			mlx_destroy_image(game->mlx_ptr, img);
		return ;
	}
	swap_frame(game, img, w, h);
	b = (t_bonus *)game->bonus;
	if (b && b->menu_mode)
		menu_layout(b, w, h);
	if (b && (b->state == STATE_PAUSED || b->state == STATE_DEAD))
		b->redraw = 1;
	ft_printf("[cub3d] framebuffer %dx%d\n", w, h);
}

/*
** StructureNotify hook: MiniLibX hands the parameter over untouched, so
** the real window size is read back from X.  Only the framebuffer is
** rebuilt here, the window itself is managed by the window manager.
*/
int	bonus_resize_hook(t_game *game)
{
	t_mlx_ctx			*x;
	t_mlx_win			*w;
	XWindowAttributes	attr;

	if (!game->bonus || !game->frame.img_ptr)
		return (0);
	x = (t_mlx_ctx *)game->mlx_ptr;
	w = (t_mlx_win *)game->win_ptr;
	if (!XGetWindowAttributes(x->display, w->window, &attr))
		return (0);
	bonus_resize_frame(game, attr.width, attr.height);
	return (0);
}
