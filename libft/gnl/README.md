*This project has been created as part of the 42 curriculum by hcosta.*

# get_next_line

A robust, efficient, and leak-free implementation of a function that reads a line from a file descriptor, written in C as part of the 42 curriculum.

---

## Table of Contents
- [Description](#description)
- [Algorithm Explanation and Justification](#algorithm-explanation-and-justification)
- [Instructions](#instructions)
- [Bonus Part](#bonus-part)
- [Testing and Memory Safety](#testing-and-memory-safety)
- [Resources](#resources)

---

## Description

The objective of `get_next_line` is to implement a function that reads from a file descriptor (`fd`) and returns the next line of text, one line per call, ending with a newline character (`\n`) if one is present, or reaching End Of File (EOF).

### Prototype
```c
char *get_next_line(int fd);
```

### Return Values
- **Line read**: String containing the line read from the file descriptor, including `\n` if present.
- **NULL**: If there is nothing more to read (EOF reached) or if an error occurred (such as an invalid file descriptor or memory allocation failure).

### Key Constraints & Rules
- Written in accordance with **Norminette v3**.
- External functions allowed: `read`, `malloc`, `free`.
- Forbidden: `lseek`, global variables, `libft`.
- Must handle arbitrary `BUFFER_SIZE` values (e.g. 1, 42, 9999, 10000000).
- Zero memory leaks at all times, verified with **Valgrind**.

---

## Algorithm Explanation and Justification

### Selected Architectural Model
The algorithm relies on the **Accumulator / Stash pattern** with static state retention. Because standard POSIX `read(2)` consumes arbitrary chunk sizes (`BUFFER_SIZE`) that may cross newline boundaries or encompass only fragments of a line, temporary buffering between function calls is mandatory.

The workflow consists of three primary phases:

```
[get_next_line(fd)]
        |
        v
1. [read_and_stash] ---> Reads from fd using BUFFER_SIZE until '\n' or EOF is found.
        |                Appends buffer into static stash via ft_strjoin_gnl.
        v
2. [extract_line]   ---> Allocates and copies up to the first '\n' (inclusive) or '\0'.
        |                Returns the completed line to the caller.
        v
3. [update_stash]   ---> Preserves characters remaining after '\n' in the stash.
                         If nothing remains or on EOF, frees stash and resets to NULL.
```

### Justification of Algorithmic Choices

1. **Short-Circuit Verification Before Allocation**:
   Before allocating a read buffer in `read_and_stash`, the algorithm checks whether `stash` already contains a newline character (`\n`) from a previous read chunk. If so, it skips `read()` and `malloc()` entirely. This minimizes system calls and heap allocations, satisfying the requirement: *"Try to read as little as possible each time get_next_line() is called."*

2. **Buffer-Localized Search**:
   Inside the reading loop, instead of rescanning the entire accumulated stash from index 0 on each iteration (which results in $O(N^2)$ algorithmic degradation for large lines when `BUFFER_SIZE=1`), the algorithm checks for `\n` directly within the newly read chunk `buffer`. This keeps per-read checks $O(\text{BUFFER\_SIZE})$ and ensures swift execution even with a 1-byte buffer.

3. **Defensive Memory & Leak-Free Lifecycle**:
   - `update_stash` rigorously checks `if (!stash[i] || !stash[i + 1])`. If no characters exist past `\n`, it immediately frees `stash` and returns `NULL`, preventing empty string allocations (`""`) from lingering in the static variable.
   - If an error occurs during `read()` (`bytes_read < 0`), all allocated memory for both the temporary buffer and the current static stash is promptly freed, avoiding unreachable blocks.
   - `ft_strjoin_gnl` automatically frees the previous `s1` (`stash`), ensuring seamless buffer replacement without orphan allocations.

---

## Instructions

### Compilation

You can compile `get_next_line` with your own test `main.c` file using `cc` or `gcc`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

If `-D BUFFER_SIZE` is omitted, it defaults to `42` as defined in `get_next_line.h`.

### Example Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Bonus Part

The bonus implementation introduces:
1. **Single Static Variable**: The entire state is managed using only one static variable:
   ```c
   static char *stash[OPEN_MAX];
   ```
2. **Concurrent Multi-File-Descriptor Reading**:
   Allows alternating reads between multiple file descriptors without losing the state or context of any stream:
   ```c
   char *l1 = get_next_line(fd1);
   char *l2 = get_next_line(fd2);
   char *l3 = get_next_line(fd1); // Resumes exactly where fd1 left off
   ```

### Bonus Compilation
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

---

## Testing and Memory Safety

All mandatory and bonus functions have been tested against:
- Standard 42 test suites (`gnlTester` by Tripouille, custom edge-case test harnesses).
- Buffer sizes: `1`, `2`, `42`, `9999`, and `10000000`.
- Arbitrary inputs: empty files, single characters, files ending with `\n`, files ending without `\n`, multiple empty lines, lines exceeding 20,000 characters, invalid file descriptors (`-1`, closed fds, non-existent fds).
- **Valgrind**: Verified zero memory leaks across all scenarios:
  ```
  HEAP SUMMARY:
      in use at exit: 0 bytes in 0 blocks
  All heap blocks were freed -- no leaks are possible
  ERROR SUMMARY: 0 errors from 0 contexts
  ```

---

## Resources

### References
- [POSIX.1-2017 `read(2)` Specification](https://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html)
- [GNU C Library File Descriptors Documentation](https://www.gnu.org/software/libc/manual/html_node/File-Descriptors.html)
- [Valgrind User Manual & Memcheck Tool](https://valgrind.org/docs/manual/mc-manual.html)
- 42 School Norminette Rules & Guidelines (v3)

### AI Usage Description
In accordance with 42 curriculum guidelines, Artificial Intelligence was utilized as follows:
- **Code Audit & Bug Detection**: AI was used to trace static variable lifetimes and detect reachable block leaks in `update_stash` where an empty string (`""`) remained allocated after reading the final newline.
- **Complexity Analysis**: Diagnosed asymptotic performance bottlenecks under `BUFFER_SIZE=1` in large lines and optimized the newline check localized to the buffer chunk.
- **Norminette Validation**: Verified compliance with 42 Norminette limits (function line limits <= 25 lines, variable declarations, prohibition of forbidden constructs).
- **Test Automation**: Developed synthetic edge-case test runners to evaluate memory behavior under Valgrind.
