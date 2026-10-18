# 🌀 Maze Runner — Cub3D (42 Common Core)

*Plano de projeto completo — conceito, estrutura, cronograma (280h), divisão de tarefas entre 2 pessoas e bónus*

---

## 1. Conceito do Jogo

**Nome:** Maze Runner
**Género:** Raycasting FPS-exploration (estilo Wolfenstein 3D)
**Engine:** miniLibX
**Linguagem:** C (Norma 42)

### 1.1 Pitch
Um labirinto antigo, gerado a partir de mapas `.cub`, onde o jogador vê o mundo em primeira pessoa através de um motor de raycasting construído do zero. O objetivo é puramente de **navegação e exploração**: encontrar o caminho, sentir a profundidade do espaço através de texturas direcionais (N/S/E/W), luz e sombra, e (na parte bónus) interagir com portas, sprites animados e um HUD.

### 1.2 Direção de arte (para o trabalho em Aseprite)
Definir uma **paleta e tema coerente** antes de começar a pintar tiles evita retrabalho:

- **Tema sugerido:** ruínas subterrâneas / masmorra de pedra com toques de ferrugem e musgo.
- **Resolução de textura recomendada:** 64x64 px por parede (potência de 2, facilita mapeamento de textura no raycasting). 32x32 se quiserem otimizar tempo.
- **Paleta:** limitada (8–16 cores) para manter consistência e acelerar produção.
- **Assets a produzir:**
  - 4 texturas de parede (N, S, E, W)
  - Chão e teto (cor sólida obrigatório; textura se fizerem sky texture no bónus)
  - Textura de porta fechada / porta aberta (bónus)
  - Sprite animado (bónus) — ex: tocha a tremeluzir, item colecionável
  - Ícone do jogador para o minimapa (bónus)

---

## 2. Estrutura do Repositório

```
maze-runner/
├── Makefile
├── README.md
├── libft/                     # cópia da libft + Makefile próprio
├── minilibx/                  # fontes da miniLibX (se não usarem a do SO)
├── maps/
│   ├── valid/
│   │   ├── simple.cub
│   │   ├── complex_shape.cub
│   │   └── minimal.cub
│   └── invalid/
│       ├── no_walls.cub
│       ├── missing_texture.cub
│       ├── bad_map_chars.cub
│       └── two_players.cub
├── textures/
│   ├── wall_north.png
│   ├── wall_south.png
│   ├── wall_east.png
│   ├── wall_west.png
│   ├── door_closed.png        # bónus
│   ├── door_open.png          # bónus
│   └── sprites/               # bónus
│       ├── torch_01.png ... torch_04.png
├── include/
│   ├── cub3d.h
│   ├── cub3d_structs.h
│   └── cub3d_bonus.h
├── src/
│   ├── main.c
│   ├── parsing/                # PESSOA A
│   │   ├── parse_file.c
│   │   ├── parse_textures.c
│   │   ├── parse_colors.c
│   │   ├── parse_map.c
│   │   └── validate_map.c
│   ├── init/                   # PESSOA A
│   │   ├── init_mlx.c
│   │   ├── init_player.c
│   │   └── init_data.c
│   ├── raycasting/              # PESSOA B
│   │   ├── dda_algorithm.c
│   │   ├── ray_direction.c
│   │   ├── wall_distance.c
│   │   └── draw_wall_slice.c
│   ├── render/                  # PESSOA B
│   │   ├── render_frame.c
│   │   ├── render_floor_ceiling.c
│   │   ├── texture_mapping.c
│   │   └── minimap.c            # bónus — PESSOA A
│   ├── player/                  # PESSOA B
│   │   ├── movement.c
│   │   ├── rotation.c
│   │   └── collision.c          # bónus — PESSOA B
│   ├── events/                  # PESSOA A
│   │   ├── keyboard.c
│   │   ├── mouse.c              # bónus — PESSOA B
│   │   └── close_window.c
│   ├── bonus/
│   │   ├── doors_bonus.c        # PESSOA A
│   │   ├── sprites_bonus.c      # PESSOA B
│   │   └── minimap_bonus.c      # PESSOA A
│   ├── utils/                   # PARTILHADO
│   │   ├── error_handling.c
│   │   ├── free_utils.c
│   │   └── string_utils.c
│   └── main_bonus.c
└── test/
    ├── leak_test.sh
    └── norm_check.sh
```

**Regra Norma importante:** os ficheiros de bónus (`_bonus.c/h`) contam na verificação da Norma — mantenham a mesma disciplina de nomenclatura e limites de linhas/funções desde o dia 1.

---

## 3. Divisão de Tarefas entre 2 Pessoas

A divisão segue a lógica natural do Cub3D: **um lado "input/dados" (parsing, estruturas, eventos, portas, minimapa)** e **um lado "motor/output" (raycasting, renderização, movimento, sprites)**. Isto minimiza dependências bloqueantes — cada pessoa consegue trabalhar isoladamente na maior parte do tempo, cruzando-se principalmente nas structs partilhadas (definidas em conjunto na Semana 1).

| | **hcosta** — Dados & Interação | **hcuessec** — Motor & Render |
|---|---|---|
| **Foco** | Parsing do `.cub`, validação, estruturas de erro, gestão de janela/eventos, portas, minimapa | Algoritmo de raycasting (DDA), mapeamento de texturas, chão/teto, movimento, colisões, sprites |
| **Ficheiros** | `parsing/`, `init/`, `events/`, `bonus/doors_bonus.c`, `bonus/minimap_bonus.c` | `raycasting/`, `render/`, `player/`, `bonus/sprites_bonus.c`, `events/mouse.c` |
| **Horas estimadas** | ~135h | ~135h |
| **Partilhado** | `utils/`, `include/cub3d_structs.h` (definido em conjunto na Semana 1), Makefile, README, testes finais | idem |

> A definição das **structs partilhadas** (`t_game`, `t_map`, `t_player`, `t_texture`) deve ser feita **em conjunto** logo na Semana 1, porque é a interface entre os dois lados do projeto. Depois disso, cada pessoa trabalha com autonomia sobre a sua parte, respeitando essa interface.

### 3.1 Cronograma Semanal com Responsáveis — 280h Total (140h/pessoa)

| Semana | Foco Geral | hcosta | hcuessec | Entrega verificável |
|---|---|---|---|---|
| 1 | Setup + structs partilhadas + Parsing base | Parsing `.cub` (texturas, cores) — 15h | Setup miniLibX + esqueleto de janela — 15h | Structs definidas em conjunto; ficheiro `.cub` é lido; janela abre |
| 2 | Parsing do mapa + validação | Parsing do mapa, validação geométrica (fechado/aberto), extração de spawn — 14h | Estrutura de dados do mapa em grid, testes de carregamento — 14h | Mapas válidos/inválidos corretamente aceites/rejeitados com `Error\n` |
| 3 | Fundação do motor | Gestão de eventos (ESC, X vermelho), tratamento de erros global — 12.5h | Início do algoritmo DDA (raycasting base) — 12.5h | Janela fecha de forma limpa; primeiro raio calculado corretamente |
| 4 | Raycasting completo | Testes de robustez do parsing (mapas irregulares, edge cases) — 17.5h | DDA completo + correção de fisheye + cor sólida por direção — 17.5h | Paredes desenhadas em cor sólida sem distorção |
| 5 | Texturização | Carregamento de imagens de textura (mlx_xpm/png), gestão de memória — 15h | Mapeamento de textura na parede (coordenada X/Y) — 15h | 4 texturas aplicadas corretamente por direção |
| 6 | Movimento e input | Keyboard hooks (WASD, setas) — 12.5h | Lógica de movimento/rotação do jogador (vetores, ângulo) — 12.5h | Jogador anda e roda suavemente |
| 7 | Chão/teto + polimento obrigatório | Validação final de cores F/C, revisão de todos os erros — 10h | Render de chão/teto colorido, otimização do render loop — 10h | **Projeto 100% obrigatório, sem crashes nem leaks** |
| 8 | Bónus (parte 1) | Sistema de minimapa (`minimap_bonus.c`) — 12.5h | Colisões robustas (bounding box) — 12.5h | Minimapa funcional; jogador não atravessa paredes |
| 9 | Bónus (parte 2) | Portas que abrem/fecham (`doors_bonus.c`) — 15h | Sprites animadas + rotação com o rato — 15h | Portas interativas; sprite animado renderizado com depth-buffer |
| 10 | Testes, Norma, README, defesa | Revisão de Norma no seu código, testes com mapas extremos — 16h | Valgrind/leak check no motor de render, otimizações finais — 16h | Zero leaks, zero erros de Norma, README completo, testado por pares |

**Total: 280h (140h por pessoa)**

> ⚠️ Lembrete crítico do subject: **os bónus só são avaliados se a parte obrigatória estiver 100% perfeita.** Não avancem para a Semana 8 sem confirmar, os dois, que a Semana 7 está impecável (zero crash, zero leak, todos os pontos obrigatórios). Se houver atraso, cortem tempo do bónus, nunca da robustez obrigatória.

---

## 4. Breakdown Detalhado por Tarefa (com responsável)

### 4.1 Parte Obrigatória

**A. Parsing — 👤 hcosta** (`src/parsing/`)
- [ ] Ler o `.cub` passado como `argv[1]`, validar extensão
- [ ] Extrair identificadores `NO`, `SO`, `WE`, `EA` (caminhos de textura) — ordem livre, pode ter espaços múltiplos
- [ ] Extrair `F` e `C` (cores chão/teto) em RGB `[0,255]`
- [ ] Detetar o mapa (sempre o último bloco), preservar espaços internos como válidos
- [ ] Validar que o mapa contém apenas `0 1 N S E W espaço`
- [ ] Validar que existe **exatamente um** spawn de jogador
- [ ] Validar que o mapa está **fechado/cercado de paredes** (flood-fill ou verificação de bordas)
- [ ] Em qualquer erro: imprimir `Error\n` + mensagem explícita, `exit` limpo, sem leaks

**B. Estruturas de dados — 👥 hcosta + hcuessec em conjunto** (`include/cub3d_structs.h`)
- [ ] `t_map` (grid, largura, altura)
- [ ] `t_player` (posição x/y, ângulo, direção, plano de câmara)
- [ ] `t_texture` (4 texturas de parede + dados de imagem mlx)
- [ ] `t_game` (struct "mãe" — mlx_ptr, win_ptr, map, player, texturas, cores)

**C. Motor de Raycasting — 👤 hcuessec** (`src/raycasting/`)
- [ ] Algoritmo DDA (Digital Differential Analysis) para cada coluna de ecrã
- [ ] Correção do efeito **fisheye** (distância perpendicular, não euclidiana)
- [ ] Determinar face da parede atingida (N/S/E/W) para escolher textura certa
- [ ] Calcular altura da linha da parede em função da distância

**D. Renderização — 👤 hcuessec** (`src/render/`)
- [ ] Mapeamento de textura (coordenada X da textura em função do ponto de impacto)
- [ ] Preencher chão e teto com as cores configuradas
- [ ] Usar `mlx_put_image_to_window` com buffer de imagem (muito mais rápido que pixel a pixel direto)

**E. Input e Janela — 👤 hcosta** (`src/events/`)
- [ ] W/A/S/D para mover (com deteção de colisão simples: não atravessar `1`)
- [ ] Setas esquerda/direita para rodar a câmara
- [ ] ESC fecha a janela de forma limpa (`mlx_destroy_window`, free tudo)
- [ ] Clique no X vermelho fecha de forma limpa (hook `mlx_hook` no evento de destroy)
- [ ] Gerenciamento de janela suave (minimizar/mudar de janela sem crash)

**F. Movimento — 👤 hcuessec** (`src/player/`)
- [ ] Cálculo vetorial de deslocamento em função do ângulo do jogador
- [ ] Rotação suave da câmara

**G. Makefile — 👥 Partilhado**
- [ ] Regras: `$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`
- [ ] Flags `-Wall -Wextra -Werror`, compilador `cc`
- [ ] Sem re-links desnecessários
- [ ] Compila `libft` via o Makefile dela própria, depois o projeto

---

### 4.2 Parte Bónus (só depois da obrigatória estar 100%)

| Bónus | Responsável | Ficheiros | Complexidade | Notas técnicas |
|---|---|---|---|---|
| Colisões nas paredes | 👤 hcuessec | `player/collision.c` | Baixa-Média | Bounding box pequena à volta do jogador, evita atravessar paredes em diagonal |
| Minimapa | 👤 hcosta | `render/minimap.c` | Média | Desenhar num canto da janela; atualizar por frame; cores sólidas simples |
| Portas que abrem/fecham | 👤 hcosta | `bonus/doors_bonus.c` | Média-Alta | Novo caractere no mapa (ex: `D`), estado (aberta/fechada), interação por tecla |
| Sprites animadas | 👤 hcuessec | `bonus/sprites_bonus.c` | Alta | Projeção 2D de objeto num mundo 3D (transformação por matriz inversa câmara), depth-buffer |
| Rotação com o rato | 👤 hcuessec | `events/mouse.c` | Média | `mlx_mouse_hook`, capturar o rato dentro da janela |

> Nota do subject: são livres de adicionar novos caracteres ao mapa ou alterar o formato do ficheiro `.cub` para os bónus, desde que justifiquem na defesa.

---

## 5. Checklist Final Antes da Entrega

- [ ] `norminette` limpo em **todos** os ficheiros, incluindo `_bonus` (ambos revisam o código um do outro)
- [ ] Zero leaks confirmados com `valgrind --leak-check=full` em todos os fluxos (incluindo caminhos de erro)
- [ ] Zero crashes: testar mapas malformados, ficheiros inexistentes, argv errado, mapas gigantes, mapas com formas irregulares
- [ ] `Makefile` sem re-link desnecessário (correr `make` duas vezes seguidas → segunda vez não recompila nada)
- [ ] `README.md` com:
  - Primeira linha em itálico: *Este projeto foi criado como parte do currículo da 42 por hcosta, hcuessec*
  - Secção **Descrição**
  - Secção **Instruções** (compilar/executar)
  - Secção **Recursos** (referências + como usaram IA, para quê e em que partes — obrigatório declarar)
- [ ] Testado por pelo menos um colega antes da avaliação oficial
- [ ] Ambos conseguem explicar **qualquer parte** do código (não só a sua) — a avaliação pode perguntar a qualquer um sobre qualquer secção
- [ ] Repositório Git contém tudo (nada de dependências externas não versionadas)

---

## 6. Recursos Técnicos Recomendados (para a secção "Recursos" do README)

- Documentação oficial da miniLibX (man pages do campus / fontes do projeto)
- Lodev's Raycasting Tutorial — referência clássica para o algoritmo DDA e correção de fisheye
- Documentação `-lm` (`man 3 math`) para funções trigonométricas usadas na direção dos raios
- Artigos sobre "sprite casting" para o bónus de sprites animadas

---

