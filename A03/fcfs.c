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

typedef struct {
     int p_id;
     int arr_time;
     int burst_time;
     int waiting_time;
     int turn_around_time;
} THREADINFO;

int countOfLinesFromFile(char *filename) {
     FILE* myfile = fopen(filename, "r");
     int ch, number_of_lines = 0;

     do{
          ch = fgetc(myfile);
          if(ch == '\n')
               number_of_lines++;
     } while (ch != EOF);

     if(ch != '\n' && number_of_lines != 0)
          number_of_lines++;

     fclose(myfile);
     return number_of_lines;
}

int main(int argc, char *argv[]) {
     int num_lines = countOfLinesFromFile(argv[1]);                        // count number of lines in file

     THREADINFO* threads = malloc(sizeof(THREADINFO) * num_lines);  // Allocate threadinfo struct == num lines
     FILE *file = fopen(argv[1], "r");

     int i = 0;
     int j = 0;
     char *token;
     char line[1024][1024];
     int burst_count = 0;
     int total_waiting_time = 0;
     int total_turn_around_time = 0;

     while (fgets(line[i], sizeof(line), file)) {
          token = strtok(line[i], ", ");
          while (token != NULL) {
               printf("j: %d token: %s", j, token);
               if (j == 0) {
                    printf("p_id: %d ", atoi(token));
                    threads[i].p_id = atoi(token);
               } else if (j == 1) {
                    printf("arr_time: %d", atoi(token));
                    threads[i].arr_time = atoi(token);
               } else if (j == 2) {
                    printf("burst_time: %d ", atoi(token));
                    threads[i].burst_time = atoi(token);
               }
               j++;
               if (j == 3) { 
                    break;
               }
          }
          i++;
     }


     for (i = 0; i < num_lines; i++) {
          printf("%d\t\t %10d\t\t %5d\t\t %5d\t\t %10d\t\t %2d\n", \
               threads[j].p_id, threads[j].arr_time, threads[j].burst_time, 
               burst_count, threads[j].turn_around_time, threads[j].waiting_time);
     }
          

     // printf("threads ID\t Arrival Time\t\tBurst Time\t Completition Time  Turn-Around Time\t Waiting Time\n");

     // for (int j = 0; j < i; j++) {
     //      threads->p_id = threads[j].p_id;
     //      threads->arr_time = threads[j].arr_time;
     //      threads->burst_time = threads[j].burst_time;
     //      threads->waiting_time = threads[j].waiting_time;
     //      threads->turn_around_time = threads[j].turn_around_time;
     //      burst_count += threads[j].burst_time;
     //      threads[j].turn_around_time = burst_count - threads[j].arr_time;
     //      threads[j].waiting_time = threads[j].turn_around_time - threads[j].burst_time;
     //      total_waiting_time += threads[j].waiting_time;
     //      total_turn_around_time += threads[j].turn_around_time;

     //      printf("%d\t\t %10d\t\t %5d\t\t %5d\t\t %10d\t\t %2d\n", \
     //           threads[j].p_id, threads[j].arr_time, threads[j].burst_time, 
     //           burst_count, threads[j].turn_around_time, threads[j].waiting_time);
     // }

     // printf("The average waiting time: %0.2f\n", (float)total_waiting_time / i);
     // printf("The average turn-around time: %0.2f\n", (float)total_turn_around_time / i);

     return 0;
}
