#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

struct ThreadStruct {
    int sudoku[9][9];
    int validArray[3]; 
};

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
        for (j = 0; j <= 8; j++) {
            count += pow(10, sudoku[i][j]);
        }
        if (count != 1111111110) { 
            return false;
        }
    }
    return true;
}

bool checkColumns(int sudoku[9][9]) { 
    int i, j;
    int count;
    for (j = 0; j < 9; j++) {
        count = 0;
        for (i = 0; i < 9; i++) {
            count += pow(10, sudoku[i][j]);
        }
        if (count != 1111111110) { 
            return false;
        }
    }
    return true;
}

bool checkBox(int sudoku[9][9], int rowStart, int columnStart) { 
    int count = 0;
    int i, j; 
    for (i = rowStart; i < rowStart+3; i++) {
        for (j = columnStart; j<columnStart + 3; j++) { 
            count += pow(10, sudoku[i][j]);
        }
    }
    if (count != 1111111110)
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


void * checkColumnsThread(struct ThreadStruct* input) { 
    if (checkRows(sudoku)) {
        printf("Check Rows Successful \n");
        validResult[0] = 1;
    }
}

void * checkRowsThread(struct ThreadStruct* input) { 
    if (checkColumns(sudoku)) {
        printf("Check Columns Successful \n");
        validResult[1] = 1;
    }
}

void * checkBoxesThread(struct ThreadStruct* input) { 
    if (checkBoxes(sudoku)) {
        printf("Check Boxes Successful \n");
        validResult[2] = 1;
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

    int validResult[3];
    struct ThreadStruct values; 
    values->sudoku = sudoku;
    values->validArray = validResult;

    pthread_t tid1, tid2, tid3; 
    pthread_create(&tid1, NULL, checkRowsThread, (void *)&values);
    // if (checkRows(sudoku)) {
    //     printf("Check Rows Successful \n");
    //     validResult[0] = 1;
    // }
    if (checkColumns(sudoku)) {
        printf("Check Columns Successful \n");
        validResult[1] = 1;
    }
    if (checkBoxes(sudoku)) {
        printf("Check Boxes Successful \n");
        validResult[2] = 1;
    }

    pthread_exit(NULL);

    for (int i = 0; i < 3; i ++) { 
        if (validResult[i] != 1) { 
            printf("Sudoku puzzle is not valid \n");
            return 1;
        }
    }
    printf("Sudoku puzzle is valid \n");
    return 1;
}