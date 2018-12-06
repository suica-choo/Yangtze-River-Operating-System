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
void testMemBandRead();
int main() {
    testMemBandCopy();
    testMemBandWrite();
    testMemBandRead();
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

    for (int i = 0; i < 128; i++) {
        memcpy(dest, src1, ARR_SIZE);
        start_tsc = rdtsc();
        memcpy(dest, src2, ARR_SIZE);
        end_tsc = rdtsc();
        total_cycle += end_tsc - start_tsc;
    }

    // total memory: 32K * 32M = 1024G
    double cycle_time = 1/(2.3*1000000000);
    double mem_total = 4; // 4G
    cout << "total cpu cycles: " << total_cycle << endl;
    cout << "memcpy bandwidth = " << mem_total / (total_cycle*cycle_time) << "G/s" << endl;
    delete[] src1;
    delete[] src2;
    delete[] dest;
}



void testMemBandWrite() {
    int* src = new int[1024*1024];
    fill(src, src+1024, 0);
    int a;
    #define wt(i,j) src[i*1024+j] = 0;
    uint64_t start_tsc = rdtsc();
    int pos;
    for (int i = 0; i < 1024*1024; i++) {
        pos = i % 1024;
        wt(pos,0) wt(pos,16) wt(pos,32) wt(pos,48) wt(pos,64) wt(pos,80) wt(pos,96) wt(pos,112) wt(pos,128)
        wt(pos,144) wt(pos,160) wt(pos,176) wt(pos,192) wt(pos,208) wt(pos,224) wt(pos,240) wt(pos,256) wt(pos,272)
        wt(pos,288) wt(pos,304) wt(pos,320) wt(pos,336) wt(pos,352) wt(pos,368) wt(pos,384) wt(pos,400) wt(pos,416)
        wt(pos,432) wt(pos,448) wt(pos,464) wt(pos,480) wt(pos,496) wt(pos,512) wt(pos,528) wt(pos,544) wt(pos,560) wt(pos,576)
        wt(pos,592) wt(pos,608) wt(pos,624) wt(pos,640) wt(pos,656) wt(pos,672) wt(pos,688) wt(pos,704) wt(pos,720) wt(pos,736)
        wt(pos,752) wt(pos,768) wt(pos,784) wt(pos,800) wt(pos,816) wt(pos,832) wt(pos,848) wt(pos,864) wt(pos,880) wt(pos,896)
        wt(pos,912) wt(pos,928) wt(pos,944) wt(pos,960) wt(pos,976) wt(pos,992) wt(pos,1008)
    }
    uint64_t end_tsc = rdtsc();
    uint64_t total_cycle = end_tsc - start_tsc;
    // total_cycle -= 1024*1024*8;
    double cycle_time = 1/(2.3*1000000000);
    double mem_total = 4; // 4G
    cout << "total cpu cycles: " << total_cycle << endl;
    cout << "write bandwidth = " << mem_total / (total_cycle*cycle_time) << "G/s" << endl;
    delete[] src;

}


void testMemBandRead() {
    int* src = new int[1024*1024];
    fill(src, src+1024, 0);
    int a;
    #define rd(i,j) a = src[i*1024+j];
    uint64_t start_tsc = rdtsc();
    int pos;
    for (int i = 0; i < 1024*1024; i++) {
        pos = i % 1024;
        rd(pos,0) rd(pos,16) rd(pos,32) rd(pos,48) rd(pos,64) rd(pos,80) rd(pos,96) rd(pos,112) rd(pos,128)
        rd(pos,144) rd(pos,160) rd(pos,176) rd(pos,192) rd(pos,208) rd(pos,224) rd(pos,240) rd(pos,256) rd(pos,272)
        rd(pos,288) rd(pos,304) rd(pos,320) rd(pos,336) rd(pos,352) rd(pos,368) rd(pos,384) rd(pos,400) rd(pos,416)
        rd(pos,432) rd(pos,448) rd(pos,464) rd(pos,480) rd(pos,496) rd(pos,512) rd(pos,528) rd(pos,544) rd(pos,560) rd(pos,576)
        rd(pos,592) rd(pos,608) rd(pos,624) rd(pos,640) rd(pos,656) rd(pos,672) rd(pos,688) rd(pos,704) rd(pos,720) rd(pos,736)
        rd(pos,752) rd(pos,768) rd(pos,784) rd(pos,800) rd(pos,816) rd(pos,832) rd(pos,848) rd(pos,864) rd(pos,880) rd(pos,896)
        rd(pos,912) rd(pos,928) rd(pos,944) rd(pos,960) rd(pos,976) rd(pos,992) rd(pos,1008)
    }
    uint64_t end_tsc = rdtsc();
    uint64_t total_cycle = end_tsc - start_tsc;
    // total_cycle -= 1024*1024*8;
    double cycle_time = 1/(2.3*1000000000);
    double mem_total = 4; // 4G
    cout << "total cpu cycles: " << total_cycle << endl;
    cout << "read bandwidth = " << mem_total / (total_cycle*cycle_time) << "G/s" << endl;
    delete[] src;

}

