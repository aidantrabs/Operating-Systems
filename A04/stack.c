/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 10

typedef struct Node {
     int data;
     struct Node *next;
} StackNode;

StackNode *top;

// Prototypes
void push(int v, StackNode **top);
int pop(StackNode **top);
int is_empty(StackNode *top);
pthread_mutex_t lock;

void push(int v, StackNode **top) {
    StackNode *new_node;
    printf("Thread is running Push() operation for value: %d\n", v);
    new_node = (StackNode *) malloc(sizeof(StackNode));
    new_node->data = v;
    new_node->next = *top;
    *top = new_node;     
}

int pop(StackNode **top) {
	StackNode *temp;
    if (is_empty(*top)) {
          printf("Stack empty \n");
          return 0;
	} else {
          int data = (*top)->data;
          printf("Thread is running Pop() operation and value is: %d\n",data);
          temp = *top;
          *top = (*top)->next;
          free(temp);
          return data;
    }
}

int is_empty(StackNode *top) {
     if (top == NULL) {
          return 1;
     } else {
          return 0;
     }
}

void* thread_push(void *args) {
     pthread_mutex_trylock(&lock);
     int i;
     int *threadId = (int *) args;
     push(*threadId + 1, &top);
     pthread_mutex_unlock(&lock);

     return NULL;
}

void* thread_pop() {
     pthread_mutex_trylock(&lock);
     pop(&top);
     pthread_mutex_unlock(&lock);

     return NULL;
}

int main(void) {
    StackNode *top = NULL;
    pthread_t threads_push[NUM_THREADS];
    pthread_t threads_pop[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i, j;

     for(i = 0; i < NUM_THREADS; i++) { 
	     thread_args[i] = i;
	     pthread_create(&threads_push[i],NULL,thread_push, (void *)&thread_args[i]);
	}

	for(i = 0; i < NUM_THREADS; i++){
          thread_args[i] = i;
	     pthread_create(&threads_pop[i],NULL,thread_pop, NULL);
	}

	for(j = 0; j < NUM_THREADS; j++) {
          pthread_join(threads_push[j], NULL);
     }

	for(j = 0; j < NUM_THREADS; j++) {
	     pthread_join(threads_pop[j],NULL);
	}

     pthread_exit(NULL);
     return 0;
}