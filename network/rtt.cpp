//
// Created by zjufisher on 12/1/18.
//

#include "../util/util.cpp"
#include "client.cpp"
#include <iostream>

#define NUM_RTT_TIMES 100000
using namespace std;

void rtt(int portno, char* host_name);
int main() {
    rtt(10086, "127.0.0.1");
}

void rtt(int portno, char* host_name) {
    // send the ping pong messages
    int socket_fd = buildConnection(portno, host_name);
    char send_buffer[10] = "ping..";
    char rec_buffer[10];
    int n;
    double total = 0;
    uint64_t start_tsc = rdtsc();
    uint64_t end_tsc = rdtsc();
    for (int i = 0; i < NUM_RTT_TIMES; i++) {
        start_tsc = rdtsc();
        n = write(socket_fd, send_buffer, strlen(send_buffer));
        if (n < 0) {
            error("ERROR in writing to socket");
        }
        n = read(socket_fd, rec_buffer, 10);
        if (n < 0) {
            error("ERROR reading from socket");
        }
        end_tsc = rdtsc();
        total += end_tsc - start_tsc;
    }

    double rtt_time = total / NUM_RTT_TIMES;
    cout << "rtt time: " << rtt_time << endl;

}