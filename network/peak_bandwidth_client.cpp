//
// Created by 黄兆维 on 2018-12-02.
//

#include "../util/util.cpp"
#include "client.cpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
#define BUFFER_SIZE 1024*1024*2 // 2MB

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr,"ERROR, no port provided\n");
        cout << "usage: ./executable server_address portno" << endl;
        exit(1);
    }
    int portno = atoi(argv[2]);
    char* host_name = argv[1];
    int sock_fd = buildConnection(portno, host_name);
    char* buffer = new char[BUFFER_SIZE];
    fill(buffer, buffer+BUFFER_SIZE, 'a');
    int n;
    uint64_t start_tsc;
    uint64_t end_tsc;
    uint64_t send_time = 0;
    uint64_t recv_time = 0;

    for (int i = 0; i < 1024; i++) {
        // 2MB * 1024 = 2GB
        start_tsc = rdtsc();
        n = write(sock_fd, buffer, BUFFER_SIZE);
        end_tsc = rdtsc();
        send_time += end_tsc - start_tsc;
        if (n < 0) {
            error("ERROR writing socket");
        }
        start_tsc = rdtsc();
        n = read(sock_fd, buffer, BUFFER_SIZE);
        end_tsc = rdtsc();
        recv_time += end_tsc - start_tsc;
        if (n < 0) {
            error("ERROR reading from socket");
        }
    }

    // total receive 2GB and send 2GB
    cout << "send time is : " << send_time << " cycles" << endl;
    cout << "recv time is : " << recv_time << " cycles" << endl;
}