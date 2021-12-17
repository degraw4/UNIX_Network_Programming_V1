#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <mqueue.h>

int error_sys(const char *msg)
{
    perror(msg);
    return -1;
}

ssize_t Read(int fd, void *buf, size_t size)
{
    ssize_t ret = read(fd, buf, size);
    if(ret < 0)
        error_sys("read error");
    return ret;
}

ssize_t Write(int fd, const void *buf, size_t size)
{
    ssize_t ret = write(fd, buf, size);
    if(ret < 0)
        error_sys("write error");
    return ret;
}