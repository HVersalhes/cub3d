/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <X11/Xutil.h>
#include "ft_printf/ft_printf.h"

static void	fs_hints(t_game *game, int full)
{
	t_mlx_ctx	*x;
	t_mlx_win	*w;
	XSizeHints	h;

	x = (t_mlx_ctx *)game->mlx_ptr;
	w = (t_mlx_win *)game->win_ptr;
	ft_memset(&h, 0, sizeof(h));
	h.flags = PMinSize | PMaxSize | PPosition;
	h.x = 0;
	h.y = 0;
	h.min_width = WIN_WIDTH;
	h.min_height = WIN_HEIGHT;
	h.max_width = WIN_WIDTH;
	h.max_height = WIN_HEIGHT;
	if (full)
	{
		h.min_width = 1;
		h.min_height = 1;
		h.max_width = DisplayWidth(x->display, DefaultScreen(x->display));
		h.max_height = DisplayHeight(x->display, DefaultScreen(x->display));
	}
	XSetWMNormalHints(x->display, w->window, &h);
}

static void	fs_event(t_game *game, int on)
{
	t_mlx_ctx	*x;
	t_mlx_win	*w;
	XEvent		ev;

	x = (t_mlx_ctx *)game->mlx_ptr;
	w = (t_mlx_win *)game->win_ptr;
	ft_memset(&ev, 0, sizeof(ev));
	ev.xclient.type = ClientMessage;
	ev.xclient.window = w->window;
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

static void	fs_apply(t_game *game, int on)
{
	t_mlx_ctx	*x;
	t_mlx_win	*w;

	x = (t_mlx_ctx *)game->mlx_ptr;
	w = (t_mlx_win *)game->win_ptr;
	fs_hints(game, on);
	fs_event(game, on);
	if (on)
		XMoveResizeWindow(x->display, w->window, 0, 0,
			DisplayWidth(x->display, DefaultScreen(x->display)),
			DisplayHeight(x->display, DefaultScreen(x->display)));
	else
		XMoveResizeWindow(x->display, w->window, 40, 40,
			WIN_WIDTH, WIN_HEIGHT);
	XFlush(x->display);
}

void	bonus_toggle_fullscreen(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	if (!b)
		return ;
	b->fullscreen = !b->fullscreen;
	fs_apply(game, b->fullscreen);
	if (b->fullscreen)
		ft_printf("[cub3d] fullscreen on\n");
	else
		ft_printf("[cub3d] fullscreen off\n");
}
