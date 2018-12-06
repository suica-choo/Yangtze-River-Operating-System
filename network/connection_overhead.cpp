//
// Created by zjufisher on 12/1/18.
//

#include "../util/util.cpp"
#include "client.cpp"
#include <iostream>

/*
 *  Create socket connection
    Send data
    Tear down socket connection
    Step 1: Requires an exchange of packets,
    so it's delayed by to & from network latency plus the destination server's service time.
    No significant CPU usage on either box is involved.

    Step 2: Depends on the size of the message.

    Step 3: IIRC, just sends a 'closing now' packet, w/ no wait for destination ack, so no latency involved.
 */

#define NUM_RTT_TIMES 10000
using namespace std;

void connection_test(int portno, char* host_name);
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr,"ERROR, no port provided\n");
        cout << "usage: ./executable server_address portno" << endl;
        exit(1);
    }
    int portno = atoi(argv[2]);
    char* host_name = argv[1];
    connection_test(portno, host_name);
}

void connection_test(int portno, char* host_name) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(host_name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    double set_up_time = 0;
    double tear_down_time = 0;
    uint64_t start_tsc;
    uint64_t end_tsc;

    for (int i = 0; i < NUM_RTT_TIMES; i++) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        start_tsc = rdtsc();
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        end_tsc = rdtsc();
        set_up_time += (end_tsc - start_tsc);
        start_tsc = end_tsc;
        if (close(sockfd) < 0) {
            error("ERROR in tearing down connection");
        }
        end_tsc = rdtsc();
        tear_down_time += (end_tsc - start_tsc);
    }

    cout << "average set up time: " << set_up_time / NUM_RTT_TIMES << endl;
    cout << "average tear down time: " << tear_down_time / NUM_RTT_TIMES << endl;
}