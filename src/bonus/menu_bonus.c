/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

static void	menu_paths(const char **paths)
{
	paths[0] = "maps/valid/simple.cub";
	paths[1] = "maps/valid/minimal.cub";
	paths[2] = "maps/valid/complex_shape.cub";
	paths[3] = "maps/valid/bonus_all.cub";
	paths[4] = "maps/valid/bonus_doors.cub";
	paths[5] = "maps/valid/bonus_sprites.cub";
	paths[6] = "maps/valid/arena.cub";
	paths[7] = "maps/invalid/bad_map_chars.cub";
	paths[8] = "maps/invalid/empty_line_in_map.cub";
	paths[9] = "maps/invalid/invalid_color.cub";
	paths[10] = "maps/invalid/missing_texture.cub";
	paths[11] = "maps/invalid/no_player.cub";
	paths[12] = "maps/invalid/no_walls.cub";
	paths[13] = "maps/invalid/two_players.cub";
	paths[14] = NULL;
}

void	bonus_menu_init(t_bonus *b)
{
	const char	*paths[MENU_MAP_MAX];
	const char	*err;
	int			i;

	menu_paths(paths);
	b->menu.count = 0;
	while (b->menu.count < MENU_MAP_MAX && paths[b->menu.count])
	{
		i = b->menu.count;
		err = bonus_validate_map(paths[i]);
		b->menu.paths[i] = paths[i];
		b->menu.errors[i] = err;
		b->menu.valid[i] = (err == NULL);
		b->menu.count++;
	}
	b->menu.selected = 0;
	b->menu.row_hover = -1;
	b->menu.btn_hover = -1;
	ft_printf("[menu] %d maps listed\n", b->menu.count);
}

int	bonus_menu_row_at(t_bonus *b, int x, int y)
{
	if (x < b->menu.row_x || x > b->menu.row_x + b->menu.row_w)
		return (-1);
	if (y < b->menu.row_y
		|| y >= b->menu.row_y + b->menu.row_h * b->menu.count)
		return (-1);
	return ((y - b->menu.row_y) / b->menu.row_h);
}

int	bonus_menu_btn_at(t_bonus *b, int x, int y)
{
	if (y < b->menu.btn_y || y > b->menu.btn_y + MENU_BTN_H)
		return (-1);
	if (x >= b->menu.btn_x1 && x <= b->menu.btn_x1 + MENU_BTN_W)
		return (0);
	if (x >= b->menu.btn_x2 && x <= b->menu.btn_x2 + MENU_BTN_W)
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
	btn = bonus_menu_btn_at(b, x, y);
	if (btn == 0)
		bonus_load_selected(game);
	else if (btn == 1)
		close_game(game);
}
