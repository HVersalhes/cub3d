/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:10:00 by hcosta            #+#    #+#             */
/*   Updated: 2026/10/19 03:00:00 by hcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

# define STATE_MENU 0
# define STATE_PLAYING 1
# define STATE_PAUSED 2
# define STATE_DEAD 3

# define MENU_MAP_MAX 16
# define MENU_ROW_W 700
# define MENU_ROW_H 34
# define MENU_BTN_W 220
# define MENU_BTN_H 54

# define PAUSE_BTN_W 220
# define PAUSE_BTN_H 60

# define TORCH_FRAMES 5
# define TORCH_FRAME_TIME 0.12

# define SPRITE_MAX 64

# define ENEMY_MAX 12
# define ENEMY_SPIDER 0
# define ENEMY_ZOMBIE 1
# define ENEMY_WALK 0
# define ENEMY_ATTACK 1
# define ENEMY_HURT 2
# define ENEMY_DIE 3
# define ENEMY_FRAMES 10
# define ENEMY_HURT_TEX 6
# define ENEMY_DIE_TEX 7
# define ENEMY_WALK_TIME 0.17
# define ENEMY_WALK_SPEED 0.85
# define ENEMY_ATTACK_TIME 0.42
# define ENEMY_DIE_TIME 0.2
# define ENEMY_HURT_TIME 0.3
# define ENEMY_ATTACK_DIST 1.0
# define ENEMY_SIGHT 10.0
# define ENEMY_MEMORY 3.0
# define ENEMY_SPAWN_MIN2 16.0
# define ENEMY_SPIDER_DMG 6
# define ENEMY_ZOMBIE_DMG 10
# define ENEMY_SPIDER_HP 60
# define ENEMY_ZOMBIE_HP 100

# define WEAPON_FRAMES 3
# define WEAPON_COOLDOWN 0.4
# define WEAPON_FIRE_TIME 0.2
# define SHOT_RANGE 13.0
# define SHOT_ANGLE 0.18
# define SHOT_DAMAGE 34

# define PLAYER_HP 100
# define FLASH_TIME 0.5
# define HURT_COOLDOWN 0.4

# define MINIMAP_MARGIN 20
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_SCALE 15.0
# define MM_RADIUS 96.0
# define MM_RADIUS2 9216.0
# define MM_RADIUS_IN2 8649.0

# define MM_COLOR_WALL 0x9CB8D8
# define MM_COLOR_DOOR 0x3EC8D8
# define MM_COLOR_FLOOR 0x1E2A38
# define MM_COLOR_PLAYER 0xFF3B30
# define MM_COLOR_SPRITE 0xFF9838
# define MM_COLOR_RING 0xC8DCEF
# define MM_HP_BAR_BG 0x1A0A0A
# define MM_HP_BAR_FILL 0xE03434

# define MM_WALL_PACKED 0x8C9CB8D8
# define MM_DOOR_PACKED 0xA63EC8D8
# define MM_SPRITE_PACKED 0xADFF9838
# define MM_FLOOR_PACKED 0x2E1E2A38
# define MM_ENEMY_PACKED 0xFF3E9BFF
# define MM_ENEMY_EDGE_PACKED 0xFF0A1420

# define DOOR_SPEED 1.5
# define DOOR_INTERACT_DIST 1.5

# define MOUSE_SENSITIVITY 0.0022
# define MOUSE_EDGE 90

# define SPRITE_MAGENTA 0xFF00FF

# define DOOR_CLOSED 0
# define DOOR_OPENING 1
# define DOOR_OPEN 2
# define DOOR_CLOSING 3

# define KEY_F 102
# define KEY_P 112
# define KEY_M 109
# define KEY_R 114
# define KEY_Q 113
# define KEY_ENTER 65293
# define KEY_UP 65362
# define KEY_DOWN 65364
# define MOUSE_LEFT 1

typedef struct s_door
{
	int		x;
	int		y;
	int		state;
	double	openness;
}	t_door;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
	double	height;
	double	center_z;
	int		hp;
	int		hp_max;
	t_img	*tex;
}	t_sprite;

typedef struct s_sprite_draw
{
	t_img	*tex;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		width;
	int		height;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	char	*dst_end;
	int		ty0;
	int		ty_step;
}	t_sprite_draw;

typedef struct s_enemy
{
	double	x;
	double	y;
	double	last_x;
	double	last_y;
	double	dist;
	double	memory;
	int		type;
	int		hp;
	int		state;
	int		frame;
	double	timer;
	int		hit_applied;
	int		alive;
}	t_enemy;

typedef struct s_weapon
{
	int		frame;
	double	timer;
	double	cooldown;
}	t_weapon;

typedef struct s_menu
{
	int			count;
	int			selected;
	int			row_hover;
	int			btn_hover;
	int			row_x;
	int			row_w;
	int			row_h;
	int			row_y;
	int			btn_x1;
	int			btn_x2;
	int			btn_y;
	int			valid[MENU_MAP_MAX];
	const char	*paths[MENU_MAP_MAX];
	const char	*errors[MENU_MAP_MAX];
}	t_menu;

/*
** Fixed-point state for one textured floor/ceiling scanline.  Texture
** coordinates are kept as 16.16 values so the pixel loop only adds
** integers (no floats, no divisions, no library calls).
*/
typedef struct s_fc
{
	char	*base;
	int		line;
	int		px;
	int		tw;
	int		th;
	int		u;
	int		v;
	int		du;
	int		dv;
}	t_fc;

typedef struct s_mm_view
{
	double	fx;
	double	fy;
	double	rx;
	double	ry;
	double	sx;
	double	sy;
	double	gx;
	double	gy;
	double	wx0;
	double	wy0;
}	t_mm_view;

typedef struct s_bvgrid
{
	char	**lines;
	int		start;
	int		width;
	int		height;
}	t_bvgrid;

typedef struct s_bonus
{
	int			state;
	t_img		door_tex;
	t_door		*doors;
	int			door_count;
	t_img		torch_tex[TORCH_FRAMES];
	t_sprite	*sprites;
	int			sprite_count;
	int			sprite_frame;
	double		sprite_timer;
	t_sprite	*draw_list;
	int			draw_count;
	t_img		enemy_tex[2][ENEMY_FRAMES];
	t_enemy		enemies[ENEMY_MAX];
	int			enemy_count;
	t_img		weapon_tex[WEAPON_FRAMES];
	t_weapon	weapon;
	t_img		floor_tex;
	t_img		ceil_tex;
	int			health;
	double		damage_flash;
	double		hurt_cd;
	int			mouse_init;
	int			mouse_x;
	int			mouse_y;
	int			menu_mode;
	int			pause_hover;
	int			mm_x;
	int			mm_y;
	int			redraw;
	double		last_time;
	t_menu		menu;
}	t_bonus;

/* shared entry points (stubbed in the mandatory build) */
int				bonus_active(void);
void			bonus_init(t_game *game);
void			bonus_update(t_game *game);
void			bonus_render(t_game *game);
void			bonus_free(t_game *game);
void			bonus_render_text(t_game *game);
int				bonus_menu_mode(t_game *game, const char *arg);
int				bonus_world_active(t_game *game);
int				bonus_render_floor_ceiling(t_game *game);
int				bonus_key_press(int keycode, t_game *game);
int				bonus_mouse_button(int button, int x, int y, t_game *game);
int				bonus_mouse_hook(int x, int y, t_game *game);

/* assets */
void			bonus_load_assets(t_game *game, t_bonus *b);
void			bonus_free_assets(t_game *game, t_bonus *b);
void			bonus_load_image(t_game *game, t_img *img, const char *path);
void			bonus_load_set(t_game *game, t_img *set, const char **paths,
					int count);
void			bonus_load_enemies(t_game *game, t_bonus *b);

/* state / levels */
t_bonus			*bonus_state_new(t_game *game);
void			bonus_init_level(t_game *game, t_bonus *b);
void			bonus_enter_overlay(t_game *game, int state);
void			bonus_unload_level(t_game *game);
int				bonus_load_selected(t_game *game);
void			bonus_restart_level(t_game *game);
void			bonus_back_to_menu(t_game *game);

/* doors */
void			bonus_init_doors(t_game *game, t_bonus *b);
int				bonus_find_door(t_bonus *b, int x, int y);
int				bonus_door_solid(t_game *game, int x, int y);
void			bonus_update_doors(t_game *game, t_bonus *b, double dt);
int				bonus_door_blocks(t_game *game, t_ray *ray);
t_img			*bonus_door_texture(t_game *game, t_ray *ray);

/* sprites */
int				count_sprites(t_game *game);
void			fill_sprites(t_bonus *b, t_game *game);
void			draw_sprite(t_game *game, t_sprite *sprite);
void			bonus_init_sprites(t_game *game, t_bonus *b);
void			bonus_free_sprites(t_game *game, t_bonus *b);
void			bonus_update_sprites(t_bonus *b, double dt);
void			bonus_render_sprites(t_game *game);
void			bonus_sort_sprites(t_sprite *list, int count, t_player *p);

/* enemies */
void			bonus_spawn_enemies(t_game *game, t_bonus *b);
void			bonus_update_enemies(t_game *game, double dt);
void			bonus_append_enemy_sprites(t_game *game, int *n);
void			bonus_damage_player(t_game *game, int dmg);
void			bonus_damage_enemy(t_game *game, int idx, int dmg);
void			bonus_tick_timers(t_bonus *b, double dt);
int				enemy_solid(char c);
int				enemy_has_los(t_game *game, t_enemy *e);
double			enemy_dist(t_game *game, t_enemy *e);
void			enemy_set_state(t_enemy *e, int state);
void			enemy_walk_tick(t_enemy *e, double dt);
void			enemy_hurt_tick(t_enemy *e, double dt);
void			enemy_die_tick(t_enemy *e, double dt);
void			enemy_attack_tick(t_game *game, t_enemy *e, double dt);
void			enemy_close_tick(t_game *game, t_enemy *e, double dt);

/* weapon */
void			bonus_update_weapon(t_game *game, double dt);
void			bonus_fire_weapon(t_game *game);
void			bonus_render_weapon(t_game *game);
void			bonus_hitscan(t_game *game);

/* hud */
void			bonus_render_hud(t_game *game);
void			bonus_hud_text(t_game *game);
void			bonus_tint_frame(t_game *game, double dark, int tint);
void			draw_rect(t_img *img, t_rect r, int color);

/* minimap */
unsigned int	mm_tile_color(t_game *game, double wx, double wy);
void			mm_blend(t_img *img, int offset, unsigned int color, int alpha);
void			mm_plot(t_game *game, int x, int y, unsigned int packed);
void			mm_enemies(t_game *game, t_mm_view *view);
int				ring_edge(int radius_sq, int dy);
int				ring_inner(int radius_sq, int dy);
void			mm_ring(t_game *game);
void			mm_player_marker(t_game *game);
void			bonus_render_minimap(t_game *game);

/* mouse look */
void			bonus_update_look(t_game *game);

/* menu */
void			bonus_menu_init(t_bonus *b);
void			bonus_menu_click(t_game *game, int x, int y);
int				bonus_menu_row_at(t_bonus *b, int x, int y);
int				bonus_menu_btn_at(t_bonus *b, int x, int y);
int				menu_row_color(t_menu *m, int i);
char			*menu_status(t_menu *m, int i);
int				menu_status_color(t_menu *m, int i);
void			menu_layout(t_bonus *b, int w, int h);
void			bonus_render_menu(t_game *game);
void			bonus_menu_text(t_game *game);
const char		*bonus_validate_map(const char *path);
char			**bv_collect_lines(const char *path);
int				bv_key(char *line);
const char		*bonus_validate_header(char **lines);
const char		*bonus_validate_chars(t_bvgrid *g);
const char		*bonus_validate_closed(t_bvgrid *g);
char			bonus_validate_tile(t_bvgrid *g, int x, int y);

/* pause */
int				bonus_pause_btn_at(t_game *game, int x, int y);
void			bonus_pause_btn_rect(t_game *game, int idx, t_rect *r);
void			bonus_pause_click(t_game *game, int x, int y);
void			bonus_pause_key(t_game *game, int keycode);
void			bonus_render_pause(t_game *game);
void			bonus_pause_text(t_game *game);

#endif
