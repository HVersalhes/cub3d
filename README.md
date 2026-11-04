# cub3D

Implementação da **parte obrigatória** do projeto **cub3D** do currículo 42:
um pequeno motor de raycasting em C, com janela MiniLibX, paredes texturizadas,
movimento em primeira pessoa, colisão e validação de mapas no formato `.cub`.

Autores: **hcosta** e **hcuessec**.

## Requisitos

- Linux com servidor X11;
- `make`;
- compilador de C em modo C99 (`cc`);
- bibliotecas de desenvolvimento `libX11` e `libXext`;
- MiniLibX e Libft incluídas neste repositório.

Além das bibliotecas incluídas, o projeto usa a biblioteca matemática
(`-lm`) e as bibliotecas do sistema X11/Xext exigidas pela MiniLibX.

## Compilação

```sh
make          # compila e gera ./cub3d
make re       # limpa tudo e compila novamente
make clean    # remove os objetos
make fclean   # remove os objetos, bibliotecas e o executável
```

O `Makefile` foi escrito para ser simples: compila os ficheiros de `src/`,
compila a `libft` e a MiniLibX e liga tudo num único executável chamado
`cub3d`. Não existem alvos nem ficheiros de configuração para modos
alternativos.

As únicas flags de compilação adicionadas ao código do projeto são
`-Wall -Wextra -Werror`. Não é usada nenhuma flag de otimização nem uma flag
`-std` explícita, porque o ambiente já compila em C99.

## Execução

```sh
./cub3d maps/valid/simple.cub
```

O programa recebe exatamente um argumento: o caminho de um ficheiro `.cub`.
Se o ficheiro não existir, se o mapa for inválido ou se faltar algum elemento
obrigatório, o programa imprime

```text
Error
<mensagem>
```

no `stderr` e termina com código de saída diferente de zero.

## Controlos

| Tecla / ação   | Efeito                                  |
|----------------|-----------------------------------------|
| `W` / `S`      | andar para a frente / para trás         |
| `A` / `D`      | andar para a esquerda / direita         |
| `←` / `→`      | rodar a câmara                          |
| `Esc`          | sair do jogo                            |
| fechar janela  | sair do jogo                            |

O movimento usa a direção e o plano da câmara, por isso andar para os lados
é sempre perpendicular à direção em que o jogador está a olhar. A colisão é
testada nos quatro cantos de um pequeno quadrado à volta do jogador; se um
eixo estiver bloqueado, o outro continua livre, permitindo deslizar ao longo
das paredes.

## Registo de ações

As ações são escritas no terminal com `ft_printf`. Cada tecla de movimento ou
rotação regista uma única linha quando é pressionada, por exemplo:

```text
[cub3d] move forward
[cub3d] strafe left
[cub3d] rotate left
```

O `ESC` e o botão de fechar a janela (`X`) também registam o motivo da saída:

```text
[cub3d] exit (ESC)
[cub3d] exit (X)
```

O auto-repeat do teclado é desativado enquanto o jogo está aberto e reposto na
saída, para que manter uma tecla pressionada produza apenas uma mensagem.

## Funcionalidades

- leitura de ficheiros `.cub` com texturas `NO`, `SO`, `WE`, `EA` e cores
  `F` (chão) e `C` (teto);
- validação de texturas, cores RGB, caracteres do mapa, limites do mapa e
  existência de exatamente um ponto de spawn;
- raycasting com o algoritmo DDA e projeção vertical das paredes;
- texturas XPM nas quatro orientações, com correção de perspetiva;
- chão e teto preenchidos com as cores definidas no mapa;
- movimento suave com `WASD`, rotação com as setas e colisão com paredes;
- gestão de eventos da MiniLibX (teclado e fecho da janela);
- libertação completa de memória em todos os caminhos de saída.

## Formato do mapa

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

Os seis elementos de cabeçalho (`NO`, `SO`, `WE`, `EA`, `F` e `C`) têm de
aparecer antes do mapa. As cores usam três canais entre 0 e 255.

Símbolos permitidos no mapa:

| Símbolo   | Significado                                  |
|-----------|----------------------------------------------|
| `0`       | chão                                         |
| `1`       | parede                                       |
| `N/S/E/W` | posição inicial e direção do jogador         |
| espaço    | exterior do mapa (não pode tocar no chão)    |

O mapa tem de ser fechado por paredes, ter pelo menos `3x3` células e conter
exatamente um `N`, `S`, `E` ou `W`.

## Mapas incluídos

Mapas válidos:

- `maps/valid/minimal.cub` — mapa mínimo;
- `maps/valid/simple.cub` — mapa básico;
- `maps/valid/complex_shape.cub` — paredes com forma irregular;
- `maps/valid/arena.cub` — mapa maior com pilares, útil para testar movimento.

Mapas inválidos em `maps/invalid/`:

- `bad_map_chars.cub` — caractere inválido;
- `empty_line_in_map.cub` — linha vazia dentro do mapa;
- `invalid_color.cub` — canal RGB fora do intervalo;
- `missing_texture.cub` — textura obrigatória em falta;
- `no_player.cub` — mapa sem jogador;
- `no_walls.cub` — mapa aberto;
- `two_players.cub` — dois pontos de spawn.

## Estrutura

```text
include/              cabeçalhos e estruturas do jogo
src/parsing/          leitura e validação do ficheiro .cub
src/raycasting/       direção dos raios, DDA e projeção das paredes
src/render/           framebuffer, chão/teto e texturas
src/player/           movimento, rotação e colisão
src/events/           teclado
src/init/             inicialização do jogo, janela e texturas
src/exit/             erros e libertação de memória
libft/                funções utilitárias, get_next_line e ft_printf
textures/             texturas XPM das quatro paredes
maps/                 mapas válidos e inválidos
```

## Qualidade e testes

- `norminette src include libft/*.c libft/*.h` sem erros;
- compilação com `make re` sem erros nem warnings no código do projeto;
- testes de todos os mapas inválidos, confirmando mensagem de erro e saída
  com código diferente de zero;
- testes de execução de todos os mapas válidos, incluindo fecho da janela;
- Valgrind sem fugas de memória:

```sh
valgrind --leak-check=full --show-leak-kinds=all \
    ./cub3d maps/valid/simple.cub
```

O resultado esperado é `All heap blocks were freed -- no leaks are possible`,
sem blocos *still reachable* no código do projeto.

## Funções externas

O código do projeto usa apenas as funções permitidas pela parte obrigatória do
subject: `open`, `close`, `read`, `write`, `malloc`, `free`, `exit`, funções de
`<math.h>` e funções da MiniLibX. A Libft é usada para operações de memória,
strings, escrita em descritores, leitura de linhas com `get_next_line` e
formatação da saída com `ft_printf`.

## Créditos

Projeto desenvolvido para o currículo 42 por **hcosta** e **hcuessec**.
MiniLibX e Libft são bibliotecas fornecidas pelo campus 42.
