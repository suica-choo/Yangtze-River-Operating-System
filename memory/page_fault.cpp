//
// Created by suica on 12/5/18.
//

#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../util/util.cpp"

#define OFFSET 33554432
#define FILESIZE 6794092544

using namespace std;
void testPageFault();

int main() {
    testPageFault();
    return 0;
}

void testPageFault() {
    uint64_t start_tsc;
    uint64_t end_tsc;
    uint64_t sum = 0;

    int fd = open("temp_file.txt", O_RDWR);
    if (fd < 0) {
      cout << "File Open failed" << endl;
      exit(1);
    }
    char* map =(char*) mmap(NULL, FILESIZE*sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    char c;
    start_tsc = rdtsc();
    for (int i = 0; i < 10; i++) {
      c = map[(((i+1) * OFFSET) % (FILESIZE - 1))];
    }
    end_tsc = rdtsc();
    sum += end_tsc - start_tsc;

    cout << "total cpu cycles: " << sum / 10 << endl;
    munmap(map, FILESIZE);
    close(fd);
}
