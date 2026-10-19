/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 03:00:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "ft_printf/ft_printf.h"

t_bonus	*bonus_state_new(t_game *game)
{
	t_bonus	*b;

	b = ft_calloc(1, sizeof(t_bonus));
	if (!b)
		error_exit("Failed to allocate bonus state", game);
	game->bonus = b;
	b->health = PLAYER_HP;
	bonus_load_assets(game, b);
	return (b);
}

void	bonus_init_level(t_game *game, t_bonus *b)
{
	b->health = PLAYER_HP;
	b->damage_flash = 0.0;
	b->weapon.frame = 0;
	b->weapon.timer = 0.0;
	b->weapon.cooldown = 0.0;
	b->sprite_frame = 0;
	b->sprite_timer = 0.0;
	bonus_init_doors(game, b);
	bonus_init_sprites(game, b);
	bonus_spawn_enemies(game, b);
	ft_printf("[cub3d] level: %d torches, %d doors, %d enemies\n",
		b->sprite_count, b->door_count, b->enemy_count);
}

static void	overlay_playing(t_game *game)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	b->mouse_init = 0;
	if (!b->menu_mode)
	{
		mlx_mouse_show(game->mlx_ptr, game->win_ptr);
		ft_printf("[cub3d] in game (classic controls)\n");
		return ;
	}
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	ft_printf("[cub3d] in game (mouse fixed at center)\n");
}

void	bonus_enter_overlay(t_game *game, int state)
{
	t_bonus	*b;

	b = (t_bonus *)game->bonus;
	b->state = state;
	if (state == STATE_PLAYING)
	{
		overlay_playing(game);
		return ;
	}
	mlx_mouse_show(game->mlx_ptr, game->win_ptr);
	if (state == STATE_PAUSED)
	{
		bonus_tint_frame(game, 0.45, 0x000000);
		ft_printf("[cub3d] paused\n");
	}
	else if (state == STATE_DEAD)
	{
		bonus_tint_frame(game, 0.45, 0x800000);
		ft_printf("[cub3d] player died\n");
	}
	else
		ft_printf("[cub3d] menu\n");
}

int	bonus_menu_mode(t_game *game, const char *arg)
{
	t_bonus	*b;

	if (ft_strlen(arg) != 4 || ft_strncmp(arg, "menu", 4) != 0)
		return (0);
	init_mlx(game);
	b = bonus_state_new(game);
	b->menu_mode = 1;
	bonus_menu_init(b);
	b->state = STATE_MENU;
	mlx_mouse_show(game->mlx_ptr, game->win_ptr);
	ft_printf("[cub3d] menu mode: %d maps listed\n", b->menu.count);
	return (1);
}
