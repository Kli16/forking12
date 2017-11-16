#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int once(){
  printf("Before forking...\n");
  pid_t pid = fork();
  if (pid == 0){
    printf("Child PID: %d\n", pid);
    int randtime = rand()%1 + 5;
    printf("randtime: %d\n", randtime);
    sleep(randtime);
    printf("Finished!\n");
    return randtime;
  }
  else if (pid < 0){
    exit(1);
  }
  else {
    int status;
    pid_t childPID = wait(&status);
    printf("status: %x\n", status);
    int randtime = WEXITSTATUS(status);
    printf("Completed Child PID: %d\nSleep Time: %d\n", childPID,randtime);
    printf("Parent Done!\n");
  }
  return 0;
}
int main(){
  once();
  once();
  return 0;
}
