//
// Created by suica on 12/4/18.
//

#include "../util/util.cpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>


using namespace std;

void testProcessCreation();
void testThreadCreation();
void* naive(void *);

int main() {
    testProcessCreation();
    testThreadCreation();
    return 0;
}


void testProcessCreation() {
    uint64_t start_tsc;
    uint64_t end_tsc;
    uint64_t sum;
    pid_t pid;

    for (int i = 0; i < 100000; i++) {
      start_tsc= rdtsc();
      pid = fork();

      if (pid == 0) {
        exit(0);
      }
      else {
        wait(NULL);
	end_tsc = rdtsc();
	sum += end_tsc - start_tsc;
      }
    }

    cout << sum/100000 << endl;
}

void testThreadCreation() {
    uint64_t start_tsc;
    uint64_t end_tsc;
    uint64_t sum;
    pthread_t child;

    for (int i = 0; i < 100000; i++) {
      start_tsc= rdtsc();
      pthread_create(&child, NULL, &naive, NULL);
      pthread_join(child, NULL);
      
      end_tsc = rdtsc();
      sum += end_tsc - start_tsc;
    }

    cout << sum/100000 << endl;
}

void* naive(void *) {
  pthread_exit(NULL);
}
