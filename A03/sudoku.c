#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

void readSudokuToArray(int sudoku[9][9], FILE** f) { 
    int i, j; 
    for(i = 0; i < 9; i++) { 
        for(j = 0; j < 9; j++) {
            char s[] = "0";
            fscanf(*f, " %c", &s[0]);
            sudoku[i][j] = atoi(s);
        }
    }

    return;
}

void printSudoku(int sudoku[9][9]) { 
    printf("Sudoku Puzzle Solution is:\n");
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
        fflush(stdout);
    }

    return;
}

void spawnThread() { 
    // int threads = 5, i = 0, ret = -1;

    // pthread_t * thread = malloc(sizeof(pthread_t)*threads);

    // int i;
    // for (i = 0; i < threads; i++) {
    //     ret = pthread_create(&thread[i], NULL, &foobar_function, NULL);

    //     if(ret != 0) {
    //         printf ("Create pthread error!\n");
    //         exit (1);
    //     }
    // }
}

bool checkRows(int sudoku[9][9]) {
    int i, j;
    int count;
    for (i = 0; i < 9; i++) {
        count = 0;
        for (j = 0; j < 9; j++) {
            count += 10*sudoku[i][j];
        }
        if (count != 111111111)
            return false;
    }
    return true;
}

bool checkColumns(int sudoku[9][9]) { 
    int i, j;
    for (j = 0; j < 9; i++) {
        for (i = 0; i < 9; j++) {
            count += 10*sudoku[i][j];
        }
        if (count != 111111111)
            return false;
    }
    return true;
}

bool checkBox(int sudoku[9][9], int rowStart, int columnStart) { 
    count = 0;
    int i, j; 
    for (i = start; i < rowStart+3; i++) {
        for (j = columnStart; j<columnStart + 3; j++) { 
            count += 10*sudoku[i][j];
        }
    }
    if (count != 111111111)
        return false;
    return true;
}

bool checkBoxes(int sudoku[9][9]) { 
    int i;
    int count; 
    for (i = 0; i < 9; i+= 3) { // decides starting row of box
        if (!checkBox(sudoku, i, 0)) return false;
        if (!checkBox(sudoku, i, 3)) return false;
        if (!checkBox(sudoku, i, 6)) return false;
    }
    return true;
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

    int validResult[3];
    if (checkRows(sudoku)) {
        validResult[0] = 1;
    }
    if (checkColumns(sudoku)) {
        validResult[1] = 1;
    }
    if (checkBoxes(sudoku)) {
        validResult[2] = 1;
    }

    for (int i = 0; i < 3; i ++) { 
        if (validResult[i] != 1) { 
            printf("Sudoku puzzle is not valid");
            return 1;
        }
    }
    printf("Sudoku puzzle is valid");
    return 1;
}