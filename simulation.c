// Assignment 1 20T1 COMP1511: Minesweeper
// paint.c
//
// This program was written by CHAN WOO BAEK (z5259628)
// on 9/03/2020
//
// Version 1.0.0 (2020-03-08): Assignment released.
// Version 1.0.1 (2020-03-08): Fix punctuation in comment.

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7

// Add any extra #defines here.
#define END_GAME                0

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

// Place your function prototyes here.
void print_gameplay_minefield(int minefield[SIZE][SIZE], int rConfirm, 
int array[SIZE][SIZE]); 
void print_endGameplay_minefield(int minefield[SIZE][SIZE], int array[SIZE][SIZE]);
void check_array(int *integer);
void array_shift(int minefield[SIZE][SIZE]);

int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");
    
    // TODO: Scan in the number of pairs of mines.
    int numMines;
    scanf("%d", &numMines);
    
    
    printf("Enter pairs:\n");
    
    // TODO: Scan in the pairs of mines and place them on the grid.
    int counter = 0;
    int row, col;
    while (counter < numMines) {
        
        scanf("%d %d",&row, &col);
        if (row >= 0 && col >= 0) {
            if (row < SIZE && col < SIZE) {
                minefield[row][col] = HIDDEN_MINE;
            }
        }
        
        counter++;
    }
    
    
    
    printf("Game Started\n");
    print_debug_minefield(minefield);

    // TODO: Scan in commands to play the game until the game ends.
    // A game ends when the player wins, loses, or enters EOF (Ctrl+D).
    // You should display the minefield after each command has been processed.
    int command = -1, helpCounter = 0, gpMode = 0, GameEnd = 0;
    int rConfirm = 0, array[SIZE][SIZE] = {0}, ShiftDown = 0;
    int useless1 = 0, useless2 = 0, useless3 = 0, useless4 = 0;
    while (command != END_GAME) {
        
        if (scanf("%d", &command) == EOF) {
            command = END_GAME;
        }
        if (command == EOF) {
            command = END_GAME;
        }
        //Detect Row Code
        if (command == DETECT_ROW && helpCounter < 3) {
            int dRow;
            int a = 0;
            int totalRow = 0;
            scanf("%d", &dRow);
            while (a < SIZE) {
                if (minefield[dRow][a] == HIDDEN_MINE) {
                    totalRow++;
                    
                }
                a++;
                
            }
            printf("There are %d mine(s) in row %d\n",totalRow, dRow); 
            helpCounter++;
            if (gpMode == 1) {
                print_gameplay_minefield(minefield, rConfirm, array);  
            } else (print_debug_minefield(minefield));
            
        //Detect Column Code
        
        } else if (command == DETECT_COL && helpCounter < 3) {
            int dCol;
            int b = 0;
            int totalCol = 0;
            scanf("%d", &dCol);
            while (b < SIZE) {
                if (minefield[b][dCol] == HIDDEN_MINE) {
                    totalCol++;
                    
                }
                b++;
                
            }
            printf("There are %d mine(s) in column %d\n",totalCol, dCol); 
            helpCounter++;  
            if (gpMode == 1) {
                print_gameplay_minefield(minefield, rConfirm, array);  
            } else (print_debug_minefield(minefield));
            
        //Detect Square Code    
        
        } else if (command == DETECT_SQUARE && helpCounter < 3) {
            int dSqrR, dSqrC, dSqrS, dSqrEndRow, dSqrEndCol, dSqrDif;
            int dSqrStartRow, dSqrStartCol;
            int totalSqr = 0;
            scanf("%d %d %d", &dSqrR, &dSqrC, &dSqrS);
            dSqrDif = (dSqrS - 1)/2;
            dSqrEndRow = dSqrR + dSqrDif;
            dSqrEndCol = dSqrC + dSqrDif;
            dSqrStartRow = dSqrR - dSqrDif;
            dSqrStartCol = dSqrC - dSqrDif;
            while (dSqrStartRow < dSqrEndRow + 1) {
                
                while (dSqrStartCol < dSqrEndCol + 1) {
                    if (minefield[dSqrStartRow][dSqrStartCol] == 2) {
                        totalSqr++;
                    }
                    dSqrStartCol++;
                }
                
                dSqrStartRow++;
                dSqrStartCol = dSqrStartCol - 2 * dSqrDif;
            }
            
            printf("There are %d mine(s) in the square ", totalSqr);
            printf("centered at row %d, column %d", dSqrR, dSqrC );
            printf(" of size %d\n", dSqrS);
            helpCounter++;
            
            if (gpMode == 1) {
                print_gameplay_minefield(minefield, rConfirm, array);  
            } else (print_debug_minefield(minefield));
        
        //REVEAL SQUARE
            
        } else if (command == REVEAL_SQUARE) {
            int rRow, rCol;
            scanf("%d %d", &rRow, &rCol);
            int rStartRow = rRow - 1;
            int rStartCol = rCol - 1;
            check_array(&rStartRow);
            check_array(&rStartCol);
            int rStartRowReset = rStartRow;
            int rStartColReset = rStartCol;
            int rEndRow = rRow + 1;
            int rEndCol = rCol + 1;
            check_array(&rEndRow);
            check_array(&rEndCol);
            //If the chosen array is a mine
            if (minefield[rRow][rCol] == HIDDEN_MINE) {
                if (ShiftDown == 0) {
                    
                    ShiftDown++;
                    array_shift(minefield);
                } else if (gpMode == 1) {
                    printf("Game over\n");
                    GameEnd = 1;
                } else if (gpMode == 0) {
                    printf("Game over\n");
                    command = END_GAME;
                }

                
            }
            //If the chosen array is not a mine
            if (minefield[rRow][rCol] != HIDDEN_MINE) {
                minefield[rRow][rCol] = VISIBLE_SAFE;
                ShiftDown++;
                //Checking if there are mines surrounding the chosen array
                while (rStartRow <= rEndRow) {
                    while (rStartCol <= rEndCol) {
                        if (minefield[rStartRow][rStartCol] == HIDDEN_MINE) {
                            rConfirm++;
                            array[rRow][rCol]++;
                        }
                        rStartCol++;
                    }
                    rStartRow++;
                    rStartCol = rStartColReset;
                }
                //If there are no mines surrounding the chosen array
                if (rConfirm == 0) {
                    rStartRow = rStartRowReset;
                    check_array(&rStartRow);
                    rStartCol = rStartColReset;
                    check_array(&rStartCol);
                    int rStartRow2 = rStartRow - 1;
                    int rStartCol2 = rStartCol - 1;
                    int rEndRow2 = rStartRow2 + 2;
                    int rEndCol2 = rStartCol2 + 2;
                    int rConfirm2 = 0;
                    check_array(&rStartRow2);
                    check_array(&rStartCol2);
                    check_array(&rEndRow2);
                    check_array(&rEndCol2);
                    int duRow = 0;
                    int duCol = 0;
                    
                    int doubleup[SIZE][SIZE] = {0};
                    while (rStartRow <= rEndRow) {
                        while(rStartCol <= rEndCol) {
                            rStartRow2 = rStartRow - 1;
                            rStartCol2 = rStartCol - 1;
                            rEndRow2 = rStartRow2 + 2;
                            rEndCol2 = rStartCol2 + 2;
                        
                            check_array(&rStartRow2);
                            check_array(&rStartCol2);
                            check_array(&rEndRow2);
                            check_array(&rEndCol2);
                            
                            int rStartCol2Reset = rStartCol2;

                            while (rStartRow2 <= rEndRow2) {
                                while (rStartCol2 <= rEndCol2) {
                                    if (minefield[rStartRow2][rStartCol2] == HIDDEN_MINE 
                                    && doubleup[rStartRow2][rStartCol2] == 0) {
                                        rConfirm2++;
                                            
                                    }
                                        
                                    rStartCol2++;
                                }
                                    
                                rStartRow2++;
                                rStartCol2 = rStartCol2Reset;
                                    
                            }
                            if (rConfirm2 != 0) {
                                array[rStartRow][rStartCol] = rConfirm2;
                                rConfirm2 = 0;
                            }
                                
                            while (duRow < SIZE) {
                                while (duCol < SIZE) {
                                    doubleup[duRow][duCol] = 0;
                                    duCol++;
                                }
                                duRow++;
                                duCol = 0;
                            }
                                
                                
                            minefield[rStartRow][rStartCol] = VISIBLE_SAFE;
                            
                            
                            rStartCol++;
                                
                        }
                        
                        rStartRow++;
                        rStartCol = rStartColReset;
                        
                    }
                    
                }
                
                
                int countdown = 0;
                int rTestRow = 0;
                int rTestCol = 0;
                while (rTestRow <= 7) {
                    while (rTestCol <= 7) {
                        if (minefield[rTestRow][rTestCol] == 0 ||
                        minefield[rTestRow][rTestCol] == 2) {
                            countdown++;
                            
                        }  
                        rTestCol++;
                    }
                    rTestCol = 0;
                    rTestRow++;
                }
                if (countdown == 64) {
                    printf("Game won!\n");
                    command = END_GAME;
                }
                
            }
            if (gpMode == 1 && GameEnd != 1) {
                print_gameplay_minefield(minefield, rConfirm, array);  
                rConfirm = 0;
            } else if (GameEnd != 1) {
                print_debug_minefield(minefield);
            }
            rConfirm = 0;
            
        } else if (helpCounter >= 3 && command != REVEAL_SQUARE && command != REVEAL_RADIAL &&  command != DEBUG_MODE && command != GAMEPLAY_MODE) {
            if (command == DETECT_COL || command == DETECT_ROW) {
                
                printf("Help already used\n");
                scanf("%d", &useless1);
                if (gpMode == 1) {
                    print_gameplay_minefield(minefield, rConfirm, array);  
                } else (print_debug_minefield(minefield));
            }
            if (command == DETECT_SQUARE) {
                printf("Help already used\n");
                scanf("%d %d %d", &useless2, &useless3, &useless4);
                if (gpMode == 1) {
                    print_gameplay_minefield(minefield, rConfirm, array);  
                } else (print_debug_minefield(minefield));
            }
        } else if (command == GAMEPLAY_MODE) {
            printf("Gameplay mode activated\n");
            print_gameplay_minefield(minefield, rConfirm, array);
            gpMode = 1;
 
        } else if (command == DEBUG_MODE) {
            printf("Debug mode activated\n");
            gpMode = 0;
            print_debug_minefield(minefield);
        } else if (command == REVEAL_RADIAL) {
            int raRow, raCol;
            int switch1 = 0, switch2 = 0, switch3 = 0, switch4 = 0, switch5 = 0;
            int switch6 = 0, switch7 = 0, switch8 = 0;
            scanf("%d %d", &raRow, &raCol); 
            if (minefield[raRow][raCol] == HIDDEN_MINE) {
                if (ShiftDown == 0) {
                    
                    ShiftDown++;
                    array_shift(minefield);
                } else if (gpMode == 1) {
                    printf("Game over\n");
                    GameEnd = 1;
                } else if (gpMode == 0) {
                    printf("Game over\n");
                    command = END_GAME;
                }
            }
            int raRowReset = raRow;
            int raColReset = raCol;
            int raRowStart = raRow - 1;
            check_array(&raRowStart);
            int raRowStartReset = raRowStart;
            int raRowEnd = raRow + 1;
            check_array(&raRowEnd);
            int raColStart = raCol - 1;
            check_array(&raColStart);
            int raColStartReset = raColStart;
            int raColEnd = raCol + 1;
            check_array(&raColEnd);
            
            int StopNow = 0, raCount = 0, raMineCount = 0;
            
            if (minefield[raRow][raCol] != HIDDEN_MINE) {
                ShiftDown++;
                while (raRowStart <= raRowEnd) {
                    while (raColStart <= raColEnd) {
                        if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                            StopNow = 1;
                            raCount++;
                            minefield[raRow][raCol] = 0;
                            array[raRow][raCol] = raCount;
                        }
                        
                        raColStart++;
                    }
                    raRowStart++;
                }
                if (StopNow == 0) {        
                    //For the up direction
                    while (raRow >= 0 && switch1 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch1 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raRow--;
                        
                    }
                    raRow = raRowReset;
                    
                    //For the down direction
                    while (raRow <= 7 && switch2 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch2 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raRow++;
                    }
                    raRow = raRowReset;
                    //For the right direction
                    while (raCol <= 7 && switch3 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch3 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raCol++;
                    }
                    raCol = raColReset;
                    //For the left direction
                    while (raCol >= 0 && switch4 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch4 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raCol--;
                    }
                    raCol = raColReset;
                    
                    //For the up right direction
                    while (raCol <= 7 && raRow >= 0 && switch5 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch5 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raCol++;
                        raRow--;
                    }
                    raCol = raColReset;
                    raRow = raRowReset;
                    
                    //For the up left direction
                    while (raCol >= 0 && raRow >= 0 && switch6 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch6 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raCol--;
                        raRow--;
                    }
                    raCol = raColReset;
                    raRow = raRowReset;
                    
                    //For the down right direction
                    while (raCol <= 7 && raRow <= 7 && switch7 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch7 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raCol++;
                        raRow++;
                    }
                    raCol = raColReset;
                    raRow = raRowReset;
                    
                    
                    //For the down left direction
                    while (raCol >= 0 && raRow <= 7 && switch8 == 0) {
                        raRowStart = raRow - 1;
                        check_array(&raRowStart);
                        raColStart = raCol - 1;
                        check_array(&raColStart);
                        raRowEnd = raRow + 1;
                        check_array(&raRowEnd);
                        raColEnd = raCol + 1;
                        check_array(&raColEnd);
                        raRowStartReset = raRowStart;
                        raColStartReset = raColStart;
                        while (raRowStart <= raRowEnd) {
                            while (raColStart <= raColEnd) {
                                if (minefield[raRowStart][raColStart] == HIDDEN_MINE) {
                                    raMineCount++;
                                }
                                raColStart++;
                            }
                            raRowStart++;
                            raColStart = raColStartReset;
                        }
                        raRowStart = raRowStartReset;
                        if (raMineCount != 0) {
                            array[raRow][raCol] = raMineCount;
                            minefield[raRow][raCol] = 0;
                            switch8 = 1;
                            raMineCount = 0;
                        } else (minefield[raRow][raCol] = 0);
                        raCol--;
                        raRow++;
                    }
                    raCol = raColReset;
                    raRow = raRowReset;
                }
            }
            
            
            
            if (gpMode == 1) {
                print_gameplay_minefield(minefield, rConfirm, array);  
            } else (print_debug_minefield(minefield));
                
            
        }
        if (GameEnd == 1) {
            print_endGameplay_minefield(minefield, array);
            command = END_GAME;
        }

            
            
                
    }

    return 0;
}

// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

//Print out the ending scene
void print_endGameplay_minefield(int minefield[SIZE][SIZE], int array[SIZE][SIZE]) {
    printf("xx\n/\\\n");
    printf("    00 01 02 03 04 05 06 07\n");
    printf("   -------------------------\n");
    int numCounter = 0;
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            if (j == 0) {
                printf("0%d |", numCounter);
                numCounter++;
            }
            if (minefield[i][j] == VISIBLE_SAFE && array[i][j] == 0) {
                printf("   ");
            } else if (minefield[i][j] == VISIBLE_SAFE && array[i][j] != 0) {
                printf("0%d ", array[i][j]);
            } else if (minefield[i][j] == HIDDEN_MINE) {
                printf("() ");
            } else if (minefield[i][j] == HIDDEN_SAFE) {
                printf("## ");
            }
            j++;
        }
        printf("|\n");
        i++;
    }
    printf("   -------------------------\n");
}
// Printing out gameplay values of the minefield.
void print_gameplay_minefield(int minefield[SIZE][SIZE], int rConfirm, 
int array[SIZE][SIZE]) {
    printf("..\n\\/\n");
    printf("    00 01 02 03 04 05 06 07\n");
    printf("   -------------------------\n");
    int numCounter = 0;
    int gRow = 0;
    while (gRow < SIZE) {
        int gCol = 0;
        while (gCol < SIZE) {
            if (gCol == 0) {
                printf("0%d |", numCounter);
                numCounter++;
            }
            if (minefield[gRow][gCol] == VISIBLE_SAFE && array[gRow][gCol] == 0) {
                printf("   ");
            } else if (array[gRow][gCol] != 0) {
                printf("0%d ", array[gRow][gCol]);
            } else if (minefield[gRow][gCol] == VISIBLE_SAFE && 
            array[gRow][gCol] != 0) {
                printf("0%d ", rConfirm);
                array[gRow][gCol] = rConfirm;
            } else if (minefield[gRow][gCol] == HIDDEN_MINE 
                || minefield[gRow][gCol] == HIDDEN_SAFE) {
                printf("## ");
            }
            gCol++;
        }
        printf("|\n");
        gRow++;
    }
    printf("   -------------------------\n");
}
// Making sure the array integer is valid
void check_array(int *integer) {
    if (*integer < 0) {
        *integer = 0;
    }
    if (*integer > 7) {
        *integer = 7;
    }
}

// Shifting the array down
void array_shift(int minefield[SIZE][SIZE]) {
    int sRow = 7, sCol = 7;
    while (sRow >= 0) {
        while (sCol >= 0) {
            if (sRow == 0) {
                minefield[sRow][sCol] = minefield[7][sCol];
            } else (minefield[sRow][sCol] = minefield[sRow - 1][sCol]);
                
            sCol--;
        }
        sRow--;
        sCol = 7;
    }
    
}
