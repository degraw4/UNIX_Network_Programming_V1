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

// waitpid(-1, NULL, WNOHANG)的返回值
// 此时有子进程终止，返回其pid
// 此时有子进程，但未终止，返回0
// 此时无子进程，返回-1

void handler(int sig){
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0){
        printf("child get\n");
    }
    printf("pid is %d\n", pid);
    return;
}

int main(int argc, char* argv[])
{
    signal(SIGCHLD, handler);
    if(fork() == 0){
        sleep(3);
        exit(0);
    }
    // if(fork() == 0){
    //     sleep(5);
    //     exit(0);
    // }
    while(1);

    return 0;
}
