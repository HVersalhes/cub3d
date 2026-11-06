*This project has been created as part of the 42 curriculum by hcosta and hcuessec.*

# cub3D

A fast, lightweight first-person 3D raycasting game engine written in **C** using the **MiniLibX** graphic library. Inspired by the legendary 1992 game *Wolfenstein 3D*, cub3D renders a real-time, textured 3D maze from a 2D map definition without using any 3D graphic libraries (such as OpenGL, DirectX, or Vulkan).

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [System Architecture](#system-architecture)
3. [How Raycasting Works](#how-raycasting-works)
   - [2D Map to 3D Projection](#2d-map-to-3d-projection)
   - [Camera Model and Ray Direction](#camera-model-and-ray-direction)
   - [DDA Grid Traversal](#dda-grid-traversal)
   - [Fisheye Correction and Perpendicular Distance](#fisheye-correction-and-perpendicular-distance)
   - [Texture Mapping and Directional Shading](#texture-mapping-and-directional-shading)
   - [Collision Detection and Wall Sliding](#collision-detection-and-wall-sliding)
   - [Off-Screen Framebuffer (Double Buffering)](#off-screen-framebuffer-double-buffering)
   - [Smooth Keyboard Input](#smooth-keyboard-input)
4. [Map Specifications and Validation](#map-specifications-and-validation)
5. [Controls](#controls)
6. [Compilation and Execution](#compilation-and-execution)
7. [Memory Management and Safety](#memory-management-and-safety)
8. [Resources and References](#resources-and-references)
9. [Use of AI Disclosure](#use-of-ai-disclosure)

---

## Project Overview

cub3D brings classic pseudo-3D graphics to life through pure software rendering:

```text
       2D TOP-DOWN MAP                       3D FIRST-PERSON VIEW
+---------------------------+       +------------------------------------+
| 1   1   1   1   1   1   1 |       |          CEILING (Sky)             |
| 1   0   0   0   0   0   1 |       |   +----------------------------+   |
| 1   0   .---.       0   1 |       |   | \                        / |   |
| 1   0  / ray \      1   1 |       |   |  |======================|  |   |
| 1   0 /   P   \     0   1 |  ==>  |   |  |      WALL SLICE      |  |   |
| 1   1   1   1   1   1   1 |       |   |  |       (TEXTURE)      |  |   |
+---------------------------+       |   | /                        \ |   |
                                    |   +----------------------------+   |
                                    |           FLOOR                |
                                    +------------------------------------+
```

* **Raycasting Engine**: Casts one ray per horizontal screen column (1200 rays per frame at `1200x800` resolution) to detect wall intersections on a 2D grid.
* **Directional Textures**: Samples North, South, East, and West XPM textures based on the wall face struck by the ray.
* **Software Framebuffer**: Draws pixels directly to an off-screen byte buffer in memory, pushing the entire completed image to the display once per frame for flicker-free 60 FPS gameplay.
* **Responsive Physics**: Continuous movement with 4-corner bounding box collision checks and independent X/Y axis wall sliding.

---

## System Architecture

The codebase is organized into modular directories:

```text
cub3d/
├── include/
│   ├── cub3d.h           # Prototypes, window dimensions, keys, and constants
│   └── cub3d_structs.h   # Data structures (t_img, t_player, t_map, t_ray, t_game)
├── libft/                # Custom library (string utilities, get_next_line, ft_printf)
├── minilibx/             # 42 MiniLibX graphic library for X11 window and display
├── maps/
│   ├── valid/            # Conforming .cub maps for testing
│   └── invalid/          # Edge-case maps verifying parser rejection
├── textures/             # North, South, East, and West wall textures (.xpm)
└── src/
    ├── main.c            # Program entry point and main game loop initialization
    ├── init/
    │   ├── init_data.c       # Zeroes structs and sets default game values
    │   ├── init_mlx.c        # Initializes MiniLibX context, window, and image buffer
    │   ├── init_player.c     # Positions player and sets direction/plane vectors
    │   └── init_textures.c   # Loads the 4 XPM textures into memory buffers
    ├── parsing/
    │   ├── parse_file.c      # Validates .cub extension and coordinates parsing
    │   ├── parse_textures.c  # Extracts and validates NO, SO, WE, EA texture paths
    │   ├── parse_colors.c    # Validates RGB channels (0-255) for Floor and Ceiling
    │   ├── parse_map.c       # Reads map lines, builds linked list, creates 2D grid
    │   └── validate_map.c    # 8-neighbor enclosure check, valid tiles, single player
    ├── raycasting/
    │   ├── raycasting.c      # Iterates over all 1200 horizontal screen columns
    │   ├── ray_direction.c   # Computes ray direction vector from camera plane
    │   └── dda_algorithm.c   # DDA grid stepping and perpendicular distance projection
    ├── render/
    │   ├── render_frame.c    # Frame loop (clears buffer -> renders walls -> blits)
    │   ├── render_floor_ceiling.c # Scanline fill for floor and ceiling colors
    │   └── texture_mapping.c # Wall texture sampling, UV scaling, directional shade
    ├── player/
    │   ├── movement.c        # Forward, backward, and strafe position updates
    │   ├── collision.c       # 4-corner hitbox verification against solid tiles
    │   └── rotation.c        # 2D Euclidean rotation of direction and camera plane
    ├── events/
    │   └── keyboard.c        # KeyPress and KeyRelease event handlers
    └── exit/
        ├── error.c           # Formatted error exit (Error\n<message>)
        └── free.c            # Memory deallocation and resource cleanup
```

---

## How Raycasting Works

### 2D Map to 3D Projection

Raycasting simulates a 3D world from a 2D tile grid. The player moves through the 2D map, and for each column of the screen, a ray is projected forward. When the ray strikes a wall, its distance determines how tall to draw that vertical slice of wall on screen:
- **Closer walls** $\rightarrow$ Ray travels a short distance $\rightarrow$ Wall slice is drawn **tall**.
- **Farther walls** $\rightarrow$ Ray travels a long distance $\rightarrow$ Wall slice is drawn **short**.

---

### Camera Model and Ray Direction

The player's viewpoint is defined by two vectors:
1. **Direction Vector (`dir`)**: The line of sight pointing directly ahead.
2. **Camera Plane Vector (`plane`)**: Perpendicular to `dir`, representing the camera's field of view (FOV $\approx 66^\circ$).

```text
                       Camera Plane (plane_x, plane_y)
             -1.0 (Left)             0.0              +1.0 (Right)
               +----------------------|--------------------+
                \                     |                   /
                 \                    |                  /
                  \                   | dir vector      /
             ray   \                  |                /   ray
           (col 0)  \                 v               /  (col 1199)
                     \                *              /
                      \               |             /
                       \              |            /
                        \             |           /
                         \            |          /
                          \           |         /
                           \          |        /
                            `-----> P <-------'
                                 Player
```

For each horizontal screen pixel column $x \in [0, 1199]$:
1. Normalize screen column coordinate to camera space between $-1$ and $+1$:
   ```c
   camera_x = 2 * x / (double)WIN_WIDTH - 1;
   ```
2. Combine direction and camera plane to find the ray's trajectory:
   ```c
   ray_dir_x = player->dir_x + player->plane_x * camera_x;
   ray_dir_y = player->dir_y + player->plane_y * camera_x;
   ```

---

### DDA Grid Traversal

Instead of inching forward in small fixed steps (which is slow and can skip through thin corners), the engine uses **DDA (Digital Differential Analysis)**. DDA jumps directly from one grid line to the next:

```text
    (map_x, map_y)
       +--------+--------+--------+--------+--------+
       |        |        |        |  WALL  |  WALL  |
       |        |        |        |   1    |   1    |
       +--------+--------+--------+---*----+--------+
       |        |        |        |  /|hit!|        |
       |        |        |   step 2 / |    |        |
       +--------+--------+--------*---+----+--------+
       |        |   step 1       /|   |    |        |
       |        |        |     *  |   |    |        |
       +--------+--------+----/---+---+----+--------+
       |        |  Player    /    |   |    |        |
       |        |    P      /     |   |    |        |
       |        |          v      |   |    |        |
       +--------+--------+--------+---+----+--------+
                  side_dist_x / side_dist_y
```

1. **Step Increments**: Compute `delta_dist_x = |1 / ray_dir_x|` and `delta_dist_y = |1 / ray_dir_y|`. This is the distance the ray travels to cross one full grid tile along each axis.
2. **Initial Distance (`side_dist`)**: The distance from the player's continuous position to the very first grid line.
3. **Step Loop**: At each step, advance along whichever axis has the smaller `side_dist`:
   - If `side_dist_x < side_dist_y`: jump to the next X boundary (`map_x += step_x`), update `side_dist_x += delta_dist_x`, and mark `side = 0` (vertical wall: East/West).
   - If `side_dist_y <= side_dist_x`: jump to the next Y boundary (`map_y += step_y`), update `side_dist_y += delta_dist_y`, and mark `side = 1` (horizontal wall: North/South).
4. **Hit Detection**: Stop immediately when `grid[map_y][map_x] == '1'`.

---

### Fisheye Correction and Perpendicular Distance

If we used direct Euclidean distance (measuring straight from player to wall), diagonal rays at the edges of the screen would have a longer distance than straight rays in the center. This causes flat walls to curve outward like a bowl (the "fisheye" effect).

```text
           WALL
=============================
  ^          ^          ^
   \         |         /
    \        |        /
     \       | d_perp/
  d_eucl      |      /  d_eucl
       \     |     /
        \    |    /
   - - - + - | - + - - -  Camera Plane
          \  |  /
           \ | /
             P (Player)

  WITHOUT CORRECTION (Euclidean):           WITH PERPENDICULAR DISTANCE:
  Rays at edges travel farther (d_eucl),    Distance projected onto camera plane
  making flat walls curve like a bowl.      (d_perp), keeping flat walls straight!

          (Curved / Fisheye)                         (Correct / Flat)
       +-----------------------+                 +-----------------------+
       |       /=======\       |                 |     =============     |
       |      /         \      |                 |     |           |     |
       |     |   WALL    |     |                 |     |   WALL    |     |
       |      \         /      |                 |     |           |     |
       |       \=======/       |                 |     =============     |
       +-----------------------+                 +-----------------------+
```

To eliminate distortion, the distance is projected orthogonally onto the camera plane:
- Vertical wall (`side == 0`):
  ```c
  perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
  ```
- Horizontal wall (`side == 1`):
  ```c
  perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
  ```

Wall slice height on screen is inversely proportional to this perpendicular distance:
```c
line_height = (int)(WIN_HEIGHT / perp_wall_dist);
```
Top (`draw_start`) and bottom (`draw_end`) bounds are centered vertically in the window.

---

### Texture Mapping and Directional Shading

Once a wall is struck, the engine maps the corresponding texture column onto that vertical slice of screen:

```text
      RAY HIT ON WALL                        XPM TEXTURE (64x64)
+-------------------------+             +-----------------------+
|                         |             |  |                    |
|                         |             |  |                    |
|             * hit point |             |  |                    |
|             |           |   =====>    |  | tex_y              |
|             | wall_x    |             |  v                    |
|  [0.0] <----+----> [1.0]|             |  *                    |
|       one map cell      |             |  |                    |
+-------------------------+             +--|--------------------+
                                           |--> tex_x (column)

                    SCREEN COLUMN (x)
             +------------------------------+
             |                              |
             |       +--------------+ draw_start
             |       |  * pixel     |
             |       |  | (sampled  |
             |       |  v  tex_y)   |
             |       |              |
             |       +--------------+ draw_end
             |                              |
             +------------------------------+
```

1. **Orientation**:
   - Vertical hit (`side == 0`): `ray_dir_x > 0` selects **East**; otherwise **West**.
   - Horizontal hit (`side == 1`): `ray_dir_y > 0` selects **South**; otherwise **North**.
2. **Horizontal Coordinate (`tex_x`)**:
   Calculate exact hit location `wall_x` inside the tile (a value between 0.0 and 1.0), and scale it to texture width:
   ```c
   tex_x = (int)(wall_x * (double)tex->width);
   ```
   If facing opposite to the wall's orientation, `tex_x` is mirrored (`tex->width - tex_x - 1`).
3. **Vertical Coordinate (`tex_y`)**:
   For each screen pixel from `draw_start` to `draw_end`, step through the texture height:
   ```c
   step = 1.0 * tex->height / line_height;
   tex_y = (int)tex_pos & (tex->height - 1);
   ```
4. **Depth Shading**:
   North/South walls (`side == 1`) are darkened by 25% to produce natural contrast and corner shading.

---

### Collision Detection and Wall Sliding

Player movement uses continuous floating-point coordinates. To prevent clipping through walls or corners:

```text
                (x - r, y - r)         (x + r, y - r)
                         [+]-------------+
                          |              |
                          |      P       |  r = COLLISION_RADIUS (0.20)
                          |   (pos_x,    |
                          |    pos_y)    |
                          |              |
                          +-------------+
                (x - r, y + r)         (x + r, y + r)
```

* **4-Corner Bounding Box**: Rather than treating the player as a zero-width point, `is_valid_walk_position` checks 4 corner points around the player offset by a radius (`0.20`). If any point falls into a wall (`'1'`) or void space (`' '`), the position is rejected.

* **Wall Sliding**:
  Movement along the X and Y axes is calculated and applied independently:
  ```c
  if (is_valid_walk_position(game, new_x, player.pos_y))
      player.pos_x = new_x;
  if (is_valid_walk_position(game, player.pos_x, new_y))
      player.pos_y = new_y;
  ```

```text
                   WALL (Solid '1')
    ===============================================
                       ^
                       | (Y movement blocked)
                       X
                      /
    Movement vector  /
    (e.g., W + D)   /
                   /   ---> Player slides smoothly
                  P         along X axis!
```

If you walk diagonally into a wall, the blocked axis stops while the free axis continues, allowing the player to slide smoothly along walls.

---

### Off-Screen Framebuffer (Double Buffering)

Drawing directly to the screen pixel-by-pixel with `mlx_pixel_put()` generates thousands of slow network calls to the X11 server, causing noticeable flicker and low frame rates.

cub3D renders everything into memory first:

```text
  1. WRITE PIXELS TO RAM (Fast)              2. SINGLE BLIT TO SCREEN
  +------------------------------------+     mlx_put_image_to_window()
  | Framebuffer (Byte Array in Memory) | ------------------------>  [ WINDOW ]
  |   - Ceiling colors filled          |                            Smooth 60 FPS
  |   - Wall texture columns rendered  |                            Zero flicker!
  |   - Floor colors filled            |
  +------------------------------------+
```

1. Allocate an off-screen image buffer with `mlx_new_image(mlx, 1200, 800)`.
2. Retrieve its memory pointer via `mlx_get_data_addr`.
3. Write pixels directly with fast pointer offsets:
   ```c
   pixel_offset = y * line_len + x * (bpp / 8);
   ```
4. Render ceiling, textured walls, and floor in memory, then push the finished frame to the display in a single call to `mlx_put_image_to_window()`.

---

### Smooth Keyboard Input

Default operating system key events produce repeat delays (a pause after the initial press). cub3D implements continuous input state tracking:
- `KeyPress` sets the key's boolean state to `true`.
- `KeyRelease` sets the state back to `false`.
- The engine checks these boolean flags on every frame update, ensuring instant responsiveness and simultaneous actions (such as walking forward while strafing and rotating).

---

## Map Specifications and Validation

### File Structure (`.cub`)

A `.cub` configuration file consists of 6 metadata identifiers followed by the maze layout:

```text
NO textures/wall_north.xpm
SO textures/wall_south.xpm
WE textures/wall_west.xpm
EA textures/wall_east.xpm

F 220,100,0
C 25,30,65

111111111111
100000000001
1000000N0001
111111111111
```

* **Textures**: 4 identifiers (`NO`, `SO`, `WE`, `EA`) pointing to valid, readable `.xpm` files.
* **Colors**: Floor (`F`) and Ceiling (`C`) specified as `R,G,B` integers in the range `[0, 255]`.
* **Map Characters**:
  - `1`: Wall
  - `0`: Walkable floor
  - `N`, `S`, `E`, `W`: Player spawn location and initial orientation
  - `' '` (space): Void area outside the maze

### 8-Neighbor Validation Check

Every walkable tile (`0`, `N`, `S`, `E`, `W`) must be completely sealed from outside space:

```text
        SEALED MAP (VALID)                     LEAKY MAP (INVALID)
    +-----------------------+              +-----------------------+
    | 1   1   1   1   1   1 |              | 1   1   1   1   1   1 |
    | 1   0   0   0   0   1 |              | 1   0   0   0   0   1 |
    | 1   0   P   0   0   1 |              | 1   0   P   0   0     | <--- OPEN HOLE!
    | 1   0   0   0   0   1 |              | 1   0   0   0   0   1 |      (Player could
    | 1   1   1   1   1   1 |              | 1   1   1   1   1   1 |       escape)
    +-----------------------+              +-----------------------+

       Every walkable tile '0' / player must be surrounded by 8 non-space tiles:
                            [N-W]   [ N ]   [N-E]
                            [ W ]   [ 0 ]   [ E ]
                            [S-W]   [ S ]   [S-E]
```

The parser guarantees:
1. File extension ends with `.cub`.
2. All 6 headers exist before map layout; duplicates are rejected.
3. Exactly one player spawn (`N`, `S`, `E`, or `W`).
4. Map is enclosed: no walkable cell touches empty space or map borders.
5. No empty lines inside the map layout.
6. Rows are padded with spaces to create a consistent rectangular matrix.

---

## Controls

| Key | Action | Behavior |
|:---:|:---|:---|
| `W` | Move Forward | Moves forward along direction vector |
| `S` | Move Backward | Moves backward opposite to direction vector |
| `A` | Strafe Left | Moves left along camera plane |
| `D` | Strafe Right | Moves right along camera plane |
| `←` | Rotate Left | Rotates camera counter-clockwise |
| `→` | Rotate Right | Rotates camera clockwise |
| `ESC` | Exit Game | Frees all resources and exits cleanly |
| `[X]` | Close Window | Standard window close button hooked to exit handler |

---

## Compilation and Execution

### Requirements (Linux / X11)

Requires standard C development tools and X11 development headers:

```sh
sudo apt-get update
sudo apt-get install -y build-essential libx11-dev libxext-dev
```

### Build Commands

```sh
make        # Compiles libft, minilibx, and builds ./cub3D
make clean  # Deletes intermediate object files (.o)
make fclean # Deletes object files, libraries, and the ./cub3D binary
make re     # Clean rebuild from scratch
```

### Running the Game

```sh
./cub3D maps/valid/simple.cub
```

Available valid maps for testing:
* `maps/valid/simple.cub`: Classic rectangular maze
* `maps/valid/minimal.cub`: Small $3 \times 3$ walkable room
* `maps/valid/arena.cub`: Large open hall with interior pillars
* `maps/valid/complex_shape.cub`: Irregular room layout with corridors

On any configuration or parsing error, the engine prints `Error` followed by an explicit message to `stderr` and exits cleanly.

---

## Memory Management and Safety

The project conforms strictly to 42 School guidelines regarding memory management:
* **Centralized Teardown**: `src/exit/free.c` releases all 4 loaded textures, the off-screen image buffer, the window pointer, the display connection, and 2D map allocations.
* **Error Handling**: On invalid map or scene definitions, all open file descriptors and temporary allocations (linked list nodes, line buffers) are freed before termination.
* **Zero Memory Leaks**: Verified under Valgrind:
  ```sh
  valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/simple.cub
  ```

---

## Resources and References

* **Raycasting Mathematics**:
  * [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
  * [F. Permadi's Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
* **Voxel Traversal**:
  * J. Amanatides & A. Woo, *A Fast Voxel Traversal Algorithm for Ray Tracing* (Eurographics '87).
* **Retro Game Engineering**:
  * Fabien Sanglard, *Game Engine Black Book: Wolfenstein 3D*.
* **Graphic Library**:
  * [42 Docs — MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)

---

## Use of AI Disclosure

In accordance with 42 curriculum standards, AI assistance (large language model) was used strictly as an advisory support tool for:
1. Verifying 2D rotation matrix formulas and perpendicular distance logic in `src/player/rotation.c` and `src/raycasting/dda_algorithm.c`.
2. Reviewing cleanup paths in `src/exit/free.c` to guarantee zero memory leaks upon exit.
3. Structuring and drafting documentation.
