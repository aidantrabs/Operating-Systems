/**
--------------------------------------
Author: Aidan Traboulay
ID: 200115590
Email: trab5590@mylaurier.ca
--------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

     /* Declare variables */
     int filedir_src, filedir_des, line;
     char buf[BUFSIZ];

     /* Output error if user does not pass parameters */
     if (argc != 3) {
          fprintf(stdout, "Insufficient parameters passed.\n");
          exit(1);
     }

     /* Output error if file source can not be read from or does not exist */
     if ((filedir_src = open(argv[1], O_RDONLY)) == -1) {
          perror(argv[1]);
          exit(2);
     }

     /* Output error if file destination is not created or replaced */
     if ((filedir_des = creat(argv[2], 0644)) == -1) {
          perror(argv[2]);
          exit(3);
     }

     /* Loop through source file directory, copy and write to destination file directory */
     while ((line = read(filedir_src, buf, BUFSIZ)) > 0) {
          if (write(filedir_des, buf, line) != line) {
               perror(argv[2]);
               exit(4);
          } else { 
               fprintf(stdout, "The contents of file %s have been successfully copied into the %s file.\n", argv[1], argv[2]);
          }
     }

     /* Close both file directories */
     close(filedir_src);
     close(filedir_des);

     return 0;
}
