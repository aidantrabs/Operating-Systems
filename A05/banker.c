/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>
#define MAXC 21

void request_resources();
void release_resources();
void status();
void run();
void exit();
void invoke_command();
void define_resources(); 

int * t_max_arr;
int * t_curr_arr;
int t_arr_len = 0;
int num_resources = 0;

int main(int argc, char** argv) {
    FILE* f;
    f = fopen("sample_in_sudoku.txt" , "r");

    if (argc > 1) {
        int resources[argc - 1];
        for (int i = 1; i < argc; i++) { 
            resources[i] = argv[i]
        }
    } else { 
        exit();
    }

    while (1) {
        char buf[MAXC];                  
        
        fputs ("enter string: ", stdout);   /* prompt */
        while (fgets(buf, MAXC, stdin);) {   // fgets
            char * prefix = strtok(buf, " ");
            invoke_command(prefix, buf, resources);
        }
    }
}

void readFileToMaxArrAlloc(FILE** f) { 
    int arr_len =
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

void invoke_command(char* prefix, char* buf, int* resources) { 
    if (strcmp(prefix, "Exit") == 0) {
        exit();
    } else if (strcmp(prefix, "Run") == 0) { 
        printf("Not Implemented Yet \n");
    } else if (strcmp(prefix, "Status") == 0) { 
        printf("Not Implemented Yet \n");
    } else if (strcmp(prefix, "RQ") == 0) { 
        printf("Not Implemented Yet \n");
    } else if (strcmp(prefix, "RL") == 0) { 
        printf("Not Implemented Yet \n");
    } else { 
        printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
}


/* RQ Command */
void request_resources() {
    // BANKERS ALGORITHM CONCEPT 
        // never allocate resources to a process when there 
        // aren't enough remaining processes for it to complete

    // iterate over resources required

        // If current available resources < max required
            // deny = true

    // if deny = false 
        // iterate over resources and allocate
}

/* RL Command */
void release_resources() {
    //
}

/* Status Command */
void status() {

}

/* Run Command */
void run() {

}

/* Exit Command */
void exit() {
    exit(0);
}