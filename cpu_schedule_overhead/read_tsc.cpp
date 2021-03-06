//
// Created by zjufisher on 12/1/18.
//


#include <iostream>
using namespace std;

int NUM_OF_LOOPS = 100000;
static inline uint64_t rdtsc()
{
    uint32_t hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (uint64_t)lo)|( ((uint64_t)hi)<<32 );
}

double testReadTSC();
double testLoopOverhead();

int main() {
    double read_tsc_sum = 0;
    int test_times = 10;
    for (int i = 0; i < test_times; i++) {
        read_tsc_sum += testReadTSC();
    }
    cout << "==========================================" << endl;
    cout << "average test read tsc time: " << read_tsc_sum / test_times << endl;
    cout << "===========================================" << endl;
    double loop_time = 0;
    for (int i = 0; i < test_times; i++) {
        loop_time += testLoopOverhead();
    }
    cout << "===========================================" << endl;
    cout << "average test loop overhead: " << loop_time / test_times << endl;
    cout << "===========================================" << endl;

}


double testLoopOverhead() {
    uint64_t start_tsc = rdtsc();
    for (int i = 0; i < NUM_OF_LOOPS; i++) {

    }

    uint64_t end_tsc = rdtsc();
    double total_loop_times = end_tsc - start_tsc;
    double per_loop_overhead = total_loop_times / NUM_OF_LOOPS;
    cout << "loop overhead: " << per_loop_overhead << endl;
    return per_loop_overhead;
}

double testReadTSC() {
    // call rdtsc in a loop
    double total_time = 0.0;
    uint64_t start_tsc = rdtsc();
    uint64_t end_tsc = rdtsc();
    for (int i = 0; i < NUM_OF_LOOPS; i++) {
        start_tsc = rdtsc();
        end_tsc = rdtsc();
        total_time += end_tsc - start_tsc;
    }

    double per_tsc_overhead = total_time / (NUM_OF_LOOPS);
    cout << "per tsc call overhead is " << per_tsc_overhead << endl;
    return per_tsc_overhead;
}