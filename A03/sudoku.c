#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readSudokuToArray(int sudoku[9][9], FILE** f) { 
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            char s[] = "0";
            fscanf(file1, " %c", &s[0]);
            sudoku[i][j] = atoi(s);
        }
    }

    return
}

void printSudoku(int sudoku[9][9]) { 
    printf("Sudoku Puzzle Solution is:\n");

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
        fflush(stdout);
    }
}

int main(int argc, char *argv[]) { 
    FILE* f; 
    if (argc == 1) {
        f = fopen("sample_in_sudoku.txt" , "r");
    } else { 
        f = fopen(argv[1] , "r");
    }

    int sudoku[9][9];
    readSudokuToArray(sudoku, &f);
    printSudoku(sudoku);
    

}