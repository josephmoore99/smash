#include <stdio.h>
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions

#include "smash.h"
#include "history.h"

#define MAXLINE 4096

int main(void) {
  setvbuf(stdout,NULL,_IONBF,0); //Disable buffering in the stdout stream
  setvbuf(stderr,NULL,_IONBF,0); //Disable buffering in the stderr stream

  char bfr[4096];
  fputs("$ ",stderr); //Output the first prompt
  //Loop reading commands until EOF or error
  init_history();
  while (fgets(bfr, MAXLINE, stdin) != NULL) {
    if(strlen(bfr) > 1) {
      bfr[strlen(bfr) - 1] = '\0'; //Replace newline with NUL
      executeCommand(bfr); //Calls on executeCommand to interpret/execute command
    }
    fputs("$ ",stderr);
  }
  return 0;
}
