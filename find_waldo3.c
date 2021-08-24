/***********************************************************************************************
 * Filename: cc_encrypt.c
 * Version: 1.3.1
 * Student Name: Megan Machkouri
 * Student Number: 041006409
 * Course Name/Number: CST 8234
 * Lab Section: 014
 * Assignment Name: Lab 02
 * Due Date: June 4th
 * Submission Date: June 4th
 * Professor Name: Gerald Hurdle
 * Purpose: A simple program that accepts a string as an input, converts the string into a decrypted
 *          string according to the shift key inputted by the user.
 * ********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <find_waldo.h>

#define DEBUG
#define MAX_ROWS 11
#define MAX_COLS 11

int main(){
int grid[MAX_ROWS][MAX_COLS];
int row;
int column;
int input;
int input2;
int rounds;
int isValid = 0;
int r = 1;

void printGrid(int grid[11][11], char result, int row, int column);
    /* Prompt User for rotation key. */
    do{
                printf("Enter the number of rounds you need to find Waldo (0 to quit; 10 max): \n");
                /* Scan user input and intialize to variable key. */
                input = scanf("%d", &rounds);
                while (getchar() != '\n')
                {
                    /* Chomp stdin (prevents infinite loop)*/
                }
                if (input != 1)
                {
                    /* Output Error Message */
                    printf("Error - key must be in range 0 and 26. Try Again\n");
                }
                if(rounds < 0 || rounds > 10){
                    printf("Error - enter number of rounds between 1 and 10.\n");
                }
                if( rounds == 0){
                    return EXIT_FAILURE;
                }
                else {
                    isValid = -1;
                    
                    do
                    {
                        int rowWaldo = 5;
                        int colWaldo = 5;
                        printf("Round %d of %d. Enter row and column (control-d to quit): \n", r, rounds);
                        input2 = scanf("%d %d", &row, &column);
                        while (getchar() != '\n')
                        {
                            /* Chomp stdin (prevents infinite loop)*/
                        }
                        if (input2 != 2)
                        {
                            /* Output Error Message */
                           printf("Error - must be in range of 1-10.\n");
                        }
                        else{
                            
                            if(column == -1 && row == -1){
                                    printf("Hint: %d %d\n", rowWaldo, colWaldo);
                                    r++;
                                }
                            else if(row >= 0 && row <= 10 && column >= 0 && column <= 10){
                                if(colWaldo == column && rowWaldo ==row){
                                    printGrid(grid,'W', row, column-1);
                                    printf("Huzzah you found Waldo.\n");
                                    r++;
                                   return EXIT_SUCCESS;

                                }
                                else {
                                    printGrid(grid,'M', row, column - 1);
                                    printf("Miss!\n");
                                    r++;
                                }
                            }
                            else {
                                printf("Error - must be in range of 1-10.\n");
                            }
                        }

                    } while (r <= rounds);
                }
    }while(isValid != 1 && r <= rounds);



    
   
    
    return EXIT_FAILURE;
    }

    void printGrid(int grid[11][11], char result, int row, int column) {
    int i,j; 
    int cols[MAX_COLS];
    int rows[MAX_ROWS];

       for (i = 1; i < MAX_COLS; i++){
            cols[i] = i;
            
        }
    
        for (i = 0; i < 9; i++) {
            for(i = 1; i < MAX_ROWS; i++){
            rows[i] = i;
            
            
        for (j = 0; j < 11; j++) {
            grid[i][j] = '*';
            
        }
        
        }
        }
        grid[row][column] = result;

         for (i = 1; i < MAX_COLS; i++){
            
            printf("    %d", cols[i]);
        }

    
        for (i = 0; i < 9; i++) {
            for(i = 1; i < 10; i++){
            printf("\n %d ", rows[i]);
            
            
            
        for (j = 0; j < 10; j++) {
            
            printf(" %c   ", grid[i][j]);
        }
        printf("\n");
        }
        printf("\n%d", rows[10]);
         for (i = 0; i < 10; i++){
            printf("  %c  ", grid[10][i]);
            
        }
        printf("\n");
        
        }

    }