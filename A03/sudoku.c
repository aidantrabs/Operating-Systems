#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void readSudokuToArray(int sudoku[9][9], FILE** f) { 
    int i, j; 
    for(i = 0; i < 9; i++) { 
        for(j = 0; j < 9; j++) {
            char s[] = "0";
            fscanf(f, " %c", &s[0]);
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
            printf("%c ", sudoku[i][j]);
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