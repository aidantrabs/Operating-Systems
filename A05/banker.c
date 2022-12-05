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
#include <stdbool.h>

#define MAXC 21

int t_arr_len = 0;
int num_resources = 0;

int ** test;

int* getMaxResourceFromLine(char *line) { 
    int * t_arr = malloc(sizeof(int) * num_resources);
    int i = 0;
    char* token = strtok(line, " ");
    t_arr[i] = atoi(token);
    while ((token = strtok(NULL, " "))) {    
        i += 1;
        t_arr[i] = atoi(token);
    }

    return t_arr;
}

void readFileToMaxArrAlloc(FILE** f, int ** t_max_arr) { 
    ssize_t read;
    size_t len = 0;
    char * line;
    int * t_arr; 

    // allocate lines and assign to index in array
    int i = 0; 
    while ((read = getline(&line, &len, *f)) != -1) {
        *(t_max_arr + i) = malloc(sizeof(int)*num_resources);
        t_arr = getMaxResourceFromLine(line);
        memcpy(t_max_arr[i], t_arr, sizeof(int) * num_resources);
        i+=1;
    }

    return;
}

void determine_t_arr_len(FILE** f) { 
    ssize_t read;
    size_t len = 0;
    char * line;
     
    // count number of lines
    while ((read = getline(&line, &len, *f)) != -1) { 
        t_arr_len += 1;
    }
    // back to top of file
    rewind(*f);

    return;
}

void invoke_command(char* prefix, char* buf, int* resources) { 
    if (strcmp(prefix, "Exit") == 0) {
        exit(0);
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

bool safety_algorithm(int *available, int **max, int **allocated, int **needed, int num_processes, int num_resources) {
    int *work = malloc(sizeof(int) * num_resources);
    int *is_done = malloc(sizeof(int) * num_processes);
    int i, j, k, count = 0;

    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < num_processes; i++) {
        is_done[i] = 0;
    }

    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_processes; j++) {
            if (is_done[j] == 0) {
                for (k = 0; k < num_resources; k++) {
                    if (needed[j][k] > work[k]) {
                        break;
                    }
                }
                if (k == num_resources) {
                    for (k = 0; k < num_resources; k++) {
                        work[k] += allocated[j][k];
                    }
                    is_done[j] = 1;
                }
            }
        }
    }

    if (count == num_processes) {
        return true;
    } else {
        return false;
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


int main(int argc, char** argv) {
    FILE* f;
    f = fopen("sample_in_baker.txt" , "r");

    int resources[argc - 1];
    if (argc > 1) {
        for (int i = 1; i < argc; i++) { 
            resources[i] = atoi(argv[i]);
            num_resources += 1; 
        }
    } else { 
        exit(0);
    }

    determine_t_arr_len(&f);
    int ** t_max_arr = malloc(sizeof(int*)*t_arr_len);;
    readFileToMaxArrAlloc(&f, t_max_arr);

    for (int i = 0; i < t_arr_len; i++) { 
        for (int j = 0; j < num_resources; j++) { 
            printf("%d ", t_max_arr[i][j]);
        }
        printf("\n");
    }

    while (1) {
        char buf[MAXC];                  
        
        fputs ("enter string: ", stdout);   /* prompt */
        while (fgets(buf, MAXC, stdin)) {   // fgets
            char * prefix = strtok(buf, " ");
            invoke_command(prefix, buf, resources);
        }
    }
}