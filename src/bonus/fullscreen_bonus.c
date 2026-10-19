/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <X11/Xutil.h>
#include "ft_printf/ft_printf.h"

static void	fs_hints(t_game *game, int w, int h)
{
	t_mlx_ctx	*x;
	t_mlx_win	*win;
	XSizeHints	sh;

	x = (t_mlx_ctx *)game->mlx_ptr;
	win = (t_mlx_win *)game->win_ptr;
	ft_memset(&sh, 0, sizeof(sh));
	sh.flags = PMinSize | PMaxSize | PPosition;
	sh.x = 0;
	sh.y = 0;
	sh.min_width = w;
	sh.min_height = h;
	sh.max_width = w;
	sh.max_height = h;
	XSetWMNormalHints(x->display, win->window, &sh);
}

static void	fs_event(t_game *game, int on)
{
	t_mlx_ctx	*x;
	t_mlx_win	*win;
	XEvent		ev;

	x = (t_mlx_ctx *)game->mlx_ptr;
	win = (t_mlx_win *)game->win_ptr;
	ft_memset(&ev, 0, sizeof(ev));
	ev.xclient.type = ClientMessage;
	ev.xclient.window = win->window;
	ev.xclient.message_type = XInternAtom(x->display, "_NET_WM_STATE",
			False);
	ev.xclient.format = 32;
	ev.xclient.data.l[0] = on;
	ev.xclient.data.l[1] = XInternAtom(x->display,
			"_NET_WM_STATE_FULLSCREEN", False);
	ev.xclient.data.l[3] = 1;
	XSendEvent(x->display, DefaultRootWindow(x->display), False,
		SubstructureRedirectMask | SubstructureNotifyMask, &ev);
}

/*
** Moves/resizes the window and immediately rebuilds the framebuffer at
** the new size: the whole screen (walls, floor, HUD, minimap, menu) is
** then rendered at the real resolution instead of being letterboxed.
*/
static void	fs_window(t_game *game, int w, int h, int full)
{
	t_mlx_ctx	*x;
	t_mlx_win	*win;

	x = (t_mlx_ctx *)game->mlx_ptr;
	win = (t_mlx_win *)game->win_ptr;
	fs_hints(game, w, h);
	if (full)
		XMoveResizeWindow(x->display, win->window, 0, 0, w, h);
	else
		XMoveResizeWindow(x->display, win->window, 40, 40, w, h);
	XFlush(x->display);
	bonus_resize_frame(game, w, h);
}

void	bonus_toggle_fullscreen(t_game *game)
{
	t_bonus	*b;
	int		w;
	int		h;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	b->fullscreen = !b->fullscreen;
	if (b->fullscreen)
	{
		mlx_get_screen_size(game->mlx_ptr, &w, &h);
		fs_event(game, 1);
		fs_window(game, w, h, 1);
		ft_printf("[cub3d] fullscreen on (%dx%d)\n", w, h);
	}
	else
	{
		fs_event(game, 0);
		fs_window(game, WIN_WIDTH, WIN_HEIGHT, 0);
		ft_printf("[cub3d] fullscreen off (%dx%d)\n", WIN_WIDTH, WIN_HEIGHT);
	}
}
