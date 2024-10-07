#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include "fops.h"

int create_file(const char *filename, int flags, mode_t mode) //impements the functions using the syscall interface
{
    int fileDescriptor = syscall(SYS_open, filename, flags | O_CREAT, mode); // O_CREAT creates the file if it doesn't already exist
    if(fileDescriptor < 0) { // error checking
        perror("create failed");
        return -1;
    }
    else {
        printf("file created/opened\n");
    }
    return fileDescriptor;
}

ssize_t write_to_file(int fd, const void *buf, size_t count)
{
    ssize_t bytesWritten = syscall(SYS_write, fd, buf, count);
    if(bytesWritten < 0) { // error checking
        perror("write failed");
        return -1;
    } else {
        printf("file written to\n");
    }
    return bytesWritten;
}

ssize_t read_from_file(int fd, void *buf, size_t count)
{
    ssize_t bytesRead = syscall(SYS_read, fd, buf, count);
    if(bytesRead < 0) { // error checking
        perror("read failed");
        return -1;
    } else {
        printf("file read\n");
    }
    return bytesRead;
}

int close_file(int fd)
{
    syscall(SYS_close, fd);
    printf("file closed\n");
    return 0;
}

int delete_file(const char *filename)
{
    syscall(SYS_unlink, filename);
    printf("file deleted\n");
    return 0;
}
