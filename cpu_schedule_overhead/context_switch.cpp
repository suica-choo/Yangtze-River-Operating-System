//
// Created by suica on 12/4/18.
//

#include "../util/util.cpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

void testProcessContextSwitch();
void testThreadContextSwitch();
void* naive(void *);
int tpfd[2];

int main() {
    testProcessContextSwitch();
    testThreadContextSwitch();
    return 0;
}


void testProcessContextSwitch() {
    uint64_t start_tsc;
    uint64_t end_tsc;
    uint64_t sum = 0;
    pid_t pid;
    int pfd[2];

    if (pipe(pfd) == -1) { perror("pipe"); exit(1); }

    int i = 0;
    while (i < 100000) {
      pid = fork();

      if (pid == -1) { perror("fork"); exit(1); }

      if (pid == 0) {
        end_tsc = rdtsc();
        write(pfd[1], (void*)&end_tsc, sizeof(uint64_t));
        exit(0);
      }
      else {
        start_tsc = rdtsc();
        wait(NULL);
	read(pfd[0], (void*)&end_tsc, sizeof(uint64_t));

        // in case child process executes before the parent process
	if (end_tsc > start_tsc) {
	  sum += end_tsc - start_tsc;
	  i++;
	}
      }
    }

    cout << sum/100000 << endl;
}

void testThreadContextSwitch() {
    uint64_t start_tsc;
    uint64_t end_tsc;
    uint64_t sum = 0;
    pthread_t child;

    if (pipe(tpfd) == -1) { perror("pipe"); exit(1); }

    int i = 0;
    while (i < 100000) {
      pthread_create(&child, NULL, &naive, NULL);
      start_tsc= rdtsc();
      pthread_join(child, NULL);
      
      read(tpfd[0], (void*)&end_tsc, sizeof(uint64_t));
      if (end_tsc > start_tsc) {
        sum += end_tsc - start_tsc;
	i++;
      }
    }

    cout << sum/100000 << endl;
}

void* naive(void *) {
  uint64_t tsc = rdtsc();
  write(tpfd[1], (void*)&tsc, sizeof(uint64_t));
  pthread_exit(NULL);
}
