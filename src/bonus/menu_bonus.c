/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static const char	*g_menu_paths[] = {
	"maps/valid/simple.cub",
	"maps/valid/minimal.cub",
	"maps/valid/complex_shape.cub",
	"maps/valid/bonus_all.cub",
	"maps/valid/bonus_doors.cub",
	"maps/valid/bonus_sprites.cub",
	"maps/valid/arena.cub",
	"maps/invalid/bad_map_chars.cub",
	"maps/invalid/empty_line_in_map.cub",
	"maps/invalid/invalid_color.cub",
	"maps/invalid/missing_texture.cub",
	"maps/invalid/no_player.cub",
	"maps/invalid/no_walls.cub",
	"maps/invalid/two_players.cub",
	NULL
};

void	bonus_menu_init(t_bonus *b)
{
	const char	*err;
	int			i;

	b->menu.count = 0;
	while (b->menu.count < MENU_MAP_MAX && g_menu_paths[b->menu.count])
	{
		i = b->menu.count;
		err = bonus_validate_map(g_menu_paths[i]);
		b->menu.paths[i] = g_menu_paths[i];
		b->menu.errors[i] = err;
		b->menu.valid[i] = (err == NULL);
		b->menu.count++;
	}
	b->menu.selected = 0;
	b->menu.row_hover = -1;
	b->menu.btn_hover = -1;
	ft_printf("[menu] %d maps listed\n", b->menu.count);
}

void	bonus_menu_select(t_bonus *b, int delta)
{
	b->menu.selected += delta;
	if (b->menu.selected < 0)
		b->menu.selected = b->menu.count - 1;
	if (b->menu.selected >= b->menu.count)
		b->menu.selected = 0;
}

int	bonus_menu_row_at(t_bonus *b, int x, int y)
{
	if (x < MENU_ROW_X || x > MENU_ROW_X + MENU_ROW_W)
		return (-1);
	if (y < MENU_ROW_Y || y >= MENU_ROW_Y + MENU_ROW_H * b->menu.count)
		return (-1);
	return ((y - MENU_ROW_Y) / MENU_ROW_H);
}

int	bonus_menu_btn_at(int x, int y)
{
	if (y < MENU_BTN_Y || y > MENU_BTN_Y + MENU_BTN_H)
		return (-1);
	if (x >= MENU_BTN1_X && x <= MENU_BTN1_X + MENU_BTN_W)
		return (0);
	if (x >= MENU_BTN2_X && x <= MENU_BTN2_X + MENU_BTN_W)
		return (1);
	return (-1);
}

void	bonus_menu_click(t_game *game, int x, int y)
{
	t_bonus	*b;
	int		row;
	int		btn;

	b = (t_bonus *)game->bonus;
	row = bonus_menu_row_at(b, x, y);
	if (row >= 0)
	{
		if (b->menu.selected == row)
			bonus_load_selected(game);
		b->menu.selected = row;
		return ;
	}
	btn = bonus_menu_btn_at(x, y);
	if (btn == 0)
		bonus_load_selected(game);
	else if (btn == 1)
		close_game(game);
}
