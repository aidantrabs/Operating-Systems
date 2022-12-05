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

#define MAXCHAR 21

int t_arr_len = 0;
int num_resources = 0;

int **max;
int **allocated;
int *available;

int* get_max_resource_line(char *line) { 
    int i = 0;
    char* token = strtok(line, ",");
    int * t_arr = malloc(sizeof(int) * num_resources);
    t_arr[i] = atoi(token);
    while ((token = strtok(NULL, ","))) {    
        i += 1;
        t_arr[i] = atoi(token);
    }

    return t_arr;
}

void read_file_to_max_arr(FILE** f, int ** max) { 
    ssize_t read;
    size_t len = 0;
    char * line;
    int * t_arr; 

    // allocate lines and assign to index in array
    int i = 0; 
    while ((read = getline(&line, &len, *f)) != -1) {
        *(max + i) = malloc(sizeof(int)*num_resources);
        t_arr = get_max_resource_line(line);

        for (int j = 0; j < num_resources; j++) { 
            max[i][j] = t_arr[j];
        }

        i += 1;
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

bool safety_algorithm(char *buf) {
    int *request = malloc(sizeof(int) * num_resources);
    int *work = malloc(sizeof(int) * num_resources);
    int *is_done = malloc(sizeof(int) * t_arr_len);
    int counter = 0, i = 0;

    char* token = strtok(buf, ",");
    request[i] = atoi(token);
    
    while ((token = strtok(NULL, ","))) {    
        i += 1;
        request[i] = atoi(token);
    }

    for (int i = 0; i < num_resources; i++) {
        if (request[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < t_arr_len; i++) {
        is_done[i] = 0;
    }

    while (counter < t_arr_len) {
        bool found = false;
        for (int i = 0; i < t_arr_len; i++) {
            if (is_done[i] == 0) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (max[i][j] - allocated[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocated[i][k];
                    }
                    is_done[i] = 1;
                    found = true;
                }
            }
        }

        if (found == false) {
            return false;
        }

        counter++;
    }

    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
    }

    return true;
}

/* RQ Command */
void request_resources(char* buf) {
    int i;
    bool deny = false;
    
    char* token = strtok(buf, " ");
    token = strtok(NULL, " ");
    int customer_number = atoi(token);
    int customer_resources[num_resources];
    i = 0;

    while ((token = strtok(NULL, " "))) {   
        customer_resources[i] = atoi(token);
        i++;
    }

    for (i = 0; i < num_resources; i++) {
        if (customer_resources[i] > max[customer_number][i]) {
            deny = true;
        }
    }

    if (deny == false) {
        for (i = 0; i < num_resources; i++) {
            if (customer_resources[i] > available[i]) {
                deny = true;
            }
        }
    }

    if (deny == false) {
        for (i = 0; i < num_resources; i++) {
            available[i] -= customer_resources[i];
            allocated[customer_number][i] += customer_resources[i];
            max[customer_number][i] -= customer_resources[i];
        }
    }

    if (deny == true) {
        printf("Request is not satisfied \n"); // TODO: add safe state check from safety algorithm
    } else {
        printf("Request is satisfied \n");
    }

    return;
}

/* RL Command */
void release_resources(char* buf) {
    char* token = strtok(buf, " ");
    int temp[num_resources];
    token = strtok(NULL, " "); // get thread num
    int thread_num = atoi(token);
    int i = 0;

    while ((token = strtok(NULL, " "))) {   
        temp[i] = atoi(token);
        i++;
    }

    printf("thread_num: %d \n", thread_num);
    printf("To release: \n");
    for (int j = 0; j < num_resources; j++) { 
        available[j] += temp[j];
        allocated[thread_num][j] -= temp[j];
        printf("%d ", temp[j]);
    }

    printf("\n");

    printf("Now Available Resources: \n");
    for (int j = 0; j < num_resources; j++) { 
        printf("%d ", available[j]);
    }

    printf("\n");

    printf("Resources still held by thread: \n");
    for (int j = 0; j < num_resources; j++) { 
        printf("%d ", allocated[thread_num][j]);
    }

    printf("\n");
}

/* Status Command */
void status() {
    printf("Available Resources: \n");
    int i, j; 
    for (i = 0; i < num_resources; i++) { 
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Max Resources: \n");
    for (i = 0; i < t_arr_len; i++) { 
        for (j = 0; j < num_resources; j++) { 
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("Allocated Resources: \n");
    for (i = 0; i < t_arr_len; i++) {
        for (j = 0; j < num_resources; j++) { 
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }

    printf("Need Resources: \n");
    for (i = 0; i < t_arr_len; i++) { 
        for (j = 0; j < num_resources; j++) { 
            printf("%d ", max[i][j] - allocated[i][j]);
        }
        printf("\n");
    }
}

void release_thread_resources(int thread_num) { 
    printf("--> Customer/Thread %d \n", thread_num);
    printf("    Allocated resources: ");
    for (int i = 0; i < num_resources; i++) { 
        printf("%d ", allocated[thread_num][i]);
    }
    
    printf(" \n");

    printf("    Needed: ");
    for (int i = 0; i < num_resources; i++) { 
        printf("%d ", max[thread_num][i] -  allocated[thread_num][i]);
    }

    printf(" \n");

    printf("    Available: ");
    for (int i = 0; i < num_resources; i++) { 
        printf("%d ", available[i]);
    }

    printf(" \n");

    printf("    Thread has started \n");
    printf("    Thread has finished \n");
    printf("    Thread is releasing resources \n");
    for (int i = 0; i < num_resources; i++) { 
        available[i] += allocated[thread_num][i];
    }

    printf("    New available: ");
    for (int i = 0; i < num_resources; i++) { 
        printf("%d ", allocated[thread_num][i]);
    }

    printf(" \n");
}

/* Run Command */
void run() {
    int thread_valid;
    int remaining_threads[t_arr_len];
    int remaining_thread_count = t_arr_len;
    
    for (int i = 0; i < t_arr_len; i++) { 
        remaining_threads[i] = i;
    }
    
    int thread_num;
    int counter = 0;

    printf("Safe Sequence is: \n");    

    while (remaining_thread_count > 0 && counter < t_arr_len) { 
        for (int i = 0; i < remaining_thread_count; i++) { 
            thread_valid = 1;

            for (int j = 0; j < num_resources; j++) { 
                if (available[j] < (max[i][j] - allocated[i][j])) {
                    thread_valid = 0;
                }
            }

            if (thread_valid == 1) {
                // record thread num
                thread_num = remaining_threads[i];
                // pop element from remaining threads
                for (; i<remaining_thread_count - 1; i++) { 
                    remaining_threads[i] = remaining_threads[i + 1];
                }

                i++;
                
                // reduce remaining thread count
                remaining_thread_count -= 1;

                // invoke print and release function on that index array
                release_thread_resources(thread_num);
            }
        }
        counter++;
    }
}


void invoke_command(char *prefix, char *buf) { 
    if (strcmp(prefix, "Exit") == 0) {
        exit(0);
    } else if (strcmp(prefix, "Run") == 0) { 
        run();
    } else if (strcmp(prefix, "Status") == 0) { 
        status();
    } else if (strcmp(prefix, "RQ") == 0) { 
        request_resources(buf);
    } else if (strcmp(prefix, "RL") == 0) { 
        release_resources(buf);
    } else { 
        printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
}

int main(int argc, char** argv) {
    FILE* f;
    f = fopen("sample_in_banker.txt" , "r");

    available = malloc(sizeof(int) * num_resources);

    if (argc > 1) {
        for (int i = 1; i < argc; i++) { 
            available[i-1] = atoi(argv[i]);
            num_resources += 1; 
        }
    } else { 
        exit(0);
    }

    determine_t_arr_len(&f);
    max = malloc(sizeof(int*)*t_arr_len);
    read_file_to_max_arr(&f, max);
    allocated = malloc(sizeof(int*) * t_arr_len);

    printf("Number of Customers: %d \n", t_arr_len);
    printf("Currently Available Resources: ");
    for (int i = 0; i < num_resources; i++) { 
        printf("%d ", available[i]);
    }

    printf(" \n");

    printf("Maximum resources from file: \n");
    for (int i = 0; i < t_arr_len; i++) { 
        allocated[i] = calloc(num_resources, sizeof(int));
        for (int j = 0; j < num_resources; j++) { 
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    while (1) {
        char buf[MAXCHAR];                  
        
        fputs ("Enter Command: ", stdout);   
        while (fgets(buf, MAXCHAR, stdin)) {  
            char* buff = malloc(sizeof(char) * MAXCHAR);
            strcpy(buff, buf);
            char * prefix = strtok(buf, " \n");
            invoke_command(prefix, buff);
            fputs ("Enter Command: ", stdout);
        }
    }
}