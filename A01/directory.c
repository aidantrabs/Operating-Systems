/**
--------------------------------------
Author: Aidan Traboulay
ID: 200115590
Email: trab5590@mylaurier.ca
--------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LENGTH 60
#define NUM_STR 10

int main() {

     /* Array of strings holding the options */
     const char CHOICES[NUM_STR][MAX_LENGTH] = {
          {"Select the option(s) appropriately by entering the number:\n"},
          {"\tEnter 1 for creating a directory\n"},
          {"\tEnter 2 for removing directory\n"},
          {"\tEnter 3 for printing working directory\n"},
          {"\tEnter 4 for changing directory one level up\n"},
          {"\tEnter 5 for reading the contents of directory\n"},
          {"\tEnter 6 for closing the directory\n"},
          {"\tEnter q to exit the program\n"}
     };

     char option;  

     /* Check that user does not quit */
     while (option != 'q') { 

          fflush(stdout); 

          for (int i = 0; i < NUM_STR; i++) {
               printf("%s", CHOICES[i]);

          }

          scanf(" %c", &option); 

          /* Check if user wants to create directory */
          if (option == '1') { 
               printf("Enter the Directory name you want to create:\n");

               char directory_name[100];

               scanf("%s", directory_name);

               int status = mkdir(directory_name, 0777);

               if (status == 0) { 
                    fprintf(stderr, "Directory is Created Successfully.\n");
               } else {
                    fprintf(stderr, "Directory was not created or already exists.\n");
               }
          } 

          /* Check if user wants to remove directory */
          else if (option == '2') { 
               printf("Enter the Directory name you want to remove:\n");

               char directory_name[100];

               scanf("%s", directory_name);

               int status = rmdir(directory_name);

               if (status == 0) {
                    fprintf(stderr, "Directory is removed Successfully.\n");
               } else {
                    fprintf(stderr, "Directory was not removed.\n");
               }
          } 

          /* Check if user wants to print current working directory */
          else if (option == '3') {
               char cwd[1024];
               getcwd(cwd, sizeof(cwd));

               printf("Current Working Directory is: %s\n", cwd);
          } 

          /* Check if user wants to change directory level */
          else if (option == '4') {
               char cwd[1024];
               getcwd(cwd, sizeof(cwd));

               printf("Working Directory Before Operation: %s\n", cwd);

               int status = chdir("..");

               if (status == 0) {
                    fprintf(stderr, "Directory Changed Successfully.\n");
               } else {
                    fprintf(stderr, "Directory was not changed.\n");
               }

               getcwd(cwd, sizeof(cwd));
               printf("Working Directory After Operation: %s\n", cwd);
          } 

          /* Check if user wants to print current working directory */
          else if (option == '5') {
               char cwd[1024];
               getcwd(cwd, sizeof(cwd));

               DIR *dir = opendir(cwd);
               struct dirent *entry;

               while ((entry = readdir(dir)) != NULL) {
                    printf("%s\n", entry->d_name);
               }
          } 

          /* Check if user wants to close current working directory */
          else if (option == '6') {
               char cwd[1024];
               getcwd(cwd, sizeof(cwd));

               DIR *dir = opendir(cwd);
               closedir(dir);

               printf("Directory Closed Successfully.\n");
          }
     }
     return 0;
}
