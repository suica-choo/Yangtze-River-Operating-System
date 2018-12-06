//
// Created by zjufisher on 12/1/18.
//


// memcpy
// write, read

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "../util/util.cpp"

#define ARR_SIZE 8388608 // 8M


using namespace std;
void testMemBandCopy();
void testMemBandWrite();

int main() {
    testMemBandCopy();
    testMemBandWrite();
}




void testMemBandCopy() {
//    int src1[ARR_SIZE];
//    int src2[ARR_SIZE];
//    int dest[ARR_SIZE];
    int* src1 = new int[ARR_SIZE]; // 32MB
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
    cout << "total cpu cycles: " << total_cycle << endl;
    cout << "total time = " << mem_total / (total_cycle*cycle_time) << "G/s" << endl;
    delete[] src1;
    delete[] src2;
    delete[] dest;
}



void testMemBandWrite() {
    int stride = ARR_SIZE / 8; 
    int* src = new int[ARR_SIZE];
    fill(src, src + ARR_SIZE, 0);
    int pos = 0;
    uint64_t start_tsc = rdtsc();
    double total_tsc = 0;
    uint64_t end_tsc = rdtsc();
    for (int i = 0; i < 1024*1024; i++) {
        start_tsc = rdtsc();
        src[0] = 0;
        src[16] = 0;
        src[32] = 0;
        src[48] = 0;
        src[64] = 0;
        src[80] = 0;
        src[96] = 0;
        src[112] = 0;
        end_tsc = rdtsc();
        // 64B * 8 = 512B
        total_tsc += end_tsc - start_tsc;
        for (int j = 0; j < 1000; j++) {
            src[j+1024] = 0;
        }


    }
    
    // assume 4M cache 
    // 16M * 128 = 2G

    double cycle_time = 1 / (2.3*1000000000);
    double mem_total = 0.5;
    cout << "bandwidth write: " << mem_total / (total_tsc*cycle_time) << "G/s" << endl;
    delete[] src;

}


void testMemBandRead() {


}

