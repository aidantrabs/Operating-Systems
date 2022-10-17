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
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[]) { 
    // Teacher Process spawns GTA processes

    int GTA_pipe[2]; // Used for pipe between Teacher process and GTA process
    int TA_pipe[2];  // Used for pipe between GTA process and TA process
    // char* TA_pipe_string; // string used to read/write for TA pipe
    // char* GTA_pipe_string; // string used to read/write for GTA pipe

    pipe(GTA_pipe);

    // Parent process spawns 3 GTA processes
    int GTA_pid, TA_PID;
    int i;  
    for (i = 0; i < 3; i++) {
        GTA_pid = fork();
        if (GTA_pid == 0) {
            break; // GTA process doesn't continue operation
        }
        else if (GTA_pid > 0) { 
            wait(NULL);         // Wait for GTA process completion
            // close(TA_pipe[1]); 

            // int arr[2];        
            // // n stores the total bytes read successfully
            // int n = read(TA_pipe[0], arr, sizeof(arr));
            // Pipe Ta_pipe_string up to Teacher
        }
        else {
            printf("Layer 1 GTA Failure: PID: %d; PPID: %d\n", getpid(), getppid());
            perror("error"); //fork()
        }
    }

    // GTA processes spawns 3 TA processes
    float avg_assignment_grades[2];
    if (GTA_pid == 0) {
        int j = 0; 
        for (j = 0; j < 2; j++) {
            if (GTA_pid == 0) {
                pipe(TA_pipe); // open pipe between parent and child
                TA_PID = fork();
            }
            if(TA_PID > 0) {        // inside of Teacher process
                wait(NULL);         // Wait for GTA process completion
                close(TA_pipe[1]); 

                int arr[100];        
                // n stores the total bytes read successfully
                int n = read(TA_pipe[0], arr, sizeof(arr));
                int k = 0;
                float total = 0;
                int num_grades = n/4; 
                for ( k = 0;k < num_grades; k++) { // GTA processing goes here 
                    total = total + arr[k];
                    fflush(stdout);
                }
                avg_assignment_grades[j] = total / num_grades;
                printf("Assignment %d - Average = %.1f\n", 2*i+j, avg_assignment_grades[j]);
                close(TA_pipe[0]);
            }
            else if( TA_PID == 0 ) {
                int arr[100];
                int temp[100];
                int k = 0; 
                FILE* f2 = fopen("sample_in_grades.txt" , "r");
                if (NULL != f2)
                {
                    char lineBuf[100];
                    while (NULL != fgets(lineBuf, sizeof(lineBuf), f2))
                    {
                        int col = 0;
                        char delim[] = " ";
                        char *str = strtok(lineBuf, delim);
                        while(str != NULL) { 
                            temp[col] = atoi(str); // convert temp into array of column values
                            col++;
                            str = strtok(NULL, delim);
                        }
                        arr[k] = temp[2*i+j]; // 2*i+j => i == (curr_num_GTA - 1) and j == (num_TA for this GTA - 1)
                        k++;
                    }
                    fclose(f2);
                }
                
                close(TA_pipe[0]); // close unused reading end
                write(TA_pipe[1], &arr, k*sizeof(int)); // sends k bites to read
                close(TA_pipe[1]);
                return 0;
            }
            else {
                printf("Layer 2 TA Failure: PID: %d; PPID: %d\n", getpid(), getppid());
                perror("error"); //fork()
            }
        }
    }
    return 0;

    // Teacher Process 
        // info pull from pipe
        // Spawn GTA Child Process
            // get information 
            // print information

    // GTA Process
        // info pull from pipe
        // spawn child processes and have them write to their memory space 
    
    // TA Process
        // Open and read memory space 
        // Open and read file 
        // Read starting char -> increment to same char at next line up until no more file 
        // Increment total -> get average
        // pass up through pipe
}