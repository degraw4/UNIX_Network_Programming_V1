#include "head.h"

#define MAX_FD 1024
#define MAX_LISTEN 1024
#define MAX_LINE 1024
#define SER_PORT 9080
#define SA struct sockaddr

// select的本质还是polling轮询，属于同步IO， 因此要是要时刻查询select的结果

int main(int argc, char* argv[])
{
    int i, maxi, maxfd, listenfd, connfd, socketfd;
    int nready, client[MAX_FD];
    char buf[MAX_LINE];
    socklen_t clilen;
    ssize_t n;
    fd_set rset, allset;
    struct sockaddr_in clientaddr, serveraddr;

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);     // INADDR_ANY为数值，因此要用addr.sin_addr.s_addr
    serveraddr.sin_port = htonl(SER_PORT);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (SA * )&serveraddr, sizeof(serveraddr));
    listen(listenfd, MAX_LISTEN);

    maxi = -1;
    maxfd = listenfd;

    for(i = 0; i < MAX_FD; ++i)
        client[i] = -1;
    
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1){
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(listenfd, &rset)){
            clilen = sizeof(clientaddr);
            connfd = accept(listenfd, (SA *)&clientaddr, &clilen);

            for(i = 0; i < MAX_FD; ++i)
                if(client[i] != -1){
                   client[i] = connfd;
                    break; 
                }
            if(i == MAX_FD)
                error_sys("too many client");

            FD_SET(connfd, &allset);

            if(maxfd < connfd)
                maxfd = connfd;

            if(i > maxi)
                maxi = i;
            
            if(--nready <= 0)
                continue;
        }

        for(i = 0; i < maxi; ++i){
            if((socketfd = client[i]) == -1)
                continue;
            if(FD_ISSET(socketfd, &rset)){
                if((n = Read(connfd, buf, MAX_LINE)) == 0){
                    close(socketfd);
                    FD_CLR(socketfd, &allset);
                    client[i] = -1;
                }
                else
                    Write(socketfd, buf, n);
                if(--nready <= 0)
                    break;
            }
        }
    }

    return 0;
}
