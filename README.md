# cub3D — Maze Runner

Implementação do projeto **cub3D** do currículo 42: um motor de raycasting em C
com texturas XPM, movimentação em primeira pessoa, colisão, minimapa, portas
deslizantes, sprites animados e mouse look.

O projeto possui dois builds que geram **um único executável `cub3d`**:

- **obrigatório** (`make`): engine base do cub3D;
- **bônus** (`make bonus`): todos os recursos extras habilitados.

O último modo compilado é o que fica disponível em `./cub3d` (o modo atual é
registrado no arquivo `.build_mode`).

## Requisitos

- Linux com servidor X11;
- `make`;
- `cc` (gcc-12 neste ambiente);
- bibliotecas de desenvolvimento `libX11`, `libXext` e `zlib`;
- MiniLibX e Libft incluídas neste repositório.

## Compilação

```sh
make            # build obrigatório, gera ./cub3d
make bonus      # build bônus, gera ./cub3d (substitui o obrigatório)
make re         # limpa e recompila o build obrigatório
make fclean     # remove binários e objetos
```

Os dois builds produzem o mesmo executável, `cub3d`, e usam diretórios de
objetos separados (`obj/` e `obj_bonus/`):

```sh
make        # ./cub3d = versão obrigatória
make bonus  # ./cub3d = versão bônus
```

Trocar de modo recompila apenas o necessário e reescreve `cub3d` com os
objetos do modo pedido; repetir o mesmo `make` não força relink.

## Execução

```sh
make bonus
./cub3d menu                    # menu inicial (bônus completo)
./cub3d maps/valid/arena.cub    # jogo direto, sem menu
```

### Modo menu (`./cub3d menu`)

Abre um menu inicial com os 14 mapas do projeto (válidos e inválidos) e libera
os recursos de interface do bônus:

- escolha de mapa com o mouse ou `↑`/`↓` + `Enter`;
- mapas inválidos mostram a mensagem de erro e o menu permanece aberto;
- `F` alterna fullscreen e `P`/`Esc` pausa o jogo (com menu de pausa);
- logs de teclado, mouse e validação de mapas no terminal.

### Modo direto (`./cub3d maps/...`)

O jogo começa imediatamente no mapa indicado. Nesse modo ficam disponíveis
apenas o jogo em si:

- `Esc` (ou fechar a janela) encerra o jogo;
- `E`/`Espaço` interagem com portas;
- clique esquerdo atira e os inimigos atacam o jogador;
- o cursor do mouse fica livre (sem captura), permitindo fechar pelo `X`;
- pause, fullscreen e menu **não** funcionam (não há estado de menu);
- ao morrer, aparece um aviso curto (`YOU DIED`) e `Esc` encerra.

`maps/valid/arena.cub` é o mapa recomendado para demonstrar o bônus completo:
12 inimigos, tochas animadas e uma porta.

## Controles

| Tecla / ação        | Efeito                                               |
|---------------------|------------------------------------------------------|
| `W` / `S`           | mover para frente / para trás                        |
| `A` / `D`           | mover para a esquerda / direita                      |
| `←` / `→`           | rotacionar a câmera                                  |
| mouse (horizontal)  | girar a câmera; o cursor fica fixo no centro (bônus) |
| clique esquerdo     | atirar (bônus)                                       |
| `E` ou `Espaço`     | abrir/fechar porta à frente (bônus)                  |
| `F`                 | ligar/desligar fullscreen (somente modo menu)        |
| `P` ou `Esc`        | pausar (somente modo menu; no modo direto `Esc` sai) |
| `R`                 | reiniciar o nível (pause/morte, modo menu)           |
| `M` ou `Esc`        | voltar ao menu inicial (pause, modo menu)            |
| `Q`                 | sair (pause/morte, modo menu)                        |
| `↑` / `↓` + `Enter` | escolher mapa no menu inicial                        |
| fechar janela       | sair                                                 |

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
2. **Minimapa circular** — radar translúcido de `260x260` pixels no canto
   inferior esquerdo, desenhado em recorte circular, centrado no jogador e sem
   fundo opaco. Gira junto com a câmera (frente para cima), rola conforme o
   jogador anda e mostra apenas o alcance ao redor dele: paredes, portas,
   tochas e inimigos em cores distintas, além do marcador do jogador no centro.
3. **Portas deslizantes** — tiles `D`; interação com `E`/`Espaço` a até `1.5`
   unidades. A porta desliza a `1.5` unidades por segundo, o DDA atravessa a
   parte aberta, a textura acompanha o deslocamento e a porta não fecha sobre o
   jogador.
4. **Sprites animados** — tiles `T` com cinco texturas de tocha animadas,
   transparência por magenta `#FF00FF`, ordenação de trás para frente e oclusão
   pelo z-buffer das paredes.
5. **Mouse look** — em jogo o cursor fica capturado no centro da janela: cada
   evento de movimento vira uma rotação proporcional da câmera e o cursor é
   recentralizado; no menu e na pausa o cursor volta a ficar livre para clicar.
6. **Inimigos** — aranhas e zumbis em pixel art, desenhados como sprites
   animados com os estados *walk*, *attack*, *hurt* e *die*. Nascem
   automaticamente em tiles livres ao redor do jogador (até 12 por nível),
   perseguem o jogador quando o veem, atacam em corpo a corpo e podem ser
   mortos a tiro.
7. **HUD, arma e vida** — arma desenhada como sprites de mãos com animação de
   disparo, barra de vida que diminui quando o jogador apanha, flash vermelho
   no dano e retículo/contadores no HUD.
8. **Menu inicial e modo direto** — o bônus só é completo quando iniciado por
   `./cub3d menu` (menu com a lista de mapas, validação com mensagens de erro e
   opções de entrar/sair). Iniciar com um mapa direto entrega apenas o jogo
   (sem pausa, menu ou fullscreen).
9. **Pausa e morte** — `P`/`Esc` congela o jogo com um painel escurecido e
   três botões (retomar/reiniciar, menu inicial, sair). A morte mostra o mesmo
   painel; no modo direto aparece apenas um aviso curto e `Esc` encerra.
10. **Fullscreen com framebuffer real** — `F` alterna para tela cheia: além do
    pedido EWMH (`_NET_WM_STATE_FULLSCREEN`) e do redimensionamento da janela
    por X11, o **framebuffer é recriado no tamanho exato da janela** (por
    exemplo `1920x1080`) e o jogo passa a renderizar nessa resolução — a imagem
    ocupa a tela inteira, sem faixas pretas. Ao sair, tudo volta a `1200x800`
    em `(40,40)`. O mesmo caminho trata o redimensionamento manual da janela
    (hook `ConfigureNotify`), e todo o layout — colunas e botões do menu,
    painel de pausa, HUD, arma, mira e minimapa — é recalculado a partir do
    tamanho atual do framebuffer.
11. **Logs no terminal** — teclas, botões do mouse, seleção/validação de mapas,
    eventos de combate e o desempenho (`[perf] <frames> frames in <ms> ms
    (<fps> fps)`, a cada 5 s no modo menu) são impressos no `stdout` para
    depuração.

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

Os inimigos do bônus não usam símbolo no mapa: eles surgem automaticamente em
tiles andáveis ao redor do jogador (até 12), segundo uma grade determinística,
em qualquer mapa rodado no build bônus.

## Mapas de exemplo

### Válidos

- `maps/valid/minimal.cub` — mapa mínimo;
- `maps/valid/simple.cub` — mapa básico para o build obrigatório;
- `maps/valid/complex_shape.cub` — paredes em formato irregular;
- `maps/valid/bonus_doors.cub` — duas salas separadas por porta;
- `maps/valid/bonus_sprites.cub` — duas tochas animadas visíveis no spawn;
- `maps/valid/bonus_all.cub` — porta + tocha + minimapa + mouse look;
- `maps/valid/arena.cub` — arena com 12 inimigos e uma porta.

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
src/bonus/        bônus (menu, inimigos, HUD) e stubs do build obrigatório
textures/         texturas XPM das paredes e porta
textures/bonus/   XPM do bônus (tochas, sprites, arma e inimigos)
maps/             mapas válidos e inválidos
```

### Build duplo sem `#ifdef`

O build obrigatório e o bônus compartilham o código base. O build obrigatório
linka `src/bonus/stub_bonus.c`, `src/bonus/stub2_bonus.c` e
`src/bonus/stub_ray_bonus.c`, que fornecem implementações vazias para os pontos
de extensão. O build bônus remove esses stubs e linka os arquivos reais
`*_bonus.c`. Assim, não é necessário usar diretivas de pré-processador dentro de
funções nem uma flag `-DBONUS` no compilador. Os dois builds usam diretórios de
objetos separados (`obj/` e `obj_bonus/`) e gravam o mesmo `cub3d`.

## Qualidade e validação

- **Norminette:** `norminette src include` sem erros;
- **Compilação:** `make re` e `make bonus` sem erros ou warnings do código do
  projeto (o único warning é interno da MiniLibX); os dois modos geram apenas
  o executável `cub3d`;
- **Valgrind:** `All heap blocks were freed -- no leaks are possible` nos
  fluxos testados, incluindo `Esc`, fechamento da janela, erros de textura,
  abertura/fechamento de portas, sprites, menu inicial, pausa e morte;
- o único erro reportado pelo Valgrind é o conhecido byte não inicializado no
  `writev` interno da MiniLibX/X11 durante a criação da janela, fora do código
  do projeto.

Exemplos de validação:

```sh
make bonus
valgrind --leak-check=full --show-leak-kinds=all ./cub3d menu
valgrind --leak-check=full --show-leak-kinds=all ./cub3d maps/valid/arena.cub
```

## Desempenho

O projeto compila **sem nenhuma flag de otimização** (apenas `-Wall -Wextra
-Werror`); todo o ganho vem do código:

- paredes, chão/teto, sprites, arma e HUD usam aritmética de **ponto fixo
  16.16** e escrevem direto nos ponteiros do framebuffer (sem `my_pixel_put`
  por pixel, sem `double` no laço interno);
- o preenchimento de áreas planas usa `img_fill` com **stores de 64 bits** (dois
  pixels por escrita, já que o framebuffer é 32bpp);
- o sombreamento das paredes laterais é feito com máscara e deslocamento
  (`(c & 0xFCFCFC) - ((c & 0xFCFCFC) >> 2)`), sem multiplicações;
- o minimapa desenha linhas inteiras de uma vez, a borda circular em *spans*
  simétricos e o marcador do jogador em treze *spans*;
- não existem variáveis globais de layout: o bônus calcula a posição de menus,
  botões e HUD a partir de `game->frame.width/height`.

Medições nesta máquina (Intel i7-7500U, 2 núcleos, `-O0`, modo menu):

| cenário                                   | resolução | fps (≈) |
|-------------------------------------------|-----------|---------|
| menu de mapas                             | 1200x800  | 250     |
| arena em jogo (janela)                    | 1200x800  | 155     |
| arena em jogo (fullscreen)                | 1920x1080 | 56–138  |
| arena em jogo (fullscreen, 12 inimigos no corpo a corpo) | 1920x1080 | 32–46 |
| estado de morte (sem render do mundo)     | 1920x1080 | 300+    |
| sob `valgrind` (menu / pausa)             | 1200x800  | 77 / 49 |

Antes desta passagem de otimização, a mesma arena rodava a **19–29 fps** em
`1200x800`. O `[perf]` impresso a cada 5 s permite repetir a medição.

## Funções externas

Além das funções permitidas na parte obrigatória (`open`, `close`, `read`,
`write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`,
`gettimeofday`, funções de `<math.h>` e a MiniLibX), o bônus usa chamadas de
X11 — `XMoveResizeWindow`, `XInternAtom`, `XSendEvent`, `XSetWMNormalHints`,
`XGetWindowAttributes` e `XFlush` — para implementar o fullscreen via EWMH
(`_NET_WM_STATE_FULLSCREEN`), alternativa que a MiniLibX não oferece, e a
MiniLibX fornece `mlx_get_screen_size` para ler a resolução do ecrã. Esse uso de
X11 fica isolado em `src/bonus/fullscreen_bonus.c` e em
`src/bonus/resize_bonus.c`, e só é alcançável pelo `F` (modo menu: em jogo e na
pausa).

## Créditos

Projeto desenvolvido para o currículo 42 por **hcosta**. MiniLibX e Libft são
bibliotecas fornecidas pelo campus 42.
