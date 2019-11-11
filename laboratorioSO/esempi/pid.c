/**
 * visualizza il proprio PID
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = getpid();
    printf("PID che il kernel ha associato a questo processo: %d\n", pid);
}
