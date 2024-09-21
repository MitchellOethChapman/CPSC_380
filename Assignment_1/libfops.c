#include <fops.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

int create_file(const char *filename, int flags, mode_t mode) //impements the functions using the syscall interface
{
    int fileDescriptor = syscall(SYS_open, filename, flags, mode);
    if(fileDescriptor < 0) {
        perror("open failed");
        return -1;
    }
    else {
        printf("file created\n");
    }
    close(fileDescriptor);
    return 0;
}

ssize_t write_to_file(int fd, const void *buf, size_t count)
{
    // syscall(SYS_write, ...);
    printf("file written to\n");

}

ssize_t read_from_file(int fd, void *buf, size_t count)
{
    // syscall(SYS_read, ...);
    printf("file read\n");
}

int close_file(int fd)
{
    // syscall(SYS_close, ...);
    printf("file closed\n");
}

int delete_file(const char *filename)
{
    // syscall(SYS_unlink, ...);
    printf("file deleted\n");
}
