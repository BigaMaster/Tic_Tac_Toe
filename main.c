//Made by Matheus Bigarelli
//Computer engineering student at UTFPR - Brazil

#include <stdio.h>
#include <stdlib.h>


#define ROWS 3
#define COLUMNS 3


typedef struct { int x, y; } Position;

int** createBoard (int n_rows, int n_columns);
void destroyBoard (int** board, int n_rows);
void makeMove (int** board, int n_rows, int n_columns, int player);
void printBoard (int** board, int n_rows, int n_columns);
int checkWinner (int** board, int n_rows, int n_columns, int* winner);
int completedRow (int** board, int n_rows, int n_columns, int* winner);
int completedColumn (int** board, int n_rows, int n_columns, int* winner);
int completedMainDiagonal (int** board, int n_rows, int n_columns, int* winner);
int completedSecondaryDiagonal (int** board, int n_rows, int n_columns, int* winner);
int gameOver (int** board, int n_rows, int n_columns);



int main()
{
    int** board, player = 1;
    int wanna_play = 1;
    int winner;

    while (wanna_play) {
        board = createBoard(ROWS, COLUMNS);

        printBoard(board, ROWS, COLUMNS);
        while (!gameOver(board, ROWS, COLUMNS) && !checkWinner(board, ROWS, COLUMNS, &winner)) {
          makeMove(board, ROWS, COLUMNS, player);
          printBoard(board, ROWS, COLUMNS);
          player *= -1;
        }

        if (winner == 1)
          printf("Congratulations x ! You won!!\n");

        else
          printf("Congratulations o ! You won!!\n");

        destroyBoard(board, ROWS);
        printf("Wanna play again? [1][0]: ");
        fflush(stdin);
        scanf("%d", &wanna_play);
    }

    system("clear");

    return 0;
}


int** createBoard (int n_rows, int n_columns) {
    int** board, row, column;

    board = malloc (sizeof(int*) * n_rows);

    for (row = 0; row < n_rows; row++)
        board[row] = malloc (sizeof(int) * n_columns);

    for (row = 0; row < n_rows; row++)
        for (column = 0; column < n_columns; column++)
            board[row][column] = 0;

    return board;
}


void destroyBoard (int** board, int n_rows) {
    int row;

    for (row = 0; row < n_rows; row++) {
        free(board[row]);
    }

    free(board);
}


void makeMove (int** board, int n_rows, int n_columns, int player) {
    int x_position, y_position;
    char player_mark;

    if (player == 1)
        player_mark = 'x';
    else
        player_mark = 'o';

    printf("Player %c\nNext position to be marked: ", player_mark);
    scanf ("%d,%d", &x_position, &y_position);


    if (0 <= x_position && x_position < n_rows && 0 <= y_position && y_position < n_columns) {
        if (player == 1) {
            if (!board[y_position][x_position])
                board[y_position][x_position] = 1;
            else {
                printBoard(board, n_rows, n_columns);
                printf("Invalid position\n");
                makeMove(board, n_rows, n_columns, player);
            }

        } else {
            if (!board[y_position][x_position])
                board[y_position][x_position] = -1;
            else {
                printBoard(board, n_rows, n_columns);
                printf("Invalid position\n");
                makeMove(board, n_rows, n_columns, player);
            }
        }
    } else {
        printBoard(board, n_rows, n_columns);
        printf("Invalid position\n");
        makeMove(board, n_rows, n_columns, player);
    }
}


void printBoard (int** board, int n_rows, int n_columns) {
  int row, column, vert_lines, hor_lines = 2;

  system("clear");

  for (row = 0; row < n_rows; row++) {
      vert_lines = 2;

      for (column = 0; column < n_columns; column++) {
          if (board[row][column] == 1)
              printf(" x ");
          else if (!board[row][column])
              printf("   ");
          else
              printf(" o ");

          if (vert_lines)
              printf("|");
          vert_lines--;
      }

      printf("\n");

      if (hor_lines)
          for (column = 0; column < n_columns; column++)
              printf("----");
      hor_lines--;

      printf("\n");
  }

}



int checkWinner (int** board, int n_rows, int n_columns, int* winner) {
    if (completedRow(board, n_rows, n_columns, winner)) {
      return 1;
    }
    if (completedColumn(board, n_rows, n_columns, winner)) {
      return 1;
    }
    if (completedMainDiagonal(board, n_rows, n_columns, winner)) {
      return 1;
    }
    if (completedSecondaryDiagonal(board, n_rows, n_columns, winner)) {
      return 1;
    }

    return 0;
}
//Made by Matheus Bigarelli

int completedRow (int** board, int n_rows, int n_columns, int* winner) {
  int row, column, counter;

  for (row = 0; row < n_rows; row++) {
    counter = 0;
    for (column = 0; column < n_columns; column++) {
      if (board[row][column] == 1)
        counter++;
      if (board[row][column] == -1)
        counter--;
    }

    if (counter == 3)
    {
      *winner = 1;
      return 1;
    }

    if (counter == -3)
    {
      *winner = -1;
      return 1;
    }
  }

  return 0;
}


int completedColumn (int** board, int n_rows, int n_columns, int* winner) {
  int row, column, counters[3];

  for (column = 0; column < n_columns; column++) {
    counters[column] = 0;
  }

  for (row = 0; row < n_rows; row++) {
    for (column = 0; column < n_columns; column++) {
      if (board[row][column] == 1)
        counters[column]++;
      if (board[row][column] == -1)
        counters[column]--;
    }
  }

  for (column = 0; column < n_columns; column++) {
    if (counters[column] == 3)
    {
      *winner = 1;
      return 1;
    }

    if (counters[column] == -3)
    {
      *winner = -1;
      return 1;
    }
  }

  return 0;
}


int completedMainDiagonal (int** board, int n_rows, int n_columns, int* winner) {
  int counter = 0, row, column;

  for (row = 0; row < n_rows; row++) {
    for (column = 0; column < n_columns; column++) {
      if (row == column) {
        if (board[row][column] == 1)
          counter++;
        if (board[row][column] == -1)
          counter--;
      }
    }
  }

  if (counter == 3)
  {
    *winner = 1;
    return 1;
  }

  if (counter == -3)
  {
    *winner = -1;
    return 1;
  }

  return 0;
}


int completedSecondaryDiagonal (int** board, int n_rows, int n_columns, int* winner) {
  int row, column, counter = 0;

  for (row = 0; row < n_rows; row++) {
    for (column = 0; column < n_columns; column++) {
      if (row + column == n_rows - 1) {
        if (board[row][column] == 1)
          counter++;
        if (board[row][column] == -1)
          counter--;
      }
    }
  }

  if (counter == 3)
  {
    *winner = 1;
    return 1;
  }

  if (counter == -3)
  {
    *winner = -1;
    return 1;
  }

  return 0;
}


int gameOver (int** board, int n_rows, int n_columns) {
  int row, column;

  for (row = 0; row < n_rows; row++) {
      for (column = 0; column < n_columns; column++) {
          if (board[row][column] == 0)
              return 0;
      }
  }

  return 1;
}

//Made by Matheus Bigarelli