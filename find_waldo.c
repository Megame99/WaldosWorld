/***********************************************************************************************
 * Filename: find_waldo.c
 * Version: 1.3.1
 * Student Name: Megan Machkouri
 * Student Number: 041006409
 * Course Name/Number: CST 8234
 * Lab Section: 014
 * Assignment Name: Lab 03
 * Due Date: June 18th
 * Submission Date: June 18th
 * Professor Name: Gerald Hurdle
 * Purpose: A simple program that accepts a string as an input, converts the string into a decrypted
 *          string according to the shift key inputted by the user.
 * ********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "find_waldo.h"

/* Global Variables */
int gWaldoColumn = 0;
int gWaldoRow = 0;



/***********************************************************************************************
 * Function Name: main
 * Purpose: Allows for program execution and testing.
 * Function In parameters: nothing
 * Function Out parameters: 0 or 1 
 * Version: 1.3.1
 * Student Name: Megan Machkouri
***********************************************************************************************/

int main(){
char world[MAX_ROWS][MAX_COLS];
int row;
int column;
int input;
int input2;
int rounds;
int isValid = 0;
int r = 1;


    /* Prompt User for rotation key. */
    do{
                /* Set World */
                resetWorld(world);

                /* Prompt User for number of rounds. */
                printf("Enter the number of rounds you need to find Waldo (0 to quit; 10 max): ");
                /* Scan user input and intialize to variable key. */
                input = scanf("%d", &rounds);
                while (getchar() != '\n')
                {
                    /* Chomp stdin (prevents infinite loop)*/
                }
                /* Validate Input(check if non-integer)*/
                if (input != 1)
                {
                    /* Output Error Message */
                    printf("Error - key must be in range 0 and 26. Try Again\n");
                }
                /* Validate Input(range check)*/
                if(rounds < 0 || rounds > MAX_ROUNDS){
                    printf("Error - enter number of rounds between 1 and 10.\n");
                    
                }
                if( rounds == 0){
                    return EXIT_FAILURE;
                }
                else if(rounds >= 0 && rounds <= 10) {
                    isValid = -1;
                    /* Display Game Board*/
                    printWorld(world);
                    /* Hide Waldo at random row and column*/
                    gWaldoColumn = hideWaldoAtColumn();
                    gWaldoRow = hideWaldoAtRow();
                    do
                    {
                        
                        /* Prompt user for guess*/
                        printf("Round %d of %d. Enter row and column (control-d to quit): ", r, rounds);
                        /* Scan user input and intialize to variable row and column. */
                        input2 = scanf("%d %d", &row, &column);
                        while (getchar() != '\n')
                        {
                            /* Chomp stdin (prevents infinite loop)*/
                        }
                        /* Validate Input(check if non-integer)*/
                        if (input2 != 2)
                        {
                            /* Output Error Message */
                           printf("Error - must be in range of 1-10.\n");
                        }
                        else{
                            /* Special Hint Case*/
                            if(column == HINT_COL_INPUT && row == HINT_ROW_INPUT){
                                    printf("Hint: %d %d\n", gWaldoRow, gWaldoColumn);
                                    
                                }
                            /* check if variables are within acceptable range*/    
                            else if(row > 0 && row <= 10 && column > 0 && column <= 10){
                                
                                /* if user guesses correctly*/ 
                                if(isWaldoAt(world, row, column) == 1){
                                    printf("Huzzah you found Waldo.\n");
                                    r++;/* increment counter*/ 
                                   return EXIT_SUCCESS; /* EXIT PROGRAM WITH SUCCESS*/ 

                                }
                                /* if user guesses incorrectly*/ 
                                else {
                                    printf("Miss!\n"); 
                                    r++;/* increment counter*/ 
                                }
                            }
                            /* Out of Range*/ 
                            else {
                                printf("Error - must be in range of 1-10.\n");
                            }
                        }

                    } while (r <= rounds); /* End While*/
                }

    }while(isValid == 0 || r <= rounds); /* End While*/

    /* Return Exit Failure*/ 
    return EXIT_FAILURE;

    }/* End Main */


/***********************************************************************************************
 * Function Name: hideWaldoAtColumn
 * Purpose: Hides Waldo at Column Index
 * Function In parameters: nothing
 * Function Out parameters: void  
 * Version: 1.3.1
 * Student Name: Megan Machkouri
***********************************************************************************************/
   
int hideWaldoAtColumn() {
#ifdef DEBUG
  return DEBUG_COL;
#else
  int randomColumn = (rand() % (10 - 1 + 1)) + 1;
  return randomColumn;
#endif
}

/***********************************************************************************************
 * Function Name: hideWaldoAtRow
 * Purpose: Hides Waldo at Row Index
 * Function In parameters: nothing
 * Function Out parameters: void  
 * Version: 1.3.1
 * Student Name: Megan Machkouri
***********************************************************************************************/
 
int hideWaldoAtRow() {
#ifdef DEBUG
  return DEBUG_ROW;
#else
  /* #TODO - change to random row in range 1 to MAX_ROWS (inclusive) */
  int randomRow = (rand() % (10 - 1 + 1)) + 1;
  return randomRow;
#endif
}

/***********************************************************************************************
 * Function Name: isWaldoAt
 * Purpose: Check's if Waldo is at given index, returns 1 if true and 0 if false
 * Function In parameters: char world[][] (2d array)
 * Function Out parameters: 0 or 1 
 * Version: 1.3.1
 * Student Name: Megan Machkouri
***********************************************************************************************/
 

int isWaldoAt(char world[][MAX_COLS], int row, int column) {
 
  if (row == gWaldoRow && column == gWaldoColumn) /* if guess is correct*/
  {
      resetWorld(world); /* Reset World */ 
      world[row-1][column-1] = 'W'; /* Set index to M*/ 
      printWorld(world); /* Print World*/
      return 1; /* Return True */
  }
  else {  /* if guess is incorrect*/
      resetWorld(world); /* Reset World */ 
      world[row-1][column-1] = 'M';/* Set index to M*/ 
      printWorld(world); /* Print World*/ 
      return 0; /* Return False */
  }
  
  return 0;
}

/***********************************************************************************************
 * Function Name: printWorld
 * Purpose: Print's Waldo's World a 10 x 10 game board 
 * Function In parameters: char world[][] (2d array)
 * Function Out parameters: void  
 * Version: 1.3.1
 * Student Name: Megan Machkouri
***********************************************************************************************/
  
void printWorld(char world[][MAX_COLS]) {
  int c;
  int r;
    printf("  ");
   /* Print Column Heading*/  
  for (r = 0; r < MAX_COLS; r++){ 
            printf(" %2d", (r+1));
        }
    printf("\n");
  /* Print Row Heading */
  for (r = 0; r < MAX_ROWS; r++) {
    printf("%2d ", (r + 1));
  /* Print Array Contents */
    for (c = 0; c < MAX_COLS; c++) {
      printf(" %c ", world[r][c]);
    }
    printf("\n");
  }
}
/***********************************************************************************************
 * Function Name: resetWorld
 * Purpose: Set's all elements of Waldo's World to a "*" char
 * Function In parameters: char world[][] (2d array)
 * Function Out parameters: void  
 * Version: 1.3.1
 * Student Name: Megan Machkouri
***********************************************************************************************/
 
void resetWorld(char world[][MAX_COLS]) {
  int c;
  int r;
  /* Set Array Elements to "*" char */
  for (r = 0; r < MAX_ROWS; r++) {
    for (c = 0; c < MAX_COLS; c++) {
      world[r][c] = '*';
    }
  }
}


    