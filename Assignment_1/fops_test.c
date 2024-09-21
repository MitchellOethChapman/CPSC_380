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
#include "fops.h"
#include "libfops.a"


int main (int argc, char *argv[])
{
    char input[] = "";
    while(1)
    {

        scanf("%s", &input);
        
        break;
    }
    return 0;
}