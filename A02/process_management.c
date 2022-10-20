/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

char *handle_file_shm();
void write_file_shm(char *memory_pointer, char *filename, int length);
void write_output(char *command, char *output);
void handle_shm_cmd(char *memory_pointer);
void pipe_to_file(int pipe_id);

const int SHM_SIZE = 4096;
const char *SHM_FILE = "shm_file";
const char *OUTPUT_FILE = "output.txt";

int main(int argc, char *argv[]) {
    if (argc > 1) {
        char *shm_base = handle_file_shm();
        char *filename = argv[1];
        write_file_shm(shm_base, filename, strlen(filename));
        handle_shm_cmd(shm_base);
    } else {
        fprintf(stderr, "No filename provided");
    }
}

void write_output(char *command, char *output) {
     FILE *fp;
     fp = fopen("output.txt", "a");
     fprintf(fp, "The output of: %s : is\n", command);
     fprintf(fp, ">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
     fclose(fp);
}

char *handle_file_shm() {
    int shm_fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
          printf("Shared memory failed: %s\n", strerror(errno));
          exit(1);
    }

    ftruncate(shm_fd, SHM_SIZE);

    char *shm_base = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (shm_base == MAP_FAILED) {
          printf("Map failed: %s\n", strerror(errno));
          exit(1);
    }

    return shm_base;
}

void write_file_shm(char *shm_base_ptr, char *filename, int length) {
    char *shm_base = shm_base_ptr;
    pid_t pid = fork();

    if (pid == 0) {
          FILE *file = fopen(filename, "r");
          char *line = NULL;
          size_t len = 0;
          ssize_t line_read;

          while ((line_read = getline(&line, &len, file)) != -1) {
               shm_base += sprintf(shm_base, "%s", line);
          }

          exit(0);
     } else if (pid > 0) {
          int status;
          wait(&status);
          if (WEXITSTATUS(status) == -1) {
               printf("Error: %s\n", strerror(errno));
               exit(-1);
          }
          printf("\nwrite_file_to_memory: Done waitin\n"); 
     } 

     else {
          printf("Fork failed: %s\n", strerror(errno));
          exit(1);
     }
}

void handle_shm_cmd(char *shm_base_ptr) {
    char *shm_base = shm_base_ptr;

    char *pipe_name = "/tmp/pipes";
    mkfifo(pipe_name, 0666);
    pid_t pid = fork();

    if (pid == 0) {
          int pipe_id = open(pipe_name, O_WRONLY);
          char result[SHM_SIZE];
          for (int i = 0; i < 64; i += 1) {
               char data = (char)shm_base[i];
               strncat(result, &data, 1);
          }

          char *result_pointer = strtok(result, "\r\n");
          char result[SHM_SIZE];

          while (shm_base) {
               /* SHOULD WRITE OUTPUT TO PIPE HERE */

               shm_base_ptr = strtok(NULL, "\r\n");
          }

          write(pipe_id, result, SHM_SIZE + 1);
          close(pipe_id);
    }

    else if (pid > 0) {
        int pipe_id = open(pipe_name, O_RDONLY);
        int status;
        wait(&status);
        if (WEXITSTATUS(status) == -1) {
          fprintf(stderr, "Error: %s\n", strerror(errno));
          exit(-1);
        }

        pipe_to_file(pipe_id);
        close(pipe_id);
    } else {
          fprintf(stderr, "Fork failed: %s\n", strerror(errno));
          exit(1);
    }
}

void pipe_to_file(int pipe_id) {
    char result[SHM_SIZE];
    read(pipe_id, result, SHM_SIZE);

    /* WRITE FROM PIPE TO FILE USING write_output() method*/
}

