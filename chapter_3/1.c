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
#include "error.h"

int main(int argc, char* argv[])
{
    struct sockaddr_in addr;
    addr.sin_family;        // uint8_t
    addr.sin_addr;          // uint16_t
    addr.sin_port;          // uint32_t构成的struct
    addr.sin_addr.s_addr;   // uint32_t

    // sockaddr_in转为通用套接字地址sockaddr
    struct sockaddr *SA = (struct sockaddr *)&addr;

    struct sockaddr_in6 addr6;
    addr6.sin6_family;      // uint8_t
    addr6.sin6_addr;        // uint16_t
    addr6.sin6_port;        // uint8_t[16]数组构成的struct
    addr6.sin6_addr.__in6_u;

    // 新的通用套接字地址结构
    struct sockaddr_storage *SAS = (struct sockaddr_storage *)&addr6; 

    char ad1[32] = "192.168.1.1";
    char ad2[32] = "";
    inet_pton(AF_INET, ad1, &addr.sin_addr);
    inet_ntop(AF_INET,  &addr.sin_addr, ad2, sizeof(ad2));
    printf("address is %s\n", ad2);
    
    

    return 0;
}
