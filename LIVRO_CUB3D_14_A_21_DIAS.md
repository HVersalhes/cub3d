# 📖 O LIVRO DO CUB3D: DO ZERO AOS 125% EM 14 A 21 DIAS
### *Manual Prático de Engenharia Gráfica, Raycasting e Arquitetura em C para a Escola 42*
**Autores:** Guia de Aceleração para **hcosta** & **hcuessec**  
**Data de Início:** 19 de Setembro de 2026  
**Meta de Conclusão:** 03 de Outubro (14 dias) ou 10 de Outubro (21 dias)

---

## 📑 SUMÁRIO GERAL

- [COMO USAR ESTE LIVRO](#como-usar-este-livro)
- [A FILOSOFIA DOS 14-21 DIAS: O MÉTODO FAST-TRACK](#a-filosofia-dos-14-21-dias-o-método-fast-track)
- **SEMANA 1: A FUNDAÇÃO BRUTAL (DIAS 1 A 7)**
  - [DIA 1: Setup, Makefile sem Relink, Libft e Structs Mestres](#dia-1-setup-makefile-sem-relink-libft-e-structs-mestres)
  - [DIA 2: Parsing das Texturas (NO, SO, WE, EA) e Cores (F, C)](#dia-2-parsing-das-texturas-no-so-we-ea-e-cores-f-c)
  - [DIA 3: O Framebuffer da MiniLibX e Render de Céu/Chão](#dia-3-o-framebuffer-da-minilibx-e-render-de-cêuchão)
  - [DIA 4: Leitura e Normalização da Matriz do Mapa](#dia-4-leitura-e-normalização-da-matriz-do-mapa)
  - [DIA 5: Validação do Labirinto com Flood Fill (Zero Mapas Abertos)](#dia-5-validação-do-labirinto-com-flood-fill-zero-mapas-abertos)
  - [DIA 6: A Matemática do Raycasting: Vetores e o Algoritmo DDA](#dia-6-a-matemática-do-raycasting-vetores-e-o-algoritmo-dda)
  - [DIA 7: Projeção de Paredes Sólidas, Shading e Fim da Semana 1](#dia-7-projeção-de-paredes-sólidas-shading-e-fim-da-semana-1)
- **SEMANA 2: TEXTURAS, MOVIMENTO E CONGELAMENTO OBRIGATÓRIO (DIAS 8 A 14)**
  - [DIA 8: Input Polling Anti-Stuttering e Eventos de Teclado](#dia-8-input-polling-anti-stuttering-e-eventos-de-teclado)
  - [DIA 9: Cinemática Vetorial: Translação WASD e Rotação 2D](#dia-9-cinemática-vetorial-translação-wasd-e-rotação-2d)
  - [DIA 10: Carregamento Seguro de Texturas XPM e Gestão de Imagens](#dia-10-carregamento-seguro-de-texturas-xpm-e-gestão-de-imagens)
  - [DIA 11: Mapeamento UV nas Paredes (WallX, TexX e TexY)](#dia-11-mapeamento-uv-nas-paredes-wallx-texx-e-texy)
  - [DIA 12: Refatoração Estrita para a Norminette 42](#dia-12-refatoração-estrita-para-a-norminette-42)
  - [DIA 13: Bateria de Testes com Valgrind e Tratamento de Erros](#dia-13-bateria-de-testes-com-valgrind-e-tratamento-de-erros)
  - [DIA 14: O Marco v1.0: Congelamento da Parte Obrigatória (Nota 100 Garantida)](#dia-14-o-marco-v10-congelamento-da-parte-obrigatória-nota-100-garantida)
- **SEMANA 3: OS 5 BÓNUS E AVALIAÇÃO FINAL (DIAS 15 A 21)**
  - [DIA 15: Bónus 1 — Bounding Box e Deslizamento nas Paredes (Wall Sliding)](#dia-15-bónus-1--bounding-box-e-deslizamento-nas-paredes-wall-sliding)
  - [DIA 16: Bónus 2 — Minimapa 2D com Radar e Cone de Visão](#dia-16-bónus-2--minimapa-2d-com-radar-e-cone-de-visão)
  - [DIA 17: Bónus 3 — Sistema de Portas Interativas ('D')](#dia-17-bónus-3--sistema-de-portas-interativas-d)
  - [DIA 18: Bónus 4 — Rotação Suave com o Mouse (Mouse Look)](#dia-18-bónus-4--rotação-suave-com-o-mouse-mouse-look)
  - [DIA 19: Bónus 5 (Parte 1) — O Z-Buffer e Ordenação de Sprites](#dia-19-bónus-5-parte-1--o-z-buffer-e-ordenação-de-sprites)
  - [DIA 20: Bónus 5 (Parte 2) — Projeção de Sprites Animadas e Transparência](#dia-20-bónus-5-parte-2--projeção-de-sprites-animadas-e-transparência)
  - [DIA 21: README Oficial (Subject Cap VI), Makefile Bonus e Simulação da Defesa](#dia-21-readme-oficial-subject-cap-vi-makefile-bonus-e-simulação-da-defesa)
- [APÊNDICE A: GUIA DE SOBREVIVÊNCIA NA AVALIAÇÃO POR PARES](#apêndice-a-guia-de-sobrevivência-na-avaliação-por-pares)
- [APÊNDICE B: TABELA PERIÓDICA DE KEYCODES NO LINUX (X11)](#apêndice-b-tabela-periódica-de-keycodes-no-linux-x11)

---

## COMO USAR ESTE LIVRO

Este livro não é apenas teoria abstrata: é um **manual de operações diárias**.  
Para cada dia de trabalho, você encontrará:
1. **O Alvo do Dia:** O que precisa estar funcionando e testado até o final do dia.
2. **Teoria Mastigada:** O conceito matemático ou gráfico por trás da implementação.
3. **Código C Prático:** Funções e trechos exatos prontos e compatíveis com a Norma 42.
4. **Divisão de Trabalho:** Tarefas isoladas para **hcosta** e **hcuessec** trabalharem em paralelo sem colisões no Git.
5. **Comandos Git do Dia:** Como criar a branch, testar e fazer o merge.
6. **Armadilha do Dia:** O erro clássico que faz 90% dos estudantes perderem horas.

### ⏱️ Escolha a sua Velocidade:
* **Modo 21 Dias (Recomendado — ~6h/dia):** Siga exatamente 1 dia do livro por dia corrido. Você terá finais de semana mais leves e tempo para absorver toda a matemática.
* **Modo 14 Dias (Hardcore / Rush — ~9h a 10h/dia):** Condense os dias pares e ímpares (ex: Dias 1 e 2 no Dia 1, Dias 3 e 4 no Dia 2). A parte obrigatória estará congelada no Dia 10 e os bónus terminam no Dia 14.

---

## A FILOSOFIA DOS 14-21 DIAS: O MÉTODO FAST-TRACK

Para terminar um projeto gráfico em tempo recorde sem retrabalho, quatro princípios precisam ser seguidos:

1. **A Interface Imutável (`cub3d_structs.h`):** Uma vez definidas as variáveis do jogador, mapa e imagem no Dia 1, NINGUÉM muda o nome dos campos. Se a interface for estável, o hcosta programa o parser sem precisar do motor gráfico, e o hcuessec programa o raycasting usando um mapa de teste estático.
2. **Valgrind Contínuo:** Se você rodar o Valgrind a cada commit, você corrige vazamentos de 2 linhas em 3 minutos. Se você deixar para rodar no último dia, terá que caçar 15 vazamentos entre 3.000 linhas de código.
3. **Vetores em vez de Trigonometria:** Funções `cos()`, `sin()` e `tan()` são pesadas e complicadas de sincronizar com a câmera. O modelo vetorial de Lode Vandevenne usa apenas somas e multiplicações, resolvendo a direção dos raios de forma ultra-rápida.
4. **Assets de 64x64 Potência de 2:** Usar texturas de $64 \times 64$ permite substituir divisões caras por operações bitwise instantâneas (`texX & 63`).

---

# SEMANA 1: A FUNDAÇÃO BRUTAL (DIAS 1 A 7)

---

## DIA 1: Setup, Makefile sem Relink, Libft e Structs Mestres

### 🎯 O Alvo do Dia
O repositório compila perfeitamente com `make`, linka a biblioteca `minilibx` e a sua `libft`, e possui todas as estruturas de dados fundamentais consolidadas em [`include/cub3d_structs.h`](file:///home/hcosta/cub3d/include/cub3d_structs.h).

### 🧠 Teoria e Arquitetura
O cub3D exige compilação modular estrita. O executável principal depende de bibliotecas estáticas externas (`libmlx.a` e `libft.a`).  
No Linux, a MiniLibX conversa com o servidor gráfico X11, exigindo as bibliotecas do sistema `-lXext -lX11 -lm` (matemática).

### 💻 Código Prático do Dia

#### 1. [`include/cub3d_structs.h`](file:///home/hcosta/cub3d/include/cub3d_structs.h) (A Interface Central)
```c
#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <stdbool.h>

typedef struct s_img {
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture {
	char	*path;
	t_img	img;
}	t_texture;

typedef struct s_keys {
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	rot_left;
	bool	rot_right;
	bool	door_interact;
}	t_keys;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		player_count;
	char	player_dir;
	int		player_spawn_x;
	int		player_spawn_y;
}	t_map;

typedef struct s_ray {
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_game {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		frame;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_texture	textures[4]; // 0: NO, 1: SO, 2: WE, 3: EA
	double		*z_buffer;   // Para os bónus de sprites
}	t_game;

#endif
```

#### 2. Regra Anti-Relink no Makefile
No Makefile, compile as bibliotecas com a flag `-C` apenas quando o arquivo `.a` correspondente não existir:
```make
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
```

### 👥 Divisão de Trabalho
* **hcosta:** Criar e conferir todas as structs em `include/cub3d_structs.h` e a função utilitária `error_exit(msg, game)`.
* **hcuessec:** Configurar o Makefile principal com as dependências da `minilibx` e `libft`, testando a compilação limpa.

### 🔄 Git & Comandos
```bash
git checkout -b feature/phase-0-setup
make re
make # Deve imprimir: "Nothing to be done for 'all'"
git add Makefile include/
git commit -m "setup: inicializacao de makefile, headers e structs centrais"
git checkout develop && git merge --no-ff feature/phase-0-setup && git push origin develop
```

### ⚠️ Armadilha do Dia
*Tentar compilar com `gcc` sem a flag `-lm`.* Funções matemáticas (`cos`, `sin`, `fabs`) exigem a flag `-lm` no final dos argumentos de linkagem no Linux!

---

## DIA 2: Parsing das Texturas (NO, SO, WE, EA) e Cores (F, C)

### 🎯 O Alvo do Dia
O programa lê o arquivo `.cub`, extrai os caminhos das 4 texturas e as cores de chão e teto, converte os valores RGB para hexadecimal (`0x00RRGGBB`) e rejeita entradas inválidas com `Error\n<mensagem>`.

### 🧠 Teoria do Parsing no cub3D
Segundo o subject:
- As texturas começam com `NO `, `SO `, `WE `, `EA `.
- O chão e teto começam com `F ` e `C `.
- Podem aparecer em **qualquer ordem** antes do mapa.
- Podem ter múltiplos espaços separando as informações.
- Se uma cor for menor que 0 ou maior que 255, ou se houver caracteres estranhos (como `F 255,100,abc`), o programa deve falhar de forma limpa.

### 💻 Código Prático: Conversão de Cor Segura
```c
int	parse_rgb(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_matrix(split), -1);
	if (!is_all_digits(split[0]) || !is_all_digits(split[1])
		|| !is_all_digits(split[2]))
		return (free_matrix(split), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_matrix(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
```

### 👥 Divisão de Trabalho
* **hcosta:** Implementar a extração dos caminhos das texturas (`open` com `O_RDONLY` para checar se o arquivo existe).
* **hcuessec:** Implementar o parser de RGB e conversão binária para `int floor_color` e `int ceiling_color`.

### 🔄 Git & Comandos
```bash
git checkout -b feature/phase-1-textures-colors
git add src/parsing/
git commit -m "feat(parsing): extracao de texturas e conversao de cores RGB"
git checkout develop && git merge --no-ff feature/phase-1-textures-colors && git push origin develop
```

---

## DIA 3: O Framebuffer da MiniLibX e Render de Céu/Chão

### 🎯 O Alvo do Dia
A janela abre suavemente ($1200 \times 800$). A metade superior da tela é preenchida com a cor do teto e a metade inferior com a cor do chão, usando o buffer de memória com taxa de quadros superior a 60 FPS.

### 🧠 Teoria: O Ponteiro de Memória do Framebuffer
Em um sistema de 32 bits por pixel (`bpp = 32`), cada pixel ocupa **4 bytes** (Alpha, Red, Green, Blue).  
A memória da imagem é um array unidimensional linear. Para acessar o pixel $(x, y)$:
$$\text{offset} = (y \times \text{line\_len}) + (x \times 4)$$
Escrever 4 bytes inteiros diretamente no ponteiro:
```c
*(unsigned int *)(img->data_addr + offset) = color;
```

### 💻 Código Prático: Framebuffer & Render de Fundo
```c
void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_ceiling_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_pixel_put(&game->frame, x, y, game->map.ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_pixel_put(&game->frame, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}
```

### 👥 Divisão de Trabalho
* **hcosta:** Criar as funções de inicialização de janela `init_mlx()` e os hooks para fechar a janela ao pressionar ESC ou clicar no botão "X".
* **hcuessec:** Implementar `my_pixel_put()` e a função de renderização do chão e teto diretamente no buffer.

---

## DIA 4: Leitura e Normalização da Matriz do Mapa

### 🎯 O Alvo do Dia
O programa lê a grade do mapa que fica no final do arquivo `.cub`, armazena em uma matriz `char **grid`, preenche as linhas menores com espaços para formar um retângulo uniforme e detecta a posição exata do jogador (`N`, `S`, `E` ou `W`).

### 🧠 Teoria: Matrizes Irregulares vs. Matrizes Uniformes
Arquivos `.cub` frequentemente contêm linhas de comprimentos desiguais:
```
111111
1001
100001111
111111111
```
Se você tentar acessar `grid[1][5]`, ocorrerá um **Segmentation Fault**!  
**A Solução de Normalização:** Encontre o maior comprimento de linha (`max_width`). Aloque todas as linhas com tamanho `max_width + 1` e preencha as lacunas com espaços `' '`. Dessa forma, o acesso `grid[y][x]` é sempre 100% seguro.

### 👥 Divisão de Trabalho
* **hcosta:** Leitura do mapa linha a linha acumulando em uma lista encadeada ou array dinâmico.
* **hcuessec:** Função de padronização retangular do mapa e extração das coordenadas do jogador e orientação inicial.

---

## DIA 5: Validação do Labirinto com Flood Fill (Zero Mapas Abertos)

### 🎯 O Alvo do Dia
O validador garante que o labirinto está **completamente cercado de paredes `'1'`**. Qualquer mapa que permita ao jogador "escapar" para o vazio deve imprimir `Error\n` e abortar a execução sem leaks.

### 🧠 Teoria: O Algoritmo de Flood Fill
Como garantir que um mapa de formato complexo está fechado?
1. Faça uma cópia da matriz do mapa.
2. Inicie a checagem a partir do ponto de spawn do jogador ou de cada `'0'`.
3. Se um espaço vazio `'0'` encostar na borda da matriz ou for adjacente a um espaço `' '`, o mapa **ESTÁ ABERTO**!

```
Exemplo de mapa inválido:
  111111
  100001
  10000   <-- Aberto! O '0' toca o espaço externo!
  111111
```

### 💻 Código Prático: Verificação de Adjacência Segura
```c
bool	is_valid_tile(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (false);
	if (map->grid[y][x] == ' ')
		return (false);
	return (true);
}

bool	check_walls_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (ft_strchr("0NSEWD", map->grid[y][x]))
			{
				if (!is_valid_tile(map, y - 1, x) || !is_valid_tile(map, y + 1, x)
					|| !is_valid_tile(map, y, x - 1) || !is_valid_tile(map, y, x + 1))
					return (false); // Furo na parede encontrado!
			}
			x++;
		}
		y++;
	}
	return (true);
}
```

### 👥 Divisão de Trabalho
* **hcosta:** Validação estrita de mapa fechado e garantia de que existe exatamente 1 jogador.
* **hcuessec:** Criar suite de testes em `maps/invalid/` (mapa sem paredes, 2 jogadores, mapa com letras aleatórias) e validar no terminal.

---

## DIA 6: A Matemática do Raycasting: Vetores e o Algoritmo DDA

### 🎯 O Alvo do Dia
O algoritmo **DDA (Digital Differential Analysis)** está completamente codificado e funcionando. Para cada uma das 1200 colunas da janela, um raio é lançado e detecta a distância perpendicular exata da parede.

### 🧠 Teoria Completa do DDA (Mastigada)

```
(posX, posY)
     o---------> rayDir
     | \
     |  \
     +---+---+  <- Linhas de Grade do Mapa
```

1. **`cameraX`:** Coordenada $x$ no espaço de câmera, variando de $-1$ (extremo esquerdo) a $+1$ (extremo direito).  
   $$\text{cameraX} = 2 \times \frac{x}{\text{largura}} - 1$$
2. **`rayDir`:** Direção vetorial do raio da coluna atual:  
   $$rayDirX = dirX + planeX \times cameraX$$  
   $$rayDirY = dirY + planeY \times cameraX$$
3. **`deltaDist`:** Distância que o raio percorre para cruzar 1 bloco completo:  
   $$deltaDistX = |1 / rayDirX|, \quad deltaDistY = |1 / rayDirY|$$
4. **`stepX / stepY`:** Direção do passo no grid (+1 ou -1).
5. **`sideDistX / sideDistY`:** Distância inicial até a primeira borda do bloco.

### 💻 Código Prático do Loop DDA
```c
void	init_ray(t_game *g, t_ray *r, int x)
{
	r->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.pos_x;
	r->map_y = (int)g->player.pos_y;
	r->delta_dist_x = (r->ray_dir_x == 0) ? 1e30 : fabs(1 / r->ray_dir_x);
	r->delta_dist_y = (r->ray_dir_y == 0) ? 1e30 : fabs(1 / r->ray_dir_y);
	r->hit = 0;
}

void	perform_dda(t_game *g, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
```

---

## DIA 7: Projeção de Paredes Sólidas, Shading e Fim da Semana 1

### 🎯 O Alvo do Dia
O labirinto 3D ganha vida na janela! Cada coluna da tela renderiza a altura proporcional da parede sem efeito de olho de peixe. As paredes possuem 4 cores sólidas para cada direção (N, S, E, W) e sombra nas faces horizontais.

### 🧠 Teoria: Eliminação do Fisheye e Altura da Parede
A distância perpendicular à câmera evita o arredondamento:
```c
if (r->side == 0)
	r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
else
	r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);

r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
if (r->draw_start < 0)
	r->draw_start = 0;
r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
if (r->draw_end >= WIN_HEIGHT)
	r->draw_end = WIN_HEIGHT - 1;
```

### 💻 Renderização com Shading Direcional
```c
int	get_wall_color(t_ray *r)
{
	int	color;

	if (r->side == 0 && r->ray_dir_x > 0)
		color = 0xFFFF00; // Oeste: Amarelo
	else if (r->side == 0 && r->ray_dir_x < 0)
		color = 0x0000FF; // Leste: Azul
	else if (r->side == 1 && r->ray_dir_y > 0)
		color = 0xFF0000; // Norte: Vermelho
	else
		color = 0x00FF00; // Sul: Verde
	if (r->side == 1)
		color = (color >> 1) & 0x7F7F7F; // Escurece 50% para efeito de sombra
	return (color);
}
```

> 🏆 **MARCO DO DIA 7:** Final da Semana 1! Vocês têm um motor 3D funcional que lê arquivos `.cub` e projeta o labirinto em cores puras!

---

# SEMANA 2: TEXTURAS, MOVIMENTO E CONGELAMENTO OBRIGATÓRIO (DIAS 8 A 14)

---

## DIA 8: Input Polling Anti-Stuttering e Eventos de Teclado

### 🎯 O Alvo do Dia
O jogo reage instantaneamente ao teclado. Pressionar e segurar `W`, `A`, `S`, `D` ou as setas não sofre com pausas ou atrasos do sistema operacional.

### 💻 Código Prático: O Padrão de Input Polling
```c
int	key_press(int keycode, t_game *g)
{
	if (keycode == 65307) // ESC no Linux
		clean_exit(g, 0);
	if (keycode == 'w' || keycode == 119)
		g->keys.w = true;
	if (keycode == 's' || keycode == 115)
		g->keys.s = true;
	if (keycode == 'a' || keycode == 97)
		g->keys.a = true;
	if (keycode == 'd' || keycode == 100)
		g->keys.d = true;
	if (keycode == 65361) // Seta Esquerda
		g->keys.rot_left = true;
	if (keycode == 65363) // Seta Direita
		g->keys.rot_right = true;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == 'w' || keycode == 119)
		g->keys.w = false;
	if (keycode == 's' || keycode == 115)
		g->keys.s = false;
	if (keycode == 'a' || keycode == 97)
		g->keys.a = false;
	if (keycode == 'd' || keycode == 100)
		g->keys.d = false;
	if (keycode == 65361)
		g->keys.rot_left = false;
	if (keycode == 65363)
		g->keys.rot_right = false;
	return (0);
}
```

---

## DIA 9: Cinemática Vetorial: Translação WASD e Rotação 2D

### 🎯 O Alvo do Dia
O jogador anda pelo labirinto suavemente com `WASD`, vira a cabeça com as setas esquerda e direita e não atravessa as paredes de tijolo `'1'`.

### 🧠 Teoria da Movimentação Vetorial
- **Frente / Trás:** Desloca ao longo do vetor de direção $\vec{dir}$:  
  $newX = posX \pm dirX \times speed$  
  $newY = posY \pm dirY \times speed$
- **Strafe (Lado):** Desloca ao longo do plano ortogonal $\vec{plane}$:  
  $newX = posX \pm planeX \times speed$  
  $newY = posY \pm planeY \times speed$
- **Rotação:** Multiplica os vetores $\vec{dir}$ e $\vec{plane}$ pela matriz de rotação 2D:  
  $$dirX' = dirX \cos(\alpha) - dirY \sin(\alpha)$$  
  $$dirY' = dirX \sin(\alpha) + dirY \cos(\alpha)$$

---

## DIA 10: Carregamento Seguro de Texturas XPM e Gestão de Imagens

### 🎯 O Alvo do Dia
As 4 imagens de textura (`NO`, `SO`, `WE`, `EA`) são carregadas na memória com `mlx_xpm_file_to_image`. O programa detecta se o arquivo XPM está corrompido ou tem dimensões incompatíveis e sai sem vazamentos.

### 💻 Código Prático: Carregamento Seguro
```c
void	load_one_texture(t_game *g, t_texture *tex, char *path)
{
	tex->img.img_ptr = mlx_xpm_file_to_image(g->mlx_ptr, path,
			&tex->img.width, &tex->img.height);
	if (!tex->img.img_ptr)
		error_exit("Falha ao carregar textura XPM", g);
	tex->img.data_addr = mlx_get_data_addr(tex->img.img_ptr,
			&tex->img.bpp, &tex->img.line_len, &tex->img.endian);
	if (!tex->img.data_addr)
		error_exit("Falha ao obter dados da textura", g);
}
```

---

## DIA 11: Mapeamento UV nas Paredes (WallX, TexX e TexY)

### 🎯 O Alvo do Dia
O visual clássico do *Wolfenstein 3D* surge na tela: as texturas reais de tijolo, pedra e madeira cobrem as paredes perfeitamente alinhadas e sem distorções de perspectiva.

### 🧠 Teoria: Calculando a Coordenada Exata da Textura
1. **`wallX`:** Onde exatamente na parede o raio bateu (número fracionário de $0.0$ a $1.0$):
   ```c
   if (r->side == 0)
       wall_x = g->player.pos_y + r->perp_wall_dist * r->ray_dir_y;
   else
       wall_x = g->player.pos_x + r->perp_wall_dist * r->ray_dir_x;
   wall_x -= floor(wall_x);
   ```
2. **`texX`:** Coluna correspondente na imagem de 64x64 da textura:
   ```c
   tex_x = (int)(wall_x * (double)tex->width);
   if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1 && r->ray_dir_y < 0))
       tex_x = tex->width - tex_x - 1; // Inverte para não ficar espelhada
   ```
3. **Interpolação Vertical de `texY`:**
   ```c
   double step = 1.0 * tex->height / r->line_height;
   double tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
   for (int y = r->draw_start; y < r->draw_end; y++) {
       int tex_y = (int)tex_pos & (tex->height - 1);
       tex_pos += step;
       int color = *(int *)(tex->data_addr + (tex_y * tex->line_len + tex_x * 4));
       my_pixel_put(&g->frame, x, y, color);
   }
   ```

---

## DIA 12: Refatoração Estrita para a Norminette 42

### 🎯 O Alvo do Dia
Todo o código da pasta `src/` e `include/` passa **100% liso na `norminette`** (0 erros, 0 avisos).

### 🛠️ Regras de Ouro da Norma:
1. Máximo de 25 linhas por função.
2. Máximo de 5 variáveis locais por função.
3. Máximo de 4 argumentos por função.
4. Nenhuma atribuição na mesma linha que a declaração.
5. Agrupar variáveis relacionadas em structs para não estourar o limite de 4 parâmetros.

---

## DIA 13: Bateria de Testes com Valgrind e Tratamento de Erros

### 🎯 O Alvo do Dia
O programa é submetido a dezenas de testes de estresse com Valgrind. Nenhum mapa malformado, nenhum fechamento de janela e nenhum erro causa *Segmentation Fault*, *Double Free* ou vazamento de memória (*leaks*).

### 🧪 Comandos de Teste com Valgrind
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d maps/valid/simple.cub
valgrind --leak-check=full ./cub3d maps/invalid/no_map.cub
valgrind --leak-check=full ./cub3d maps/invalid/open_wall.cub
valgrind --leak-check=full ./cub3d maps/invalid/bad_colors.cub
```
> **Critério de Aprovação:** `All heap blocks were freed -- no leaks are possible`.

---

## DIA 14: O Marco v1.0: Congelamento da Parte Obrigatória (Nota 100 Garantida)

### 🎯 O Alvo do Dia
A parte obrigatória do projeto está **100% COMPLETA E PERFEITA**.  
Faz-se o merge na branch principal e cria-se a tag de segurança no Git.

```bash
git checkout develop
git merge --no-ff feature/phase-6-mandatory-audit
git checkout main
git merge --no-ff develop
git tag -a v1.0-mandatory -m "Parte Obrigatoria 100% Finalizada e Validada com Zero Leaks"
git push origin main develop --tags
```

> 🛡️ **Lembrete do Subject:** Os bónus só são avaliados se o obrigatório estiver impecável. Se vocês precisarem entregar agora, já têm aprovação com nota máxima na parte obrigatória!

---

# SEMANA 3: OS 5 BÓNUS E AVALIAÇÃO FINAL (DIAS 15 A 21)

---

## DIA 15: Bónus 1 — Bounding Box e Deslizamento nas Paredes (Wall Sliding)

### 🎯 O Alvo do Dia
O jogador não trava abruptamente ao andar em quinas e paredes diagonais: ele **desliza suavemente** pela parede. O jogador possui uma caixa de colisão física (*bounding box*) de 0.2 unidades.

### 💻 Código Prático: Deslizamento em Eixos Independentes
```c
#define COLLISION_DIST 0.2

void	move_with_sliding(t_game *g, double move_x, double move_y)
{
	double	check_x;
	double	check_y;

	// Testa eixo X de forma independente
	check_x = (move_x > 0) ? move_x + COLLISION_DIST : move_x - COLLISION_DIST;
	if (g->map.grid[(int)g->player.pos_y][(int)(g->player.pos_x + check_x)] != '1')
		g->player.pos_x += move_x;

	// Testa eixo Y de forma independente
	check_y = (move_y > 0) ? move_y + COLLISION_DIST : move_y - COLLISION_DIST;
	if (g->map.grid[(int)(g->player.pos_y + check_y)][(int)g->player.pos_x] != '1')
		g->player.pos_y += move_y;
}
```

---

## DIA 16: Bónus 2 — Minimapa 2D com Radar e Cone de Visão

### 🎯 O Alvo do Dia
Um minimapa elegante no canto superior do ecrã exibe a vizinhança do labirinto ao redor do jogador, a posição atual e uma linha indicando a direção para onde ele está a olhar.

### 💻 Implementação do Minimapa no Framebuffer
```c
#define MINI_SIZE 150
#define MINI_SCALE 10

void	draw_minimap(t_game *g)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	for (y = 0; y < MINI_SIZE; y++)
	{
		for (x = 0; x < MINI_SIZE; x++)
		{
			map_x = (int)(g->player.pos_x) + (x - MINI_SIZE / 2) / MINI_SCALE;
			map_y = (int)(g->player.pos_y) + (y - MINI_SIZE / 2) / MINI_SCALE;
			if (map_x >= 0 && map_x < g->map.width && map_y >= 0 && map_y < g->map.height)
			{
				if (g->map.grid[map_y][map_x] == '1')
					my_pixel_put(&g->frame, x + 10, y + 10, 0x444444); // Parede
				else
					my_pixel_put(&g->frame, x + 10, y + 10, 0x111111); // Vazio
			}
		}
	}
	// Desenha o jogador no centro do minimapa (Ponto vermelho)
	my_pixel_put(&g->frame, 10 + MINI_SIZE / 2, 10 + MINI_SIZE / 2, 0xFF0000);
}
```

---

## DIA 17: Bónus 3 — Sistema de Portas Interativas ('D')

### 🎯 O Alvo do Dia
O mapa aceita o caractere `'D'`. Ao aproximar-se de uma porta fechada e pressionar a tecla `E` ou `Espaço`, a porta abre-se (permitindo a passagem de raios e movimento do jogador) ou fecha-se.

### 💻 Lógica de Interação com Portas
```c
void	toggle_door(t_game *g)
{
	int	front_x = (int)(g->player.pos_x + g->player.dir_x * 1.2);
	int	front_y = (int)(g->player.pos_y + g->player.dir_y * 1.2);

	if (g->map.grid[front_y][front_x] == 'D')
		g->map.grid[front_y][front_x] = 'O'; // Open (Aberta)
	else if (g->map.grid[front_y][front_x] == 'O')
	{
		// Só fecha se o jogador não estiver parado dentro da porta!
		if ((int)g->player.pos_x != front_x || (int)g->player.pos_y != front_y)
			g->map.grid[front_y][front_x] = 'D'; // Fechada
	}
}
```

---

## DIA 18: Bónus 4 — Rotação Suave com o Mouse (Mouse Look)

### 🎯 O Alvo do Dia
O jogador pode girar a visão livremente movimentando o rato para a esquerda e para a direita, tal como num jogo FPS moderno de computador.

### 💻 Hook do Rato no Linux com a MiniLibX
```c
int	mouse_move(int x, int y, t_game *g)
{
	(void)y;
	static int	prev_x = WIN_WIDTH / 2;
	int			delta_x;
	double		rot;

	delta_x = x - prev_x;
	prev_x = x;
	if (delta_x != 0)
	{
		rot = delta_x * 0.003; // Sensibilidade
		rotate_player(g, rot);
	}
	// Se o mouse sair perto da borda, centraliza de volta
	if (x < 100 || x > WIN_WIDTH - 100)
	{
		mlx_mouse_move(g->mlx_ptr, g->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		prev_x = WIN_WIDTH / 2;
	}
	return (0);
}
```

---

## DIA 19: Bónus 5 (Parte 1) — O Z-Buffer e Ordenação de Sprites

### 🎯 O Alvo do Dia
O motor implementa um **Z-Buffer (Depth Buffer)** para registrar a distância exata de cada coluna de parede. Sprites distantes são ordenados antes dos próximos (*Painter's Algorithm*).

### 🧠 Teoria do Z-Buffer
Para cada coluna $x$ de $0$ a $WIN\_WIDTH - 1$, guardamos no array:
```c
g->z_buffer[x] = r->perp_wall_dist;
```
Quando formos desenhar um sprite na coluna $x$, só desenhamos o pixel se:
$$\text{distância\_do\_sprite} < \text{z\_buffer}[x]$$
Isso impede que uma tocha ou monstro seja visto através de uma parede de tijolos!

---

## DIA 20: Bónus 5 (Parte 2) — Projeção de Sprites Animadas e Transparência

### 🎯 O Alvo do Dia
Tochas medievais animadas cintilam nas paredes do labirinto! O fundo transparente da imagem do sprite não desenha nenhum pixel, revelando a textura da parede ou o chão.

### 💻 Projeção de Sprite pela Matriz Inversa da Câmera
```c
void	render_sprites(t_game *g)
{
	// 1. Transformação de coordenadas pela matriz inversa da câmera
	double inv_det = 1.0 / (g->player.plane_x * g->player.dir_y - g->player.dir_x * g->player.plane_y);
	double transform_x = inv_det * (g->player.dir_y * sprite_x - g->player.dir_x * sprite_y);
	double transform_y = inv_det * (-g->player.plane_y * sprite_x + g->player.plane_x * sprite_y);

	int sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));
	// 2. Desenha colunas se transform_y > 0 e transform_y < z_buffer[stripe]
}
```

---

## DIA 21: README Oficial (Subject Cap VI), Makefile Bonus e Simulação da Defesa

### 🎯 O Alvo do Dia
Projeto **100% finalizado com todos os 5 bónus**, README rigorosamente preenchido no padrão exigido pelo Capítulo VI do subject, e simulação de avaliação por pares.

### 📝 Estrutura Obrigatória do `README.md`
```markdown
*Este projeto foi criado como parte do currículo da 42 por hcosta, hcuessec*

## Descrição
O Maze Runner (cub3D) é um motor gráfico de raycasting em primeira pessoa...

## Instruções
- Compilação: make bonus
- Execução: ./cub3d maps/valid/dungeon.cub

## Recursos e Declaração de Uso de IA
- Algoritmo DDA baseado no tutorial de Lode Vandevenne.
- A IA foi utilizada para estruturar o roadmap inicial de tarefas e auxiliar na arquitetura do pipeline de testes com Valgrind. Todo o código e matemática foram verificados e compreendidos pelos autores.
```

---

## APÊNDICE A: GUIA DE SOBREVIVÊNCIA NA AVALIAÇÃO POR PARES

Durante a defesa oficial do cub3D, o avaliador pode pedir que você realize uma **modificação ao vivo de código** em 5 a 10 minutos (conforme especificado no Capítulo IX do subject).

### As 5 Perguntas/Modificações mais comuns:
1. **"Mude a velocidade do jogador ou a velocidade de rotação."**
   * *Onde mudar:* Vá em `init_player()` e altere `player->move_speed = 0.05;` para `0.1;`.
2. **"Inverta a direção dos raios ou altere a cor do teto dinamicamente."**
   * *Onde mudar:* No parser ou no render do céu/chão.
3. **"Explique por que ocorre o efeito de olho de peixe e aponte no código onde você o removeu."**
   * *Resposta:* Mostre a variável `perp_wall_dist`. Explique que a distância euclidiana mede a hipotenusa de um triângulo, enquanto a distância perpendicular projeta o impacto sobre o vetor do plano de visão da câmera.
4. **"Como você evita vazamentos de memória se o mapa estiver corrompido na última linha?"**
   * *Resposta:* Mostre a função `clean_exit(game, exit_code)`. Demonstre que todas as texturas carregadas recebem `mlx_destroy_image`, a matriz recebe `free_matrix()` e o display é finalizado com `mlx_destroy_display`.
5. **"Como o Z-Buffer funciona no bónus de sprites?"**
   * *Resposta:* Mostre o array `z_buffer[x]`. Explique que ele armazena a profundidade da parede em cada fatia vertical e que o sprite só é desenhado se `transform_y < z_buffer[x]`.

---

## APÊNDICE B: TABELA PERIÓDICA DE KEYCODES NO LINUX (X11)

| Ação | Tecla | Keycode Decimal (Linux/X11) |
| :--- | :--- | :--- |
| **Mover para Frente** | `W` / `w` | `119` |
| **Mover para Trás** | `S` / `s` | `115` |
| **Mover para Esquerda (Strafe)** | `A` / `a` | `97` |
| **Mover para Direita (Strafe)** | `D` / `d` | `100` |
| **Girar Câmera para Esquerda** | Seta Esquerda (`<-`) | `65361` |
| **Girar Câmera para Direita** | Seta Direita (`->`) | `65363` |
| **Sair do Jogo** | `ESC` | `65307` |
| **Interagir com Portas (Bónus)** | `E` / `e` ou `Espaço` | `101` ou `32` |

---

*Parabéns por aceitar o desafio! Sigam este livro dia a dia e vocês conquistarão os 125% com louvor.*
