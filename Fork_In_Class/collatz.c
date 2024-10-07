#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int n = atoi(argv[1]);

    pid = fork();
    if(pid < 0) {
        perror("fork failed");
        return -1;
    }
    else if (pid == 0) {
        while (n != 1) {
            if ((n % 2) == 0) {
                n = n / 2;
            }
            else {
                n = (3 * n) + 1;
            }
            printf("%d, ",n);
        }
    }
    else {
        wait(NULL);
    }
}