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

void draw_grid(int g[]) {
  for (int x = 0; x < 9; x++) {
    bool even = x % 2 == 0;
    switch (g[x]) {
    case O_SQUARE:
      printf("%s O %s", even ? O_BF_WB : O_BF, RESET);
      break;
    case X_SQUARE:
      printf("%s X %s", even ? X_RF_WB : X_RF, RESET);
      break;
    case BLANK_SQUARE:
    default:
      printf("%s %d %s", even ? BLANK_GF_WB : BLANK_GF, x + 1, RESET);
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
    puts("Value out range.");
    return -1;
  }
  if (square == 0) {
    return square;
  }
  if (grid[square - 1] != BLANK_SQUARE) {
    printf("Square %d is occupied, try again.\n", square);
    return -1;
  }
  return square;
}

int calculate_winner(int grid[]) {
  // ROWS
  if (grid[0] == grid[1] && grid[1] == grid[2]) /* First Row */
    return grid[0];
  if (grid[3] == grid[4] && grid[4] == grid[5]) /* Second Row */
    return grid[3];
  if (grid[6] == grid[7] && grid[7] == grid[8]) /* Third Row */
    return grid[6];

  // COLUMNS
  if (grid[0] == grid[3] && grid[3] == grid[6]) /* First Column */
    return grid[0];
  if (grid[1] == grid[4] && grid[4] == grid[7]) /* Second Column */
    return grid[1];
  if (grid[2] == grid[5] && grid[5] == grid[8]) /* Third Column */
    return grid[2];

  // DIAGONAL
  if (grid[0] == grid[4] && grid[4] == grid[8]) /* Main Diagonal */
    return grid[0];
  if (grid[2] == grid[4] && grid[4] == grid[6]) /* Anti Diagonal */
    return grid[1];

  return 0;
}

int main(void) {
  int grid[] = {BLANK_SQUARE, BLANK_SQUARE, BLANK_SQUARE,
                BLANK_SQUARE, BLANK_SQUARE, BLANK_SQUARE,
                BLANK_SQUARE, BLANK_SQUARE, BLANK_SQUARE};

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
      printf(">>> %c wins!\n", result == X_SQUARE ? 'X' : 'O');
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
