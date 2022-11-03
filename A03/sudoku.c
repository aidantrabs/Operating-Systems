/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

struct ThreadStruct {
    int sudoku[9][9];
    int validArray[3]; 
    int columnsValid; 
    int rowsValid; 
    int boxesValid;
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

void * checkColumnsThread(void * input) { 
    struct ThreadStruct *input_struct = (struct ThreadStruct*)input;
    if (checkColumns((*input_struct).sudoku)) {
        printf("Check Columns Successful \n");
        (*input_struct).validArray[0] = 1;
    }
}

void * checkRowsThread(void * input) {
    struct ThreadStruct *input_struct = (struct ThreadStruct*)input;
    if (checkRows((*input_struct).sudoku)) {
        printf("Check Rows Successful \n");
        (*input_struct).validArray[1] = 1;
    }
}

void * checkBoxesThread(void * input) {
    struct ThreadStruct *input_struct = (struct ThreadStruct*)input;
    if (checkBoxes((*input_struct).sudoku)) {
        printf("Check Boxes Successful \n");
        (*input_struct).validArray[2] = 1;
    }
}

int main(int argc, char *argv[]) { 
    FILE* f; 
    if (argc == 1) {
        f = fopen("sample_in_sudoku.txt" , "r");
    } else { 
        f = fopen(argv[1] , "r");
    }
    // set sudoku and get values
    int sudoku[9][9];
    readSudokuToArray(sudoku, &f);
    printSudoku(sudoku);

    // create struct to input values to thread
    int validResult[3];
    struct ThreadStruct values; 
    memcpy(&values.sudoku, &sudoku, 81*sizeof(int));
    memcpy(&values.validArray, &validResult, 3*sizeof(int));

    // run threads
    pthread_t tid[3]; 
    pthread_create(&tid[0], NULL, checkRowsThread, (void *)&values);
    pthread_create(&tid[1], NULL, checkColumnsThread, (void *)&values);
    pthread_create(&tid[2], NULL, checkBoxesThread, (void *)&values);

    // await thread completion
    int i;
    for (i = 0; i < 3; i++) { 
        pthread_join(tid[i], NULL);
    }

    // check if result has been set to valid for each
    for (i = 0; i < 3; i ++) { 
        if (values.validArray[i] != 1) { 
            printf("Sudoku puzzle is not valid \n");
            return 1;
        }
    }
    printf("Sudoku puzzle is valid \n");
    return 1;
}