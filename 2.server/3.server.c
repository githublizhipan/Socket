/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月22日 星期日 20时04分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

struct FD {
    int sock_cfd;
};

void *func(void *p) {
    int sockfd = ((struct FD *)p)->sock_cfd;
    char name[20] = {0};
    if(recv(sockfd, name, sizeof(name), 0) <= 0) {
        perror("recv");
        close(sockfd);
    }
    printf("Name = %s\n", name);
    pthread_exit(0);
}


int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }
    int port, server_listen;
    port = atoi(argv[1]);

    if((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    printf("Socket Create.\n");
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;
    
    printf("Socket bind.\n");
    if(bind(server_listen, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }

    if(listen(server_listen, 20) < 0) {
        perror("server");
        exit(1);
    }
    
    while(1) {
        int sockfd;
        if((sockfd = accept(server_listen, NULL, NULL)) < 0) {
            perror("accept");
            close(sockfd);
            continue;
        }
        
        struct FD fd;
        fd.sock_cfd = sockfd;
        
        pthread_t tid;
        int err = (pthread_create(&tid, NULL, func, &fd));
        if(err) {
            close(server_listen);
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
        pthread_join(tid, NULL);
    }
    return 0;
}
