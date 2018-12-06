#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../util/util.cpp"

const off_t BLOCK = 8*1024;

int main(int argc, const char * argv[])
{
    uint64_t start;
    uint64_t end;
    uint64_t duration = 0;
    void* buf = malloc(BLOCK);
	const off_t FILESIZE = atoll(argv[1]);
    int fd = open(argv[2], O_RDONLY | O_SYNC);

    lseek(fd, FILESIZE - 1, SEEK_SET);
    off_t totalBytes = 0;

    while(1){
        lseek(fd, -2*BLOCK, SEEK_CUR);
        ssize_t bytes = read(fd, buf, BLOCK);
        if (bytes <= 0 || totalBytes >= FILESIZE)
            break;
        totalBytes += bytes;
    }
    
    close(fd);

    fd = open(argv[2], O_RDONLY| O_SYNC);
    totalBytes = 0;
    lseek(fd, FILESIZE - 1, SEEK_SET);
    
    while(1){
        lseek(fd, -2*BLOCK, SEEK_CUR);
        start = rdtsc();
        ssize_t bytes = read(fd, buf, BLOCK);
        end = rdtsc();
        duration += end - start;
        if (bytes <= 0 || totalBytes >= FILESIZE)
            break;
    }
    close(fd);
    free(buf);
    double ans = (double)(duration / (FILESIZE / BLOCK)) - 102;
    printf("%lf\n",ans);
    return 0;
}

