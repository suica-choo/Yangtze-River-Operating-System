//
// Created by zjufisher on 12/1/18.
//

#include "../util/util.cpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>


using namespace std;

// TODO: hzw, this code can't work
// measure system call getpid() overhead
// each time fork a new process to get its pid ( to avoid the cache of pid )
// what's the proper estimate overhead for the system call ?

void testGetPid();
void testSysCall();

int main() {
//    testGetPid();
    testSysCall();
    return 0;
}


void testSysCall() {
    // get thread id
    uint64_t start_tsc = rdtsc();
//    cout << gettid() << endl;
    for (int i = 0; i < 100000; i++) {
        getuid();
    }

    uint64_t end_tsc = rdtsc();
    cout << (end_tsc - start_tsc)/100000 << endl;
}


void testGetPid() {

//    cout << getpid() << endl;
//    for (int i = 0; i < 10000; i++) {
//        getpid();
//    }
//    pid_t pid = fork();
//
//    if (pid == 0) {
//        // child process
//        uint64_t start_tsc = rdtsc();
//        getpid();
//        uint64_t end_tsc = rdtsc();
//        cout << (end_tsc - start_tsc) << endl;
//    } else {
//        wait(nullptr);
//    }
    uint64_t start_tsc = rdtsc();
    getpid();
    uint64_t end_tsc = rdtsc();

    cout << end_tsc - start_tsc << endl;



}