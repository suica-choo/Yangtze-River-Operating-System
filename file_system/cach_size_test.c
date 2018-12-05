#include <stdio.h>
#include <sys/types.j>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

const off_t BLOCK = 8*1024;

int main(int argc, const char * argv[])
{
    uint64_t start;
    uint64_t end;
    uint64_t duration = 0;
    void* buf = malloc(BLOCKSIZE);
	const off_t FILESIZE = atoll(argv[1]);
    int fd = open(argv[2], O_RDONLY | O_SYNC);

    lseek(fd, FILESIZE - 1, SEEK_SET);
    off_t totalBytes = 0;

    while(1){
        lseek(fd, -2*BLOCKSIZE, SEEK_CUR);
        ssize_t bytes = read(fd, buf, BLOCK);
        if (bytes <= 0 || totalBytes >= FILESIZE)
            break;
        totalBytes += bytes;
    }
    
    close(fd);

    fd = open(argv[2], O_RDONLY| O_SYNC);
    totalBytes = 0;
    lseek(fd, FILESIZE - 1, SEEK_SET);
    
    while(true){
        lseek(fd, -2*BLOCK, SEEK_CUR);
        start = rdtsc();
        ssize_t bytes = read(fd, buf, BLOCK);
        end = rdtsc();
        duration += end - start;
        if (bytes <= 0 || totalBytes >= FILESIZE)
            break;
        totalBytes += bytes;
    }
    
    close(fd);
    free(buf);
    double ans = (double)(duration / (FILESIZE / BLOCK)) - 102;
    printf("%lf\n",ans);
    return 0;
}

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" : "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}
