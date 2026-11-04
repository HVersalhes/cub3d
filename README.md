*This project has been created as part of the 42 curriculum by hcosta, hcuessec.*

# cub3D

## Description

**cub3D** is a first-person 3D maze renderer written in **C** with the **MiniLibX** library, inspired by *Wolfenstein 3D*. The goal is to build a real-time view of a maze from a 2D `.cub` map using **raycasting**, without any 3D API such as OpenGL.

Overview:
- A `.cub` file defines four wall textures (N/S/E/W), floor and ceiling colors, and the map grid.
- For each screen column (1200 columns, 1200x800 window) a ray is cast from the player. The **DDA** algorithm finds the first wall hit and its perpendicular distance (no fisheye effect).
- The wall slice is drawn with the matching directional XPM texture, and the frame is composed in an off-screen image before being displayed.
- The player moves with collision detection and wall sliding.

## Instructions

**Requirements** (Linux/X11): `cc`, `make`, `libx11-dev`, `libxext-dev`.

```sh
sudo apt-get install -y build-essential libx11-dev libxext-dev
```

**Compilation**

```sh
make        # builds libft, minilibx and ./cub3D
make clean  # removes object files
make fclean # removes objects and binary
make re     # full rebuild
```

**Execution**

```sh
./cub3D maps/valid/simple.cub
```

Other maps: `maps/valid/{minimal,complex_shape,arena}.cub`. Invalid maps for error testing are in `maps/invalid/`. On any error the program prints `Error` followed by a message and exits.

**Controls**

| Key | Action |
|:---:|:---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera |
| `ESC` or window `[X]` | Quit (frees all resources) |

**Map format**

```text
NO textures/wall_north.xpm
SO textures/wall_south.xpm
WE textures/wall_west.xpm
EA textures/wall_east.xpm

F 220,100,0
C 25,30,65

11111111
10000001
100N0001
11111111
```

- `NO/SO/WE/EA`: texture paths; `F/C`: floor/ceiling color as `R,G,B` (0–255).
- Map characters: `1` wall, `0` floor, `N/S/E/W` player start and direction, space = void.
- The map must have exactly one player and be fully enclosed by walls.

**Project structure**

```text
include/   cub3d.h, cub3d_structs.h
libft/     custom C library (incl. get_next_line, ft_printf)
minilibx/  MiniLibX for X11
maps/      valid/ and invalid/ test maps
textures/  wall XPM textures
src/
├── main.c
├── init/        data, MLX window, player, textures
├── parsing/     .cub parsing and map validation
├── raycasting/  ray direction, DDA, column loop
├── render/      floor/ceiling, texture mapping, frame
├── player/      movement, rotation, collision
├── events/      keyboard handling
└── exit/        error handling and cleanup
```

## Resources

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [F. Permadi's Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [42 Docs — MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
- Amanatides & Woo, *A Fast Voxel Traversal Algorithm for Ray Tracing* (Eurographics '87)
- Fabien Sanglard, *Game Engine Black Book: Wolfenstein 3D*

**Use of AI**

AI (an LLM assistant) was used as a support tool for:
- Checking the rotation and perpendicular-distance math (`src/player/rotation.c`, `src/raycasting/dda_algorithm.c`).
- Reviewing cleanup paths in `src/exit/free.c` for memory leaks.
- Helping write and structure this README.md
