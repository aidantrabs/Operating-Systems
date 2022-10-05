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
        printf("Program must be run with only one arg being fileName")
        exit(EXIT_FAILURE);
    }
    const char *name = argv[1];	// file name
    const int SIZE = 4096;		// file size

    const char *message0 = "Studying ";
    const char *message1 = "Operating Systems ";
    const char *message2 = "Is Fun!";
    const char *msg_end  = "\n";

    int shm_fd;		// file descriptor, from shm_open()
    char *shm_base;	// base address, from mmap()
    char *ptr;		// shm_base is fixed, ptr is movable

    /* create the shared memory segment as if it was a file */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("prod: Shared memory failed: %s\n", strerror(errno));
        exit(1);
    }
  
    
}
