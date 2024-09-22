/*
Create a main program that uses the static library to perform file operations. The program
should accept command-line arguments to specify the operation and the file name. The
supported operations include:
    create <filename>: Create a new file.
    write <filename> <data>: Write data to the file.
    read <filename>: Read data from the file.
    close <filename>: Close the file
    delete <filename>: Delete the file.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#include "fops.h"
#include "libfops.a"

int main (int argc, char *argv[])
{
    int action; // stores the action the use would like to take
    char filename[100]; // stores the command line input
    int flags;
    mode_t mode = 0644;
    int fd;
    int running = 1;

    while(running == 1)
    {
        printf("What would you like to do?\n");
        printf("Type the corresponding number to initiate a command:\n");
        printf("1. Create a new file or open an existing file.\n");
        printf("2. Write to a file.\n");
        printf("3. Read a file.\n");
        printf("4. Close a file.\n");
        printf("5. Delete a file.\n");
        printf("6. Quit\n");

        if (scanf("%i", &action) != 1) {
            printf("You didn't enter an integer.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
        
        switch (action) {
            case 1: // create or open a file
                printf("What is the name of the file?\n");
                scanf("%s", filename);
                flags = O_WRONLY | O_CREAT | O_TRUNC;
                fd = create_file(filename, flags, mode);
                if(fd < 0) { // error checking
                    perror("open failed");
                    return -1;
                }
                break;
            case 2: // write to a file
                printf("What is the name of the file?\n");
                scanf("%s", filename);
                flags = O_WRONLY;
                fd = create_file(filename, flags, mode);
                if(fd < 0) { // error checking
                    perror("open failed");
                    return -1;
                }
                printf("What would you like to write to the file?\n");
                char writeData[100];
                scanf("%s", writeData);
                ssize_t bytesWritten = write_to_file(fd, writeData, strlen(writeData));
                if(bytesWritten < 0) { // error checking
                    perror("write failed");
                    close_file(fd);
                    return -1;
                } else {
                    printf("Bytes written to %s: %zd\n", filename, bytesWritten);
                }
                close_file(fd);
                break;
            case 3: // read a file
                printf("What is the name of the file?\n");
                scanf("%s", filename);
                flags = O_RDONLY;
                fd = create_file(filename, flags, mode);
                if(fd < 0) { // error checking
                    perror("open failed");
                    return -1;
                }
                char fileContents[100];
                ssize_t bytesRead = read_from_file(fd, fileContents, sizeof(fileContents) - 1);
                if(bytesRead < 0) { // error checking
                    perror("read failed");
                    close_file(fd);
                    return -1;
                }
                fileContents[bytesRead] = '\0'; // Null terminate fileContents
                printf("file contents: %s\n", fileContents);
                close_file(fd);
                break;
            case 4: // close a file
                printf("What is the name of the file?\n");
                scanf("%s", filename);
                flags = O_WRONLY | O_CREAT | O_TRUNC;
                fd = create_file(filename, flags, mode);
                if(fd < 0) { // error checking
                    perror("open failed");
                    return -1;
                }
                close_file(fd);
                break;
            case 5:
                printf("What is the name of the file?\n");
                scanf("%s", filename);
                delete_file(filename);
                break;
            case 6:
                running = 0;
                printf("Goodbye\n");
                break;
        }
    }
    return 0;
}
