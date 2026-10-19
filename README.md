# cub3D — Maze Runner

Implementação do projeto **cub3D** do currículo 42: um motor de raycasting em C
com texturas XPM, movimentação em primeira pessoa, colisão, minimapa, portas
deslizantes, sprites animados e mouse look.

O projeto possui dois builds separados:

- **obrigatório** (`make`): engine base do cub3D;
- **bônus** (`make bonus`): todos os recursos extras habilitados.

## Requisitos

- Linux com servidor X11;
- `make`;
- `cc` (gcc-12 neste ambiente);
- bibliotecas de desenvolvimento `libX11`, `libXext` e `zlib`;
- MiniLibX e Libft incluídas neste repositório.

## Compilação

```sh
make            # build obrigatório; gera cub3d_mandatory e copia para cub3d
make bonus      # build bônus; gera cub3d_bonus e copia para cub3d
make re         # limpa e recompila o build obrigatório
make fclean     # remove binários e objetos
```

Os dois binários ficam disponíveis:

```sh
./cub3d_mandatory maps/valid/simple.cub
./cub3d_bonus     maps/valid/bonus_all.cub
```

Como `cub3d` é uma cópia do último build compilado, para executar o bônus com
certeza use `make bonus` antes de `./cub3d ...`.

## Execução

```sh
make bonus
./cub3d maps/valid/bonus_all.cub
```

`maps/valid/bonus_all.cub` é o mapa recomendado para demonstrar todos os
recursos bônus em conjunto: o jogador começa diante de uma porta e, ao abri-la,
vê uma tocha animada na sala seguinte.

## Controles

| Tecla / ação       | Efeito                                      |
|--------------------|---------------------------------------------|
| `W` / `S`          | mover para frente / para trás               |
| `A` / `D`          | mover para a esquerda / direita             |
| `←` / `→`          | rotacionar a câmera                         |
| mouse (horizontal) | rotacionar a câmera (build bônus)           |
| `E` ou `Espaço`    | abrir/fechar porta à frente (build bônus)    |
| `Esc`              | sair                                        |
| fechar janela      | sair                                        |

## Funcionalidades

### Parte obrigatória

- Parsing de arquivos `.cub` com texturas `NO`, `SO`, `WE`, `EA` e cores de
  chão (`F`) e teto (`C`) em RGB;
- validação de mapa fechado, exatamente um spawn e caracteres permitidos;
- raycasting com DDA e projeção de paredes;
- texturas XPM nas quatro orientações, com correção de perspectiva;
- movimentação suave com `WASD` e rotação;
- tratamento de erros com `Error\n<mensagem>` no `stderr` e código de saída
  diferente de zero.

### Bônus

1. **Colisão com deslizamento** — raio de colisão de `0.20` unidades e
   movimento separado nos eixos X e Y, permitindo deslizar ao longo das paredes.
   O código de colisão é compartilhado e também está ativo no build obrigatório.
2. **Minimapa** — HUD opaco de `195x195` pixels no canto superior esquerdo,
   com tiles de `15px`, paredes, portas, chão, sprites, jogador e direção.
3. **Portas deslizantes** — tiles `D`; interação com `E`/`Espaço` a até `1.5`
   unidades. A porta desliza a `1.5` unidades por segundo, o DDA atravessa a
   parte aberta, a textura acompanha o deslocamento e a porta não fecha sobre o
   jogador.
4. **Sprites animados** — tiles `T` com quatro texturas de tocha animadas a
   cada `0.15s`, transparência por magenta `#FF00FF`, ordenação de trás para
   frente e oclusão pelo z-buffer das paredes.
5. **Mouse look** — rotação horizontal proporcional ao deslocamento do mouse,
   com recentralização do cursor e proteção contra eventos de inicialização.

## Formato de mapa

Exemplo mínimo:

```text
NO textures/wall_north.xpm
SO textures/wall_south.xpm
WE textures/wall_west.xpm
EA textures/wall_east.xpm

F 220,100,0
C 25,30,65

11111111
10000001
10011001
100N0001
11111111
```

Símbolos do mapa:

| Símbolo | Significado                                      |
|---------|--------------------------------------------------|
| `0`     | chão                                             |
| `1`     | parede                                           |
| `N/S/E/W` | spawn e direção inicial do jogador             |
| `D`     | porta deslizante (bônus)                         |
| `T`     | tocha animada (bônus)                            |
| espaço  | vazio externo (não pode encostar em área andável)|

O mapa deve ser fechado por paredes, conter exatamente um spawn e usar apenas
os caracteres acima.

## Mapas de exemplo

### Válidos

- `maps/valid/minimal.cub` — mapa mínimo;
- `maps/valid/simple.cub` — mapa básico para o build obrigatório;
- `maps/valid/complex_shape.cub` — paredes em formato irregular;
- `maps/valid/bonus_doors.cub` — duas salas separadas por porta;
- `maps/valid/bonus_sprites.cub` — duas tochas animadas visíveis no spawn;
- `maps/valid/bonus_all.cub` — porta + tocha + minimapa + mouse look.

### Inválidos

`maps/invalid/` contém casos de erro para validar o parser: caractere inválido,
mapa aberto, ausência de jogador, dois jogadores, textura ausente e cor inválida.
Todos devem terminar com:

```text
Error
<mensagem>
```

e código de saída `1`.

## Estrutura

```text
include/          cabeçalhos e structs
src/parsing/      parser e validação do .cub
src/raycasting/   DDA e projeção das paredes
src/render/       framebuffer, chão/teto e texturas
src/player/       movimento, rotação e colisão
src/events/       teclado e fechamento da janela
src/bonus/        bônus e stubs usados no build obrigatório
textures/         texturas XPM (paredes, porta e tochas)
maps/             mapas válidos e inválidos
```

### Build duplo sem `#ifdef`

O build obrigatório e o bônus compartilham o código base. O build obrigatório
linka `src/bonus/stub_bonus.c` e `src/bonus/stub_ray_bonus.c`, que fornecem
implementações vazias para os pontos de extensão. O build bônus remove esses
stubs e linka os arquivos reais `*_bonus.c`. Assim, não é necessário usar
diretivas de pré-processador dentro de funções nem uma flag `-DBONUS` no
compilador. Os dois builds usam diretórios de objetos separados (`obj/` e
`obj_bonus/`).

## Qualidade e validação

- **Norminette:** `norminette src include` sem erros;
- **Compilação:** `make re` e `make bonus` sem erros ou warnings do código do
  projeto (o único warning é interno da MiniLibX);
- **Valgrind:** `0 bytes in use at exit` e `All heap blocks were freed` nos
  fluxos testados, incluindo `Esc`, fechamento da janela, erros de textura,
  abertura/fechamento de portas e sprites;
- o único erro reportado pelo Valgrind é o conhecido byte não inicializado no
  `writev` interno da MiniLibX/X11 durante a criação da janela, fora do código
  do projeto.

Exemplo de validação:

```sh
make bonus
valgrind --leak-check=full --show-leak-kinds=all \
  ./cub3d maps/valid/bonus_all.cub
```

## Créditos

Projeto desenvolvido para o currículo 42 por **hcosta**. MiniLibX e Libft são
bibliotecas fornecidas pelo campus 42.
