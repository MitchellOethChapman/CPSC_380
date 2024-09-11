#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>

int main()
{
    char *msg = "Hello World!\n";

syscall(SYS_write, STDOUT_FILENO, msg, strlen(msg) )
return 0;

}