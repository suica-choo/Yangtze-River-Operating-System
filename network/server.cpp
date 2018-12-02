//
// Created by zjufisher on 12/1/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

struct ThreadArgs {
    int clntSock;
};

void *ThreadMain(void *threadArgs) {
    pthread_detach(pthread_self());
    char buffer[21];
    int clntSock = ((struct ThreadArgs*) threadArgs) -> clntSock;
    int read_size;
    while ((read_size = recv(clntSock, buffer, 20, 0)) > 0) {
        int n = write(clntSock, "pong...", 8);
        if (n < 0) {
            error("error writing");
        }
    }
    if (read_size == 0) {
        close(clntSock);
    } else if (read_size == -1) {
        close(clntSock);
        error("recv failed");
    }
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        cout << "usage: ./executable port" << endl;
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    if (listen(sockfd, 20) < 0) {
        error("listen() failed");
    }
    int i = 0;
    for (;;) {
        i += 1;

        struct sockaddr_in clntAddr;
        int clntSock;
        socklen_t clntLen;
        if ((clntSock = accept(sockfd, (struct sockaddr *) &clntAddr, &clntLen)) < 0) {
            error("accept() failed");
        }
        struct ThreadArgs *threadArgs = (struct ThreadArgs*) malloc(sizeof(struct ThreadArgs));
        if (threadArgs == NULL) {
            error("malloc failed");
        }
        threadArgs->clntSock = clntSock;
        pthread_t threadID;

        int returnVal = pthread_create(&threadID, NULL, ThreadMain, threadArgs);
        if (returnVal != 0) {
            error("pthread_create() failed");
        }

    }
    return 0;
}