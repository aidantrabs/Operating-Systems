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

struct threadInfo {
     int p_id;
     int arr_time;
     int burst_time;
     int waiting_time;
     int turn_around_time;
};

int main(int argc, char *argv[]) {
     struct threadInfo *thread = malloc(sizeof(struct threadInfo) * 3);
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
               if (j == 0) {
                    thread[i].p_id = atoi(token);
               } else if (j == 1) {
                    thread[i].arr_time = atoi(token);
               } else if (j == 2) {
                    thread[i].burst_time = atoi(token);
               }
               token = strtok(NULL, ", ");
               j++;
          }
          i++;
     }

     printf("Thread ID\t Arrival Time\t\tBurst Time\t Completition Time  Turn-Around Time\t Waiting Time\n");

     for (int j = 0; j < i; j++) {
          thread->p_id = thread[j].p_id;
          thread->arr_time = thread[j].arr_time;
          thread->burst_time = thread[j].burst_time;
          thread->waiting_time = thread[j].waiting_time;
          thread->turn_around_time = thread[j].turn_around_time;
          burst_count += thread[j].burst_time;
          thread[j].turn_around_time = burst_count - thread[j].arr_time;
          thread[j].waiting_time = thread[j].turn_around_time - thread[j].burst_time;
          total_waiting_time += thread[j].waiting_time;
          total_turn_around_time += thread[j].turn_around_time;

          printf("%d\t\t %10d\t\t %5d\t\t %5d\t\t %10d\t\t %2d\n", \
               thread[j].p_id, thread[j].arr_time, thread[j].burst_time, 
               burst_count, thread[j].turn_around_time, thread[j].waiting_time);
     }

     printf("The average waiting time: %0.2f\n", (float)total_waiting_time / i);
     printf("The average turn-around time: %0.2f\n", (float)total_turn_around_time / i);

     return 0;
}
