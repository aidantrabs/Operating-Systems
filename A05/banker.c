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
#define MAXC 21

void request_resources();
void release_resources();
void status();
void run();
void exit();
void invoke_command();
void define_resources(); 
void getMaxResourceFromLine();

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
    ssize_t read;
    size_t len = 0;
    char * line;
    char * token;

    // get num tokens in first line to know how long 
    // each resource array should be
    read = getline(&line, &len, fp)
    if (read != -1) { 
        // get count of how many resources each will need
        char* token = strtok(s, " ");
        t_arr_len += 1 
        while (token = strtok(NULL, " ")) { 
            t_arr_len += 1
        }

        // assign the first array values
        getMaxResourceFromLine(&line);
    }
    while ((read = getline(&line, &len, f)) != -1) { 

    }

    return;
}

int* getMaxResourceFromLine(char * line) { 
    int * t_arr = malloc(sizeof(int) * t_arr_len)
    int i = 0
    char* token = strtok(s, " ");
    t_arr[i] = atoi(token);
    while (token = strtok(NULL, " ")) {    
        i += 1
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