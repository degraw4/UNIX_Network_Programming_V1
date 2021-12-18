#include "head.h"

#define MAX_FD 1024
#define MAX_LISTEN 1024
#define MAX_LINE 1024
#define SER_PORT 9080
#define SA struct sockaddr

int max(int a, int b)
{
    return a > b ? a : b;
}

void str_client(FILE* fp, int socketfd)
{
    int maxfd, stdineof;
    ssize_t n;
    fd_set rset;
    char buf[MAX_LINE];

    stdineof = 0;
    FD_ZERO(&rset);

    while(1){
        // 每次轮询之前，重置fd_set
        if(stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(socketfd, &rset);
        maxfd = max(fileno(fp), socketfd) + 1;
        select(maxfd, &rset, NULL, NULL, NULL);

        if(FD_ISSET(socketfd, &rset)){
            if((n = Read(socketfd, buf, MAX_LINE)) == 0){
                if(stdineof == 0)
                    error_sys("server terminated prematurely");
                else
                    return;
            }
            Write(fileno(stdout), buf, n);
        }

        if(FD_ISSET(fileno(fp), &rset)){
            if((n = Read(fileno(fp), buf, MAX_LINE)) == 0){
                stdineof = 1;
                shutdown(socketfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Write(socketfd, buf, n);
        }
    }
}

int main(int argc, char* argv[])
{
    
    return 0;
} 
