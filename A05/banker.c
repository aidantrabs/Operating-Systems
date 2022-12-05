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

void request_resources();
void release_resources();
void status();
void run();
void exit();
void invoke_command();
void define_resources(); 
int* getMaxResourceFromLine(char *line);
bool safety_algorithm(int *available, int **max, int **allocated, int **needed, int num_processes, int num_resources);


int *t_max_arr;
int *t_curr_arr;

int t_arr_len = 0;
int num_resources = 0;

int main(int argc, char** argv) {
    FILE* f;
    f = fopen("sample_in_baker.txt" , "r");

    int resources[argc - 1];

    if (argc > 1) {
        for (int i = 1; i < argc; i++) { 
            resources[i] = argv[i];
            num_resources += 1; 
        }
    } else { 
        exit();
    }

    readFileToMaxArrAlloc(*f);

    while (1) {
        char buf[MAXC];                  
        
        fputs ("enter string: ", stdout);   /* prompt */
        while (fgets(buf, MAXC, stdin)) {   // fgets
            char * prefix = strtok(buf, " ");
            invoke_command(prefix, buf, resources);
        }
    }
}

void readFileToMaxArrAlloc(FILE** f) { 
    ssize_t read;
    size_t len = 0;
    char * line;
    char * token;
    int * t_arr;

    // count number of lines
    while ((read = getline(&line, &len, f)) != -1) { 
        t_arr_len += 1;
    }
    // !TODO: CODE HERE TO GO BACK TO TOP OF FILE
    
    malloc(t_arr_len * sizeof(int[]))
    // allocate lines and assign to index in array
    int i = 0; 
    while ((read = getline(&line, &len, f)) != -1) { 
        t_arr = getMaxResourceFromLine(&line);
        t_max_arr[i] = &t_arr;
    }

    return;
}

int* getMaxResourceFromLine(char *line) { 
    int * t_arr = malloc(sizeof(int) * num_resources);
    int i = 0;
    char* token = strtok(s, " ");
    t_arr[i] = atoi(token);
    while (token = strtok(NULL, " ")) {    
        i += 1;
        t_arr[i] = atoi(token);
    }

    return t_arr;
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
    // BANKERS ALGORITHM CONCEPT 
        // never allocate resources to a process when there 
        // aren't enough remaining processes for it to complete

    // iterate over resources required

        // If current available resources < max required
            // deny = true

    // if deny = false 
        // iterate over resources and allocate
void request_resources(int *resources, int *available, int **max, int **allocated, int **needed, int num_processes, int num_resources) {
    int *request = malloc(sizeof(int) * num_resources);
    int *available_temp = malloc(sizeof(int) * num_resources);
    int *allocated_temp = malloc(sizeof(int) * num_resources);
    int *needed_temp = malloc(sizeof(int) * num_resources);
    bool deny = false;
    int i, j, k;

    for (i = 0; i < num_resources; i++) {
        request[i] = resources[i];
    }

    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            if (request[j] > needed[i][j]) {
                deny = true;
                break;
            }
        }
    }

    if (deny == false) {
        for (i = 0; i < num_resources; i++) {
            if (request[i] > available[i]) {
                deny = true;
                break;
            }
        }
    }

    if (deny == false) {
        for (i = 0; i < num_resources; i++) {
            available_temp[i] = available[i] - request[i];
            allocated_temp[i] = allocated[i] + request[i];
            needed_temp[i] = needed[i] - request[i];
        }

        if (safety_algorithm(available_temp, max, allocated_temp, needed_temp, num_processes, num_resources) == true) {
            for (i = 0; i < num_resources; i++) {
                available[i] = available_temp[i];
                allocated[i] = allocated_temp[i];
                needed[i] = needed_temp[i];
            }
        } else {
            deny = true;
        }
    }

    if (deny == true) {
        fprintf(stdout, "State is not safe, and request is not satisfied \n");
    } else {
        fprintf(stdout, "State is safe, and request is satisfied \n");
    }
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