/**
* ENGG1110 24R1 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy a nd
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Li Ho Yuen
 * Student ID    : 1155235714
 * Class/Section : D
 * Date          : 11/15/2024
 */

/****************************************/
/* Header File Declaration */
#include <stdio.h>
#include <stdlib.h>
/* NO other header files are allowed */
/****************************************/
/****************************************/
/* Given Global Variables and Definition */
#define H 6  // height
#define W 6  // width

char candies[] = {'*', '#', '@', '%'};
/* NO other global variables are allowed */
/****************************************/

/****************************************/

/* Part I Functions */
void initGameBoard(int board[][W], int board_sample[][W]);
void printGameBoard(int board[][W]);
int askForSwap(int board[][W]);
void swap(int board[][6], int row1, int col1, int row2, int col2) ;
int findAndRemoveMatch(int board[][W], int row, int col);
int isMatching(int board[6][6], int row, int col);
/* Part II Functions */
int initGameBoardFromFile(int board[][W], int stacks[]);
void applyGravity(int board[][W]);
int fillEmpty(int board[][W], int stacks[], int current, int numCandies);
int cascade(int board[][6], int stacks[], int current, int numCandies);

/****************************************/
// Function Definitions/

/**
 * Main() will call this function in the beginning.
 * initGameBoard() load the game board with the pre-defined board_sample array
 * @param board The gameboard the game is using
 * @param board_sample The given game board sample values
 */
void initGameBoard(int board[H][W], int board_sample[][W]) {
 for (int i = 0; i < H; i++) {
  for (int j = 0; j < W; j++) {
   board[i][j] = board_sample[i][j];
  }
 }
}

/**
 * [Part II]
 * Main() will call this function in the beginning.
 * initGameBoardFromFile will load the file "board.txt" to load two information:
 * (1) Game Board ; (2) Candy Stacks
 * If the file loading is unsuccessful, quit the program with the error message.
 * @param board The Game board the program is using.
 * @param stacks The stack array to store candies. It will be inititalized from the file.
 * @return The number of candies in the stack.
 */
int initGameBoardFromFile(int board[][W], int stacks[]) {
 FILE *brd;
 int row, col,n;
 brd = fopen("D:/sbb/ENGG1110D/project/board.txt", "r");
 if (brd == NULL) {
  printf("Failed to open board.txt!\n");
  exit(-1);
 }
 fscanf(brd, "%d %d", &row, &col);
 for (int i = 0; i < row; i++) {
  for (int j = 0; j < col; j++) {
   fscanf(brd, "%d", &board[i][j]);
  }
 }
 fscanf(brd, "%d", &n);
 for (int i = 0; i < n; i++) {
  fscanf(brd, "%d", &stacks[i]);
 }
 fclose(brd);
 return n;
}

/**
 * Various functions will call this.
 * printGameBoard() will print the current game board in the specified format
 * @param board The game board the game is using
 */
void printGameBoard(int board[][W]) {
 printf("=====\n");
 printf("  | 0 | 1 | 2 | 3 | 4 | 5 |\n");
 for (int i = 0; i < H; i++) {
  printf(" %d|",i);
  for (int j = 0; j < W; j++) {
   if (board[i][j] == 32) {printf("   |");}
   else printf(" %c |", candies[board[i][j]]);

  }
  printf("\n");
 }
}

/**
 * Main() will call this function.
 * askForSwap() will perform the major game logic by (1) asking the users which candy to swap
 * (2)Validate whether the swapping can be done (3) Perform the swapping
 * @param board The game board the game is using.
 * @return 0 if the error is encountered (e.g. Coordinates out of bound);
 * 1 if swapping is successfully
 */
int askForSwap(int board[][W]) {
 printf("Enter the coordinate (row, column) of the candy:");
 int row, col;
 scanf("%d %d", &row, &col);
 if (row >5 || col >5 || row < 0 || col < 0) {
  printf("Coordinates Out of Bound.\n");
  return 0;
 }
 if (board[row][col] == 32) {
  printf("Empty Cell Selected.\n");
 return 0;
 }
printf("Enter the direction to swap (U for Up, D for Down, L for Left, R for Right):");
 char direction;
 scanf("%c", &direction);
 scanf("%c", &direction);
 if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R') {
  printf("Wrong Direction Input.\n");
 return 0;
 }
 if (direction == 'U') {
  if (row-1 < 0) {printf("Move Out of Bound.\n"); return 0;}
  if (board[row-1][col] == 32) {printf("Empty Cell Selected.\n"); return 0;}
  swap(board,row,col,row-1,col);
  if ((findAndRemoveMatch(board,row-1,col))+findAndRemoveMatch(board,row,col)==0) {

    printGameBoard(board);
    printf("No Match found!\n");
    swap(board,row,col,row-1,col);

  }
  else printGameBoard(board);
 }
 if (direction == 'D') {
  if (row+1 > H-1) {printf("Move Out of Bound.\n"); return 0;}
  if (board[row+1][col] == 32) {printf("Empty Cell Selected.\n"); return 0;}
  swap(board,row,col,row+1,col);
  if (!(findAndRemoveMatch(board,row+1,col)||(findAndRemoveMatch(board,row,col)))) {
   printGameBoard(board);
   printf("No Match found!\n");
   swap(board,row,col,row+1,col);
  }
  else printGameBoard(board);
 }
 if (direction == 'L') {
  if (col-1 < 0) {printf("Move Out of Bound.\n"); return 0;}
  if (board[row][col-1] == 32) {printf("Empty Cell Selected.\n"); return 0;}
  swap(board,row,col,row,col-1);
  if (!(findAndRemoveMatch(board,row,col-1)||(findAndRemoveMatch(board,row,col)))) {
   printGameBoard(board);
   printf("No Match found!\n");
   swap(board,row,col,row,col-1);
  }
  else printGameBoard(board);
 }
 if (direction == 'R') {
  if (col+1 > W-1) {printf("Move Out of Bound.\n"); return 0;}
  if (board[row][col+1] == 32) {printf("Empty Cell Selected.\n"); return 0;}
  swap(board,row,col,row,col+1);
  if (!(findAndRemoveMatch(board,row,col+1)||(findAndRemoveMatch(board,row,col)))) {
   printGameBoard(board);
   printf("No Match found!\n");
   swap(board,row,col,row,col+1);
  }
  else printGameBoard(board);


 }


 return 1;
}

/**
 * Various functions will call this
 * swap() will perform value swapping of two cells,
 * with the given source and destination coordinates respectively.
 * @param board the game board the game is using
 * @param row1 The row number of the source cell
 * @param col1 The column number of the source cell
 * @param row2 The row number of the destination cell
 * @param col2 The column number of the destination cell
 */
void swap(int board[][6], int row1, int col1, int row2, int col2) {
  int tmp;
 tmp = board[row1][col1];
 board[row1][col1] = board[row2][col2];
 board[row2][col2] = tmp;
}

/**
 * Various functions will call this.
 * findAndRemoveMatch() will find possible matches at the given coordinates (row,col)
 * for all four directions (Up, Down, Left, Right).
 * If found, turn the cell to ASCII 32 (' ').
 *
 * @param board The game board the game is using
 * @param row The row number of the given coordinate
 * @param col The column number of the given coordinate
 * @return 1 if there is a match in the board, 0 if there is not.
 */
int findAndRemoveMatch(int board[][W], int row, int col) {
 int i,j,count,start,flag,flag1;
 int boardcopy[H][W] ;
 for (i = 0; i < H; i++) {
  for (j = 0; j < W; j++) {
   boardcopy[i][j] = board[i][j];
  }
 }
 count=0;
 flag=1;
 flag1=0;
 for (i = col; i >0; i--) {
  //if (board[row][i] == 32) { count--;}
  if (i >=2){
   if ((boardcopy[row][i] == boardcopy[row][i-1])&& (boardcopy[row][i-1]== boardcopy[row][i-2])&&(boardcopy[row][i]!=32)&&(boardcopy[row][i]==boardcopy[row][col])) {
    count++;
    if (flag){start=i;}
    flag = 0;
   }
  }
 }
 if (count >= 1) {
  count +=2;
  for (i = start; count >0; i--) {
  board[row][i] = 32;
   count--;
 }
  printf("Horizontal Match found at row %d!\n",row);
  flag1 = 1;
 }
 count = 0;
 flag =1;

 for (i = col; i <W; i++) {
  // if (board[row][i] == 32) { count--;}
  if (i <=3) {
   if ((boardcopy[row][i] == boardcopy[row][i+1])&&(boardcopy[row][i+1]==boardcopy[row][i+2])&&(boardcopy[row][i]!=32)&&(boardcopy[row][i]==boardcopy[row][col])) {
    count++;
    if (flag){start=i;}
    flag = 0;
   }
  }
 }
 if (count >= 1) {
  count +=2;
  for (i = start; count>0; i++) {
   board[row][i] = 32;
   count--;
  }
 printf("Horizontal Match found at row %d!\n",row);
  flag1 = 1;
 }
 count = 0;
 flag=1;

 for (i = row; i >0; i--) {
// if (board[i][col] == 32) { count--;}
  if (i>=2) {
   if ((boardcopy[i][col] == boardcopy[i-1][col])&&(boardcopy[i-1][col] == boardcopy[i-2][col])&&(boardcopy[i][col]!=32)&&(boardcopy[i][col]==boardcopy[row][col])) {
    count++;
    if (flag){start=i;}
    flag = 0;
   }
  }
 }
 if (count >= 1) {
  count +=2;
  for (i = start; count >0; i--) {
   board[i][col] = 32;
   count--;
  }
  printf("Vertical Match found at column %d!\n",col);
  flag1 = 1;
 }
 count = 0;
 flag=1;

 for (i = row; i <H; i++) {
 // if (board[i][col] == 32) { count--;}
  if (i<=3) {
   if ((boardcopy[i][col] == boardcopy[i+1][col])&&(boardcopy[i+1][col] == boardcopy[i+2][col])&&(boardcopy[i][col]!=32)&&(boardcopy[i][col]==boardcopy[row][col])) {
    count++;
    if (flag){start=i;}
    flag = 0;
   }
  }
 }
 if (count >= 1) {
  count +=2;
  for (i = start; count>0; i++) {
   board[i][col] = 32;
   count--;
  }
  printf("Vertical Match found at column %d!\n",col);
  flag1 = 1;
 }
 if (flag1){return 1;}
 return 0;
/* int i,countxl,countxr,countyu,countyd,startxl,startxr,startyu,startyd,flag1;
 int flag = 1;
 for (i = col; i >0; i--) {
  if (i >=2) {
   if ((board[row][i] == board[row][i-1])&& (board[row][i-1]== board[row][i-2])&&(board[row][i]!=32)) {
    countxl++;
    if (flag) {
     startxl=i;
    }
    flag = 0;
   }
  }
 }
 flag = 1;
 for (i = col; i <W; i++) {
  if (i <=3) {
   if ((board[row][i] == board[row][i+1])&&(board[row][i+1]==board[row][i+2])&&(board[row][i]!=32)) {
    countxr++;
    if (flag) {
     startxr=i;
    }
    flag = 0;
   }
  }
 }
 flag = 1;
 for (i = row; i >0; i--) {
  if (i>=2) {
   if ((board[i][col] == board[i-1][col])&&(board[i-1][col] == board[i-2][col])&&(board[i][col]!=32)) {
    countyu++;
    if (flag) {
     startyu=i;
    }
    flag = 0;
   }
  }
 }
 flag = 1;
 for (i = row; i <H; i++) {
  if (i<=3) {
   if ((board[i][col] == board[i+1][col])&&(board[i+1][col] == board[i+2][col])&&(board[i][col]!=32)) {
    countyd++;
    if (flag) {
     startyd=i;
    }
    flag = 0;
   }
  }
 }
 if (countxl >= 1) {
  countxl +=2;
  for (i = startxl; countxl >0; i--) {
   board[row][i] = 32;
   countxl--;
  }
  printf("Horizontal Match found at row %d!\n",row);
  flag1 = 1;
 }
 if (countxr >= 1) {
  countxr +=2;
  for (i = startxr; countxr>0; i++) {
   board[row][i] = 32;
   countxr--;
  }
  printf("Horizontal Match found at row %d!\n",row);
  flag1 = 1;
 }
 if (countyu >= 1) {
  countyu +=2;
  for (i = startyu; countyu >0; i--) {
   board[i][col] = 32;
   countyu--;
  }
  printf("Vertical Match found at column %d!\n",col);
  flag1 = 1;
 }
 if (countyd >= 1) {
  countyd +=2;
  for (i = startyd; countyd>0; i++) {
   board[i][col] = 32;
   countyd--;
  }
  printf("Vertical Match found at column %d!\n",col);
  flag1 = 1;
 }
 if (flag1) {
  return 1;
 }
 return 0; */

}

/**
 * Main() function will call this.
 * isGameOver() is to check whether there exists a game over situation, i.e.
 * no more match can be made under the current board scenerio.
 *
 * @param board The game board the game is using.
 * @return 1 if it is game over; 0 if it isn't .
 */
int isGameOver(int board[][W]) {
int i,j;
 for (i=0;i<W;i++) {
  for (j=0;j<H;j++) {
   if (j<5) {
    swap(board,i,j,i,j+1);
    if (isMatching(board,i,j)) {
     swap(board,i,j+1,i,j);
     //  printf("111\n");
     return 1;
    }
    if (isMatching(board,i,j+1)) {
     swap(board,i,j+1,i,j);
     //   printf("222\n");
     return 1;
    }
    swap(board,i,j+1,i,j);
   }
   if (i<5) {
    swap(board,i,j,i+1,j);
    if (isMatching(board,i,j)) {
     swap(board,i+1,j,i,j);
     //  printf("333\n");
     return 1;
    }
    if (isMatching(board,i+1,j)) {
     swap(board,i+1,j,i,j);
     // printf("444\n");
     return 1;
    }
    swap(board,i+1,j,i,j);
   }
  }
 }


 return 0;
}

/**
 * isGameOver() will call this function.
 * isMatching will check if there is at least 1 match-three at the given coordinate (row,col)
 * for four directions (Top,Down,Left,Right).
 * @param board The game board the game is using.
 * @param row The row number of the target cell
 * @param col The column number of the target cell
 * @return 1 if there is at least 1 match in any direction; 0 if there is not.
 */
int isMatching(int board[6][6], int row, int col) {
 if (col<=4){
 if((board[row][col] == board[row][col+1])&&(board[row][col+1]==board[row][col+2])&&(board[row][col]!=32)&&(board[row][col+1]!=32)&&(board[row][col+2]!=32)) {
  // printf("%d %d 11\n",row,col);
  return 1;
 }
}
 if (col>=2) {
  if((board[row][col] == board[row][col-1])&&(board[row][col-1]==board[row][col-2])&&(board[row][col]!=32)&&(board[row][col-1]!=32)&&(board[row][col-2]!=32)) {
   // printf("%d %d 22\n",row,col);
   return 1;
  }
 }
 if (row<=4) {
  if((board[row][col] == board[row+1][col])&&(board[row+1][col]==board[row+2][col])&&(board[row][col]!=32)&&(board[row+1][col]!=32)&&(board[row+2][col]!=32)) {
   // printf("%d %d 33\n",row,col);
   return 1;
  }
 }
 if (row>=2) {
  if((board[row][col] == board[row-1][col])&&(board[row-1][col]==board[row-2][col])&&(board[row][col]!=32)&&(board[row-1][col]!=32)&&(board[row-2][col]!=32)) {
   // printf("%d %d 44\n",row,col);
   return 1;
  }
 }
return 0;
}

/**
 * [Part II]
 * askForSwap() and cascade() will call this function
 * applyGravity() will scan the all columns from left to right, and
 * if there are empty cells, it will move down the candy. Lastly, print the
 * gameboard.
 * @param board The game board the game is using
 */
void applyGravity(int board[][6]) {
 int i,j,tmp,num;
 num = 0;
 for (j=0;j<W;j++) {
  for (i=H-1;i>=0;i--) {
   num = i;
   if (board[i][j]==32) {
    while (board[num][j]==32) {
     num--;
     if (num<0) {break;}
    }
    if (num<0) {break;}
    tmp = board[i][j];
    board[i][j] = board[num][j];
    board[num][j] = tmp;
   }
  }
 }

 printGameBoard(board);
}

/**
 * [Part II]
 * askForSwap() and cascade() will call this.
 * fillEmpty() will scan the columns from left to right. If there are empty cells,
 * it will fill them with candies got from the stacks, in bottom-to-top manner. Lastly,
 * print the gameboard.
 * @param board the game board the game is using
 * @param stacks the 1D array containing the  candies
 * @param current the counter of the next candy location in stacks array
 * @param numCandies the total number of candies in the stacks
 * @return the updated current value, i.e. the updated counter pointing to the next
 * available candy
 */
int fillEmpty(int board[][W], int stacks[], int current, int numCandies) {
  int i,j;
 for (j=0;j<W;j++) {
  for (i=H-1;i>=0;i--) {
    if (board[i][j]==32) {
     board[i][j] = stacks[current];
     current++;
    }
  }
 }
 if (current >= numCandies) {
  printf("No more candies available. ");
  exit(-1);
 }
 printGameBoard(board);
 return current;
}

/**
 * [Part II]
 * main() function will call this
 * cascade() will continously check the board to see if there is any matches
 * and perform removal until no further matches can be found.
 * First, you can apply the gravity and fill in the empty cells.
 * Then, for each cells on the board and if it is not empty, try to call
 * findAndRemoveMatch() to remove matches if any. If there is a match,
 * print the specified message.
 * Remember to collect the return value of current in fillEmpty() such that
 * you return to the main function to update the variable.
 * @param board the game board the game is using
 * @param stacks the 1D array containing the candies
 * @param current the counter of the next candy location in stacks array
 * @param numCandies the total number of candies in the stacks
* @return the updated current value, i.e. the updated counter pointing to the next
 * available candy
 */
int cascade(int board[][6], int stacks[], int current, int numCandies) {
int i,j=0;
 int flag = 1;
 int flag1 = 0;
 int flagforcascade=0;
 while (flag) {
  flag1 = 0;
  flagforcascade = 0;
  applyGravity(board);
  current=fillEmpty(board,stacks,current,numCandies);
 //printf("%d",current);
  for(i=0;i<W;i++) {
   for(j=0;j<H;j++) {
    if (findAndRemoveMatch(board,i,j)) {
  //   printf("%d%d",i,j);
     flagforcascade++;

     flag1 = 1;
  //printf("%d",current);
     break;
    }
   }
  }
  if (flagforcascade) {printf("Cascade Matches found!\n");}
  if (!flag1) {flag=0;}
 }

 return current;
}
/* Main Function */
/**
 * The main function will hold the game loop and hold the game logic.
 * main() will call various functions to accompolish various tasks such as
 * initializing the game board, asking for Input, and etc.
 * It will hold an infinite loop to repeatly hold the game. If it is a game over status,
 * i.e. isGameOver() returns one (1), then it will break out of the loop and the program
 * finishes.
 *
 * @return 0
 */
int main(void) {
 // This is the variable holding a sample board value
 int board_sample[6][6] = {
  {1,3,2,0,1,0},
  {2,2,0,1,1,3},
  {1,3,3,2,3,0},
  {3,0,2,1,0,2},
  {1,0,2,3,3,2},
  {3,2,1,0,3,3}
 };

 int board[H][W] = {0}; // The game board, initialized to 0
 int stacks[100] = {0}; // Stacks array containing candy, Maximum capacity 100
 int numCandies = 0; // Number of candies in the stacks
 int current = 0; // the counter pointing to the next available candy
// You may declare more variables if needed.

 // 1. First, you may initialize the board first
 // For part 1, you may use initGameBoard() while for part 2, initGameBoardFromFile()

 // Then, you may hold a loop to keep the game running
  numCandies = initGameBoardFromFile(board,stacks);
  //initGameBoard(board, board_sample);
  // printf for your reference
//111
 while (isGameOver(board)) {
  printf("=====\n");
  printf("New Round:\n");
  printGameBoard(board);
 if (!askForSwap(board)) {printf("Please try again.\n");}
  else {current=cascade(board,stacks,current,numCandies);}

 }
 printf("Game Over! No more possible moves.\n");
 // Print the board using printGameBoard()

  // Call askForSwap() to ask which candy to swap and perform swapping if successful.
  // If not, print error message, shown for your reference

  // printf("Please try again.\n");

  // Otherwise, continue the game logic by applying gravity and filling empty cells
  // For part II, you may replace the above two to cascade(), as cascade() will be
  // responsible to call at that moment.

 // Check if it is a game over status. If yes, print the message and break the loop
 // printf is left for your reference.

  // printf("Game Over! No more possible moves.\n");

// Hope you enjoy the game : )













 return 0;
}