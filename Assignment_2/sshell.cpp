#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

int main()
{
    char *args[(MAX_LINE/2) + 1]; // command line arguments
    int should_run = 1; // flag to determine when to exit program

    while (should_run) {
        printf("osh>");
        fflush(stdout);

        // Allocate memory for the command line arguments
        args[0] = (char *)malloc(MAX_LINE * sizeof(char));
        if (args[0] == NULL) {
            perror("Unable to allocate memory");
            return 1;
        }

        // Handle if args is empty first

        fgets(*args, sizeof(args), stdin); // read the command line arguments to args[0]
        // printf("%s", args[0]);
        args[0][strcspn(args[0], "\n")] = 0; // removing newline character from end of the user input

        char *token = strtok(args[0], " "); // using " " to split up the arguments
        int num_args = 0; // counting the number of arguments
        for (int i = 0; i < (MAX_LINE / 2) && token!=NULL; i++) {
            args[i] = token;
            token = strtok(NULL, " ");
            num_args++;
        }

        // Checking whether the parent should wait for the child to finish
        int should_wait = 1;
        if (strcmp(args[num_args - 1], "&") == 0) {
            should_wait = 0;
            printf("will wait\n");
        }
        // end of user input

        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */

        pid_t pid;
        pid = fork();
        if(pid < 0) {
            perror("fork failed");
            return -1;
        } else if (pid == 0) {
            // child process
            int user_function = execvp(args[0], args);
            if (user_function < 0) {
                perror("execvp failed");
            }
            should_run = 0;
        } else {
            // parent process
            if (should_wait) {
                int child_time;
                pid_t child = wait(&child_time);
            }

            //handling exit manually because strcmp isn't working
            if (args[0][0] == 'e' && args[0][1] == 'x' && args[0][2] == 'i' && args[0][3] == 't' && strlen(args[0]) == 5) {
                should_run = 0;
                printf("Exiting shell\n");
            }
        }
    }
    return 0;
}
