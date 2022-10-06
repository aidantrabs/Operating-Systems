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


    // int GTA1, GTA2, GTA3;
    

    // Teacher Process spawns GTA processes

    printf("I am the Parent, my PID: %d, my PPID: %d \n", getpid(), getppid());

    // Parent process spawns 3 GTA processes
    int GTA_pid, TA_PID;
    int i;  
    for (i = 0; i < 3; i++) {
        GTA_pid = fork();
        if (GTA_pid == 0) {
            printf("Layer 1 Child: PID: %d; PPID: %d\n", getpid(), getppid());
            break;
        }
        wait();
    }

    // GTA processes spawns 3 TA processes
     
    if (GTA_pid == 0) {
        for (i = 0; i < 2; i++) {
            TA_PID = fork();
            if (TA_PID == 0) {
                printf("Layer 2 Child: PID: %d; PPID: %d\n", getpid(), getppid());
                return 0;
            }
            wait();
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