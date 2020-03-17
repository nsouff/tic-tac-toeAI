#include <stdlib.h>
#include <stdio.h>

#define L 9
#define HUMAN -1
#define BOT 1


void initBoard(int board[]);
void printBoard(int const board[]);
int put(int board[], int player, int index);
int where();
void humanMove(int board[]);
int winner(int const board[]);
int nbEmpty(int const board[]);
void botMove(int board[]);
int minmax(int board[], int depth, int player);
int startingPlayer();
void move(int board[], int player);
void printWinner(int winnerPlayer);
int reset();
void game();

int main() {
  game();
  return 0;
}



void initBoard(int board[]) {
  for (int i = 0; i < L; i++) {
    board[i] = 0;
  }
}

void printBoard(int const board[]) {
  char symbol[] = {'X', '-', 'O'};
  for (int i = 0; i < L; i++) {
    printf("%c", symbol[board[i] + 1]);
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

void botMove(int board[]) {
  int depth = nbEmpty(board);
  int index = minmax(board, depth, BOT);
  board[index] = BOT;
}

int nbEmpty(int const board[]) {
  int c = 0;
  for (int i = 0; i < L; i++) {
    if (!board[i])
      c++;
  }
  return c;
}

// the bot is always the maximazing player
int minmax(int board[], int depth, int player) {
  int winnerPlayer = winner(board);
  if (depth == 0 || winnerPlayer != 0)
    return winnerPlayer;

  // Either bigger than maximum or lower than minimum possible value
  int m = -2*player;
  int res = -1;

  for (int i = 0; i < L; i++) {
    if (!board[i]) {
      board[i] = player;
      int tmp = minmax(board, depth-1, -player);
      if (player == 1 && tmp > m) {
        m = tmp;
        res = i;
      }
      else if (player == -1 && tmp < m) {
        m = tmp;
        res = i;
      }
      board[i] = 0;
    }
  }

  return res;
}

int startingPlayer() {
  char res;
  int s;
  printf("Do you want to start? [y/n]\n");
  while(! (s = scanf("\n%c", &res))) {
    printf("Error, insert y or n\n");
    while(getchar() != '\n');
    printf("Do you want to start? [y/n]\n");
    }
  return (res == 'y') ? HUMAN : BOT;
}

void move(int board[], int player) {
  if (player == BOT)
    botMove(board);
  else
    humanMove(board);
}

void printWinner(int winnerPlayer) {
  if (winnerPlayer == BOT)
    printf("You loose try again\n");
  else if (winnerPlayer == HUMAN)
    printf("You won, unbelievable\n");
  else
    printf("Draw! Well done\n");
}

int reset() {
  char res;
  int s;
  printf("Do you want to play again? [y/n]\n");
  while(! (s = scanf("\n%c", &res))) {
    printf("Error, insert y or n\n");
    while(getchar() != '\n');
    printf("Do you want to play again? [y/n]\n");
    }
  return (res == 'y');
}

void game() {
  int board[L];
  initBoard(board);
  int sPlayer = startingPlayer();
  int winnerPlayer;
  while ( ( !(winnerPlayer = winner(board)) ) || (!nbEmpty(board)) ) {
    printBoard(board);
    move(board, sPlayer);
    sPlayer = -sPlayer;
  }

  printBoard(board);
  printWinner(winnerPlayer);
  if (reset())
    game();
}
