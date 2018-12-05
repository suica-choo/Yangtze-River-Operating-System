#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "../util/util.cpp"
#include <mach/mach_time.h>

#define COUNT 1e4
#define TIMES 1e2
#define NANO_TRANSFER 1e9

//declare variables
int stride_arr[7] = {4, 64, 128, 1024, 1048576, 4194304, 16777216};


static mach_timebase_info_data_t timebase;
static void __attribute__((constructor)) init_info() {
	mach_timebase_info(&timebase);
}

double calculate_time();
double cacheAccessTime(int size, int strideLength);
void fixedStride(int strideIndex, FILE *file, int times);

int main(int argc, const char * argv[])
{
	FILE *file;
	file = fopen("memory_access_result", "w");
    srand((unsigned int)time(0));
	fixedStride(2, file, TIMES);
    fclose(file);
    printf("Finish the benchmark for memory access time\n");
    return 0;
}

double calculate_time() {
  uint64_t time = mach_absolute_time();
  double dtime = (double) time;
  dtime *= (double) timebase.numer;
  dtime /= (double) timebase.denom;
  return dtime / NANO_TRANSFER;
}

double cacheAccessTime(int size, int strideLength)
{
    int* A;
    A = (int *)malloc(size * 1024 / 4 * sizeof(int));
    int num, length;
    length = strideLength / 4;   
    num = size * 1024 / 4;
    int index;
    A[0] = 0;
    for (int i = 0; i < num; i++) {
        index = i + length;
        if (index >= num) {
            index %= num;
        }
        A[i] = index;
    }

    int x = 0;
    int64_t start;
    int64_t end;
    int64_t total_time = 0;
    int count = COUNT;

    start = rdtsc();
    for (int i = 0; i < count; i++) {
        x = A[x];
    }
    end = rdtsc();
    total_time = end - start;
    double ans = (total_time - 106) / count - 6;
    free(A);
    return ans;
}

void fixedStride(int strideIndex, FILE *file, int ts)
{
    int size_arr[18] = {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
    for (int i = 0; i < ts; i++) {
		for (int j = 0; j < 18; j++) {
			double averageTime = cacheAccessTime(size_arr[j], stride_arr[strideIndex]);
			fprintf(file, "%lf ", averageTime);
		}
		fprintf(file, "\n");
	}
	return ;

}

