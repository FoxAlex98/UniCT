#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int n = 0;
  int pid = fork();
  if (pid == 0) {
    n++;
    printf("tuo padre\n");
    printf("n=%d\n", n);
  } else {
    n++;
    printf("tuo figlio, pid = %d \n", pid);
    printf("n=%d\n", n);
  }
  return 0;
}
