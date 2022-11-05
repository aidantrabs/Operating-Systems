/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Thread Info Struct */
typedef struct {
     int p_id;
     int arr_time;
     int burst_time;
     int waiting_time;
     int turn_around_time;
} THREADINFO;

/* Utility function to count lines in file */
int count_lines(char *filename) {
     FILE* fd = fopen(filename, "r");
     int ch, number_of_lines = 0;

     do {
          ch = fgetc(fd);
          if(ch == '\n') {
               number_of_lines++;
          }
     } while (ch != EOF);

     if(ch != '\n' && number_of_lines != 0) {
          number_of_lines++;
     }

     fclose(fd);
     return number_of_lines;
}

/* Main */
int main(int argc, char *argv[]) {
     /* Declare and initialize variables */
     int num_lines = count_lines(argv[1]);                  
     THREADINFO* threads = malloc(sizeof(THREADINFO) * num_lines);  
     FILE *file = fopen(argv[1], "r");
     int i = 0;
     int j = 0;
     char *token;
     char line[1024][1024];
     int burst_count = 0;
     int total_waiting_time = 0;
     int total_turn_around_time = 0;

     /* Read file into struct */
     while (fgets(line[i], sizeof(line), file)) {
          j = 0;
          token = strtok(line[i], ", ");
          while (token != NULL) {
               if (j == 0) {
                    threads[i].p_id = atoi(token);
               } else if (j == 1) {
                    threads[i].arr_time = atoi(token);
               } else if (j == 2) {
                    threads[i].burst_time = atoi(token);
               }
               token = strtok(NULL, ", ");
               j++;
               if (j == 3) { 
                    break;
               }
          }
          i++;
     }
     
     /* Output and Calculations */
     fprintf(stdout, "Thread ID       Arrival Time    Burst Time  Completion Time Turn-Around Time    Waiting Time\n");
     
     for (int j = 0; j < i; j++) {
          threads->p_id = threads[j].p_id;
          threads->arr_time = threads[j].arr_time;
          threads->burst_time = threads[j].burst_time;
          threads->waiting_time = threads[j].waiting_time;
          threads->turn_around_time = threads[j].turn_around_time;
          burst_count += threads[j].burst_time;
          threads[j].turn_around_time = burst_count - threads[j].arr_time;
          threads[j].waiting_time = threads[j].turn_around_time - threads[j].burst_time;
          total_waiting_time += threads[j].waiting_time;
          total_turn_around_time += threads[j].turn_around_time;

          fprintf(stdout, "%-24d%-16d%-12d%-16d%-12d%d\n", \
               threads[j].p_id, threads[j].arr_time, threads[j].burst_time, 
               burst_count, threads[j].turn_around_time, threads[j].waiting_time);
     }

     fprintf(stdout, "The average waiting time: %0.2f\n", (float)total_waiting_time / i);
     fprintf(stdout, "The average turn-around time: %0.2f\n", (float)total_turn_around_time / i);

     return 0;
}