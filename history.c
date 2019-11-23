#include <stdio.h>
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions

#include "history.h"

struct Cmd *ptr[MAXHISTORY];
int head;
//Function prototypes for the command history feature
void init_history(void) {
  for(int i = 0; i < MAXHISTORY; i++) {
    ptr[i] = (struct Cmd *)malloc(sizeof(struct Cmd));
  }
  head = 0;
} //Builds data structures for recording cmd history
void add_history(char *cmd, int exitStatus) {
    ptr[head]->cmd = cmd;
    ptr[head]->exitStatus = exitStatus;

    head++;
    if(head>=10) {
      head = 0;
    }
} //Adds an entry to the history
void clear_history(void){
  for(int i = 0; i < MAXHISTORY; i++) {
    free(ptr[i]);
  }
} //Frees all malloc’d memory in the history
void print_history(int firstSequenceNumber){
  if(firstSequenceNumber==1) { // if history contains 10 or less elements
    if(head == 0) {
      head = 10;
    }
    for(int i = 0; i < head; i++) {
      printf("%d [%d] %s\n",firstSequenceNumber+i, ptr[i]->exitStatus, ptr[i]->cmd);
    }
    if(head == 10) {
      head = 0;
    }
  } else if(firstSequenceNumber>1) { // if history contains more than 10 elements
    int j = 0;
    int i = head;

    do {
      printf("%d [%d] %s\n",firstSequenceNumber + j, ptr[i]->exitStatus, ptr[i]->cmd);
      j++;
      if(i == 9) {
        i = 0;
      } else {
        i++;
      }
    } while(i != head);
  }
} //Prints the history to stdout
