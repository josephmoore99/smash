#include <stdio.h>
#include <stdlib.h>  //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#include <unistd.h>  //Directory functions
#include <sys/types.h>
#include <sys/wait.h>

#include "smash.h"
#include "history.h"

char *args[11];
char *copy;
int cmdCount = 0;

void executeCommand(char *str) {

  copy = strndup(str, 100);
  char *parser;
  int i = 0;
  cmdCount++;

  parser = strtok(str, " ");

  while(parser != NULL) {
    if(i<10) {
      args[i] = parser;
      i++;
      args[i] = NULL;
    }
    parser = strtok(NULL, " ");
  }

  if(args[0] == NULL) {
    //Ignore
  } else if(strcmp(args[0],"exit")==0) { //implementation of the exit command
    clear_history();
    exit(0);
  } else if(strcmp(args[0],"cd")==0) { //implementation of cd command
    int err = 0;
    if(args[1]!=NULL) {
      err = chdir(args[1]);
      if(err == -1) {
        fputs(args[1],stderr);
        fputs(": No such file or directory\n",stderr);
        err = 1;
      } else if(err != 0) {
        //do nothing
      } else {
        fputs(args[1], stderr);
        fputs("\n",stderr);
      }
    }
    add_history(copy, err);

  } else if(strcmp(args[0],"history")==0){ //history command
    add_history(copy,0);
    if(cmdCount<10) {
      print_history(1);
    } else {
      print_history(cmdCount-9);
    }
  } else { //invalid command
    executeExternalCommand(copy);

    // for(int j = 0; j < argCount; j++) {
    //   fprintf(stderr,"[%d] %s\n", j, args[j]);
    // }
    // add_history(copy,127);
  }
}

void executeExternalCommand(char *exStr) {
  int pid = fork();
  if(pid==0) {
    int err = execvp(args[0],args);
    if(err!=0) {
      printf("smash: %s: command not found\n",copy);
      exit(127);
    }
  } else if(pid>0){
    int exitResult;
    wait(&exitResult);
    add_history(copy,WEXITSTATUS(exitResult));
  } else {
    fputs("Something went terribly wrong", stderr);
    exit(-1);
  }
}
