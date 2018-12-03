//
// Created by zjufisher on 12/1/18.
//


// memcpy
// write, read

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "../util/util.cpp"

#define ARR_SIZE 8388608
using namespace std;
void testMemBandCopy();

int main() {
    testMemBandCopy();
}




void testMemBandCopy() {
//    int src1[ARR_SIZE];
//    int src2[ARR_SIZE];
//    int dest[ARR_SIZE];
    int* src1 = new int[ARR_SIZE];
    int* src2 = new int[ARR_SIZE];
    int* dest = new int[ARR_SIZE];

    fill(src1, src1 + ARR_SIZE, 0);
    fill(src2, src2 + ARR_SIZE, 0);
    fill(dest, dest + ARR_SIZE, 0);

    uint64_t start_tsc;
    uint64_t end_tsc;

    double total_cycle = 0;

    for (int i = 0; i < 32768; i++) {
        memcpy(dest, src1, ARR_SIZE);
        start_tsc = rdtsc();
        memcpy(dest, src2, ARR_SIZE);
        end_tsc = rdtsc();
        total_cycle += end_tsc - start_tsc;
    }

    // total memory: 32K * 32M = 1024G
    double cycle_time = 1/(2.3*1000000000);
    double mem_total = 1024; // 1024G
    cout << "total cpu cycles: " << total << endl;
    cout << "total time = " << mem_total / (total_cycle*cycle_time) << "G/s" << endl;
    delete[] src1;
    delete[] src2;
    delete[] dest;
}



void testMemBandWrite() {


}


void testMemBandRead() {


}

