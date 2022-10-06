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
    
    // int GTA1 = fork();
    // printf("GTA 1 %i \n", GTA1);
    // wait();
    // if (GTA1 == 0) {
    //     int GTA2 = fork();
    //     printf("GTA 2 %i \n", GTA2);
    //     wait();
    //     if (GTA2 == 0) {
    //         int GTA3 = fork();
    //         printf("GTA3 %i \n", GTA3);
    //         wait();
    //     }
    // } 

    printf("I am the Parent, my PID: %d, my PPID: %d \n", getpid(), getppid());

    // Parent process spawns 3 GTA processes
    int child_pid, GTA_pid;
    int i;  
    for (i = 0; i < 3; i++) {
        child_pid = fork();
        if (child_pid == 0) {
            printf("Child: PID: %d; PPID: %d\n", getpid(), getppid());
            return 0;
        }
    }

    child_pid = fork();
    if (child_pid == 0) {
        printf("Child: PID: %d; PPID: %d\n", getpid(), getppid());
        return 0;
    }

    // code here is for GTA process
    // if (child_pid > 0) { 

    // }

    // for (i = 0; i < 3; i++) {
    //     child_pid = wait(&status);
    //     if (child_pid == -1) {
    //         perror("wait() failed");
    //         return 1;
    //     }

    //     if (WIFEXITED(status)) {
    //         printf("Child %d exited with code %d\n", child_pid, WEXITSTATUS(status));
    //     } else {
    //         // Handle other cases here like WIFSIGNALED, WIFSTOPPED, etc...
    //         // See `man 2 wait` for more information.
    //     }
    // }

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