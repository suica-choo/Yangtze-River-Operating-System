#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "../util/util.cpp"

const off_t BLOCK = 8*1024;
off_t FILESIZE;
double sequence_read_time(const char *file, void* buf);
double random_read_time(const char *file, void* buf);

int main(int argc, const char *argv[])
{
    FILESIZE = atoll(argv[1]);
    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCK);
    double seq_ans = sequence_read_time(argv[2], buf);
    double ran_ans = random_read_time(argv[2], buf);
    free(buf);
    printf("%.2lf %.2lf\n", seq_ans, ran_ans);
    return 0;
}



double sequence_read_time(const char *file, void* buf)
{
    int fd = open(file, O_SYNC);
    if(fcntl(fd, F_NOCACHE, 1) == -1) {
        printf("Trying to disable cache Failed \n"); 
    }
    uint64_t start;
    uint64_t end;
    uint64_t duration;
    int count = 0;
    //calculate the sequence read time
    while (1) {
        start = rdtsc();
        ssize_t bytes = read(fd, buf, BLOCK);
        if (bytes <= 0) {
            break;
        }
        end = rdtsc();
        duration += end - start;
    }
    close(fd);
    double num = FILESIZE / BLOCK;
    return duration/(num*2.6*1e3);
}

double random_read_time(const char *file, void* buf)
{
    int i = 0;
    int fd = open(file, O_SYNC);
    if(fcntl(fd, F_NOCACHE, 1) == -1) 
    {
        printf("Trying to disable cache Failed \n"); 
    }
    off_t num = FILESIZE / BLOCK;
   
    uint64_t start;
    uint64_t end;
    uint64_t duration = 0;
    int count = 0;
    //calculate the random read time
    while(i < num) {
        off_t k = rand() % num;
        start = rdtsc();
        lseek(fd, k * BLOCK, SEEK_SET);
        read(fd, buf, BLOCK);
        end = rdtsc();
        duration += end - start;
        i++;
    }
    close(fd);
    return duration/(num*2.6*1e3);
}