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
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
     int fd = open(argv[1], O_RDONLY);
     if (fd == -1) {
         perror("open");
         exit(1);
     }

     int pid = fork();
     if (pid == -1) {
         perror("fork");
         exit(1);
     }

     if (pid == 0) {
         int shm_fd = shm_open("shared_memory", O_CREAT | O_RDWR, 0666);
         if (shm_fd == -1) {
             perror("shm_open");
             exit(1);
         }

         ftruncate(shm_fd, 4096);

         char *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
         if (ptr == MAP_FAILED) {
             perror("mmap");
             exit(1);
         }

         int n = read(fd, ptr, 4096);
         if (n == -1) {
             perror("read");
             exit(1);
         }         

         close(fd);
         close(shm_fd);
         munmap(ptr, 4096);

         exit(0);
     }

     int status;
     wait(&status);

     int shm_fd = shm_open("shared_memory", O_RDONLY, 0666);
     if (shm_fd == -1) {
         perror("shm_open");
         exit(1);
     }

     char *ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);

     char *arr = (char *) malloc(4096);
     strcpy(arr, ptr);

     close(shm_fd);
     munmap(ptr, 4096);
     shm_unlink("shared_memory");



}