/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

sem_t running;
sem_t even;
sem_t odd;

void logStart(char *tID); //function to log that a new thread is started
void logFinish(char *tID); //function to log that a thread has finished its time

void startClock(); //function to start program clock
long getCurrentTime(); //function to check current time since clock was started
time_t programClock; //the global timer/clock for the program

typedef struct thread //represents a single thread, you can add more members if required
{
	char tid[4]; //id of the thread as read from file
	unsigned int startTime;
	int state;
	pthread_t handle;
	int retVal;
    int semaphores[2]; // added semaphore array to track even and odd activity
} Thread;

//you can add more functions here if required

int threadsLeft(Thread *threads, int threadCount);
int threadToStart(Thread *threads, int threadCount);
void* threadRun(void *t); //the thread function, the code executed by each thread
int readFile(char *fileName, Thread **threads); //function to read the file content and build array of threads

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

	//you can add some suitable code anywhere in main() if required

	Thread *threads = NULL;
	int threadCount = readFile(argv[1], &threads);

	startClock();
	while (threadsLeft(threads, threadCount) > 0) //put a suitable condition here to run your program - What does he mean???
	{
		//you can add some suitable code anywhere in this loop if required

		int i = 0;
		while ((i = threadToStart(threads, threadCount)) > -1) {
			//you can add some suitable code anywhere in this loop if required

			threads[i].state = 1;
			threads[i].retVal = pthread_create(&(threads[i].handle), NULL,
					threadRun, &threads[i]);
		}
	}
	return 0;
}

int readFile(char *fileName, Thread **threads) //do not modify this method
{
	FILE *in = fopen(fileName, "r");
	if (!in) {
		printf(
				"Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';
	while (!feof(in)) {                                 // while not at end of file 
		char line[100];
		if (fgets(line, 100, in) != NULL) {             // reads line from file 
			strncat(fileContent, line, strlen(line));   // appends line string to fileContent char-array
		}
	}
	fclose(in);

	char *command = NULL;
	int threadCount = 0;
	char *fileCopy = (char*) malloc((strlen(fileContent) + 1) * sizeof(char));
	strcpy(fileCopy, fileContent);                      // copies fileContent str in to fileCopy
	command = strtok(fileCopy, "\r\n");                 // tokenizes string for Thread IDs
	while (command != NULL) {                           // counts number of tokens in threadCount variable
		threadCount++;                                     
		command = strtok(NULL, "\r\n");
	}
	*threads = 
        (Thread*) malloc(sizeof(Thread) * threadCount); // allocates space for Thread struct array of len threadCount

	char *lines[threadCount];                           // initialize array of len threadCount for mem addresses of tokenStr
	command = NULL;                                     
	int i = 0;
	command = strtok(fileContent, "\r\n");              // get first token of fileContent str
	while (command != NULL) {                           // for each token of fileContent
		lines[i] = 
            malloc(sizeof(command) * sizeof(char));     // assign lines[i] the memory address of command token
		strcpy(lines[i], command);                      // copy token to that address 
		i++;
		command = strtok(NULL, "\r\n");                 // get next token
	}

	for (int k = 0; k < threadCount; k++) {             // then for each thread counter by threadCount 
		char *token = NULL;
		int j = 0;                                      
		token = strtok(lines[k], ";");                  // get token id 
		while (token != NULL) {
//if you have extended the Thread struct then here
//you can do initialization of those additional members
//or any other action on the Thread members

            // *TODO: extend struct with even and odd semaphore references

			(*threads)[k].state = 0;                    // ready state assignment
			if (j == 0)
				strcpy((*threads)[k].tid, token);       // thread ID assignment
			if (j == 1)
				(*threads)[k].startTime = atoi(token);  // int assignment of startTime
			j++;
			token = strtok(NULL, ";");
		}
	}
	return threadCount;
}

void logStart(char *tID) {
	printf("[%ld] New Thread with ID %s is started.\n", getCurrentTime(), tID);
}

void logFinish(char *tID) {
	printf("[%ld] Thread with ID %s is finished.\n", getCurrentTime(), tID);
}

int threadsLeft(Thread *threads, int threadCount) {
	int remainingThreads = 0;
	for (int k = 0; k < threadCount; k++) {
		if (threads[k].state > -1)
			remainingThreads++;
	}
	return remainingThreads;
}

int threadToStart(Thread *threads, int threadCount) {
	for (int k = 0; k < threadCount; k++) {
		if (threads[k].state == 0 && threads[k].startTime == getCurrentTime())
			return k;
	}
	return -1;
}

void* threadRun(void *t) //implement this function in a suitable way
{
	logStart(((Thread*) t)->tid);

//your synchronization logic will appear here

    // case 1: even semaphore is ready and odd semaphore is notReady
        // case a: even semaphore exists 
    // case 2: odd semaphore is ready and even semaphore is notReady 

    // case 3: both are ready

    // case 4: neither are ready 

	//critical section starts here
	printf("[%ld] Thread %s is in its critical section\n", getCurrentTime(),
			((Thread*) t)->tid);
	//critical section ends here

//your synchronization logic will appear here

	logFinish(((Thread*) t)->tid);
	((Thread*) t)->state = -1;
	pthread_exit(0);
}

void startClock() {
	programClock = time(NULL);
}

long getCurrentTime() //invoke this method whenever you want check how much time units passed
//since you invoked startClock()
{
	time_t now;
	now = time(NULL);
	return now - programClock;
}
