#include <stdlib.h>
#include <stdio.h>

#define L 9
#define HUMAN 1
#define BOT 2


void initBoard(int board[]);
void printBoard(int const board[]);
int put(int board[], int player, int index);
int where();
void humanMove(int board[]);
int winner(int const board[]);

int main() {

  return 0;
}



void initBoard(int board[]) {
  for (int i = 0; i < L; i++) {
    board[i] = 0;
  }
}

void printBoard(int const board[]) {
  char symbol[] = {'-', 'X', 'O'};
  for (int i = 0; i < L; i++) {
    printf("%c", symbol[board[i]]);
    if (i%3 == 2)
      printf("\n");
  }
}

int put(int board[], int player, int index) {
  if (board[index] != 0)
    return 0;
  board[index] = player;
  return 1;
}

int where() {
  int res;
  int s;
  printf("Where do you want to play?\n");
  while(! (s = scanf("\n%d", &res))) {
    printf("Error, insert int\n");
    while(getchar() != '\n');
    printf("Where do you want to play?\n");
    }
  return res-1;
}

void humanMove(int board[]) {
  int index;
  while ((index = where()) < 0 || index >= L || put(board, HUMAN, index) == 0)
    printf("Error, try again\n");
}

int winner(int const board[]) {
  // Check diagonal
  if (board[4] != 0) {
    if ( (board[0] == board[4] && board[8] == board[4]) || (board[2] == board[4] && board[6] == board[4]) )
      return board[4];
  }

  for (int i = 0; i < L/3; i++) {

    // Check vertical
    if (board[i] != 0 && board[i] == board[i+L/3] && board[i] == board[i+2*L/3])
      return board[i];

    // Check horizontal
    if (board[i*L/3] != 0 && board[i*L/3 + 1] == board[i*L/3] && board[i*L/3] == board[i*L/3 + 2])
      return board[i*L/3];
  }
  return 0;
}
