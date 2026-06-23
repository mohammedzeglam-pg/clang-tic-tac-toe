#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define X_SQUARE 1
#define O_SQUARE -1
#define BLANK_SQUARE 0
#define BLANK_GF_WB "\x1b[32;47m"
#define BLANK_GF "\x1b[32m"
#define X_RF_WB "\x1b[31;47m"
#define X_RF "\x1b[31m"
#define O_BF_WB "\x1b[34;47m"
#define O_BF "\x1b[34m"
#define RESET "\x1b[0m"

#define EVEN_OR_ODD(x, do_even, do_odd)                                        \
  if (x % 2 == 0) {                                                            \
    do_even;                                                                   \
  } else {                                                                     \
    do_odd;                                                                    \
  }

#define RETURN_IF_ALL_EQUAL(x, y, z)                                           \
  if ((x == y) && (x == z)) {                                                  \
    return x;                                                                  \
  }

void draw_grid(int g[]) {
  for (int x = 0; x < 9; x++) {
    switch (g[x]) {
    case O_SQUARE:
      EVEN_OR_ODD(x, printf("%s O %s", O_BF_WB, RESET),
                  printf("%s O %s", O_BF, RESET));

      break;
    case X_SQUARE:
      EVEN_OR_ODD(x, printf("%s X %s", X_RF_WB, RESET),
                  printf("%s X %s", X_RF, RESET));
      break;
    case BLANK_SQUARE:
    default:
      EVEN_OR_ODD(x, printf("%s %d %s", BLANK_GF_WB, x + 1, RESET),
                  printf("%s %d %s", BLANK_GF, x + 1, RESET));
    }
    if ((x + 1) % 3 == 0) {
      putchar('\n');
    }
  }
  putchar('\n');
}

int prompt(int p, int grid[]) {
  int square;

  printf("%c's turn: Pick a square, 0 to quit: ", p % 2 ? 'O' : 'X');
  // FIXME: proper handling user input `fgets/3`.
  scanf("%d", &square);
  if (square < 0 || square > 9) {
    puts("Value out range");
    return -1;
  }
  if (square == 0) {
    return square;
  }
  if (grid[square - 1] != 0) {
    printf("Square %d is occupied, try again\n", square);
    return -1;
  }
  return square;
}

int calculate_winner(int grid[]) {
  // ROWS
  RETURN_IF_ALL_EQUAL(grid[0], grid[1], grid[2]);
  RETURN_IF_ALL_EQUAL(grid[3], grid[4], grid[5]);
  RETURN_IF_ALL_EQUAL(grid[6], grid[7], grid[8]);
  // COLUMNS
  RETURN_IF_ALL_EQUAL(grid[0], grid[3], grid[6]);
  RETURN_IF_ALL_EQUAL(grid[1], grid[4], grid[7]);
  RETURN_IF_ALL_EQUAL(grid[2], grid[5], grid[8]);
  // DIAGONAL
  RETURN_IF_ALL_EQUAL(grid[0], grid[1], grid[2]);
  RETURN_IF_ALL_EQUAL(grid[3], grid[4], grid[5]);

  return 0;
}

int main(void) {
  int grid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  puts("Tic Tac Toe");

  int ply = 0, p;

  // game loop
  while (ply < 9) {

    draw_grid(grid);

    p = prompt(ply, grid);

    if (p == 0) {
      break;
    } else if (p == -1) {
      continue;
    }

    // update grid

    grid[p - 1] = ply % 2 ? O_SQUARE : X_SQUARE;

    // calculate winner

    int result = calculate_winner(grid);

    switch (result) {
    case X_SQUARE:
    case O_SQUARE:
      draw_grid(grid);
      printf(">>> %c wins!\n", result == X_SQUARE ? 'X' : 0);
      ply = 9;
      break;
    }
    ply++;
  }

  if (ply == 9) {
    draw_grid(grid);
    puts("Cat's game!");
  }

  return EXIT_SUCCESS;
}
