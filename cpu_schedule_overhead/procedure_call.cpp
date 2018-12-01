//
// Created by zjufisher on 12/1/18.
//



#include "../util/util.cpp"
#include <iostream>
using namespace std;

void proc_test0() {
}

void proc_test1(int a) {

}

void proc_test2(int a, int b) {

}

void proc_test3(int a, int b, int c) {

}

void proc_test4(int a, int b, int c, int d) {

}

void proc_test5(int a, int b, int c, int d, int e) {

}

void proc_test6(int a, int b, int c, int d, int e, int f) {

}

void proc_test7(int a, int b, int c, int d, int e, int f, int g) {

}
int NUM_TEST_CALLS = 100000;

int main() {
//    cout << rdtsc() << endl;
    uint64_t cur_time_sum = 0;
    uint64_t start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test0();
    }
    uint64_t end_tsc = rdtsc();
    cout << "======================================" << endl;
    cout << "0 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;


    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test1(1);
    }
    end_tsc = rdtsc();
    cout << "======================================" << endl;
    cout << "1 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test2(1,1);
    }
    end_tsc = rdtsc();
    cout << "======================================" << endl;
    cout << "2 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test3(1,1,1);
    }
    end_tsc = rdtsc();
    cout << "======================================" << endl;
    cout << "3 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test4(1,1,1,1);
    }
    end_tsc = rdtsc();

    cout << "======================================" << endl;
    cout << "4 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test5(1,1,1,1,1);
    }
    end_tsc = rdtsc();

    cout << "======================================" << endl;
    cout << "5 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test6(1,1,1,1,1,1);
    }
    end_tsc = rdtsc();


    cout << "======================================" << endl;
    cout << "6 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

    start_tsc = rdtsc();
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        proc_test7(1,1,1,1,1,1,1);
    }
    end_tsc = rdtsc();

    cout << "======================================" << endl;
    cout << "7 argument overhead: " << endl;
    cout << double(end_tsc - start_tsc) / NUM_TEST_CALLS << endl;

}




