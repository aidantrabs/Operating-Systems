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

     for (int i = 0; i < NUM_STR; i++) {
          printf("%s", CHOICES[i]);
     }

     char option;
     scanf("%c", &option);

     while (option != 'q') {
          if (option == '1') {
               printf("Enter the name of the directory you want to create:\n");
               char directory_name[100];
               scanf("%s", directory_name);

               int status = mkdir(directory_name, 0777);

               if (status == 0) {
                    printf("Directory created successfully\n");
               } else {
                    printf("Directory was not created\n");
               }
          } 
     
          else if (option == '2') {
               printf("Enter the name of the directory you want to remove:\n");
               char directory_name[100];
               scanf("%s", directory_name);

               int status = rmdir(directory_name);

               if (status == 0) {
                    printf("Directory removed successfully\n");
               } else {
                    printf("Directory was not removed\n");
               }
          } 
          
          else if (option == '3') {
               char cwd[1024];
               getcwd(cwd, sizeof(cwd));
               printf("Current working directory: %s\n", cwd);
          } 
          
          else if (option == '4') {
               char cwd[1024];
               getcwd(cwd, sizeof(cwd));
               printf("Working Directory Before Operation: %s\n", cwd);

               int status = chdir("..");

               if (status == 0) {
                    printf("Directory changed successfully\n");
               } else {
                    printf("Directory was not changed\n");
               }

               getcwd(cwd, sizeof(cwd));
               printf("Working Directory After Operation: %s\n", cwd);
          } 
          
          else if (option == '5') {
               printf("Enter the name of the directory you want to read:\n");
               char directory_name[100];
               scanf("%s", directory_name);

               DIR *dir = opendir(directory_name);

               if (dir == NULL) {
                    printf("Directory was not opened\n");
               } else {
                    printf("Directory opened successfully\n");
               }

               struct dirent *entry;
               while ((entry = readdir(dir)) != NULL) {
                    printf("%s", entry->d_name);
               }

               closedir(dir);
          } 
          
          else if (option == '6') {
               printf("Enter the name of the directory you want to close: ");
               char directory_name[100];
               scanf("%s", directory_name);

               DIR *dir = opendir(directory_name);

               if (dir == NULL) {
                    printf("Directory was not opened");
               } else {
                    closedir(dir);
               }
          }

          for (int i = 0; i < NUM_STR; i++) {
               printf("%s", CHOICES[i]);
          }

          scanf("%c", &option);
     }
     return 0;
}
