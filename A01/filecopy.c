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

int main() {

     char input_file_name[100];
     char output_file_name[100];

     printf("Enter the name of the input file:\n");
     scanf("%s", input_file_name);

     printf("Enter the name of the output file:\n");
     scanf("%s", output_file_name);

     FILE *input_file = fopen(input_file_name, "r");
     FILE *output_file = fopen(output_file_name, "w");

     if (input_file == NULL) {
          printf("Input file does not exist\n");
          return 0;
     }

     if (output_file == NULL) {
          printf("Output file does not exist\n");
          return 0;
     }

     char ch;
     while ((ch = fgetc(input_file)) != EOF) {
          fputc(ch, output_file);
     }

     fclose(input_file);
     fclose(output_file);

     return 0;
}

