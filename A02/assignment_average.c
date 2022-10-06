/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 
Emails: trab5590@mylaurier.ca & 
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
#include <errno.h>


int main(int argc, char *argv[]) { 
    if (argc != 1) { 
        printf("Program must be run with only one arg being fileName");
        exit(EXIT_FAILURE);
    }
    const char *name = "sample_in_grades.txt";	// file name
    int status;
    
    // Teacher Process spawns GTA processes
    printf("I am the Parent, my PID: %d, my PPID: %d \n", getpid(), getppid());

    int GTA_pipe[2]; // Used for pipe between Teacher process and GTA process
    int TA_pipe[2];  // Used for pipe between GTA process and TA process
    char* TA_pipe_string; // string used to read/write for TA pipe
    char* GTA_pipe_string; // string used to read/write for GTA pipe

    int GTA_pid, TA_PID; // PIDs for 
     // Parent process spawns 3 GTA processes
    int i;  
    for (i = 0; i < 3; i++) {
        GTA_pid = fork();
        if (GTA_pid == 0) {
            printf("Layer 1 GTA: PID: %d; PPID: %d\n", getpid(), getppid());

            // Open reading end of pipe between GTA and TA
            if (pipe(TA_pipe) < 0) { 
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            close(TA_pipe[1]); // Close writing end of TA_pipe for GTA process
            break;
        }
        wait(); // wait for execution of child process to complete
        read(TA_pipe[0], TA_pipe_string, 100); // read information put into pipe
        printf("TA_piped_string:  %s\n", TA_pipe_string);
        // Pipe Ta_pipe_string up to Teacher
    }

    // GTA processes spawn 3 TA processes
    if (GTA_pid == 0) {
        for (i = 0; i < 2; i++) {
            TA_PID = fork();
            if (TA_PID == 0) {
                printf("Layer 2 TA: PID: %d; PPID: %d\n", getpid(), getppid());
                close(TA_pipe[0]); // Close Reading end of TA_pipe for TA process
                
                TA_pipe_string = "Average of column goes here"
                write(TA_pipe[1], TA_pipe_string, strlen(TA_pipe_string) + 1);
                return 0;
            }
            wait();
        }
    }

    close(TA_pipe[1]); 
    close(TA_pipe[0]); 
    close(TA_pipe[0]);
    close(GTA_pipe[0]);

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

float avgOfColumnOfFile(int column_num, *char file_name) { 

}

int* createPipe() { 
    pipe(fd1)
}