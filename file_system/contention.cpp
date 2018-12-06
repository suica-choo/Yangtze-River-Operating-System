#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "../util/util.cpp"

using namespace std;
off_t FILESIZE;
const char *files[] = {"temp0", "temp1", "temp2", "temp3", "temp4", "temp5", "temp6", "temp7", "temp8", "temp9"};

void readFile(int index){
  void *buf = malloc(4096);
  int fd = open(files[index], O_RDONLY);
  if(fcntl(fd, F_NOCACHE, 1) == -1) {
     exit(1);
  }

  uint64_t start_tsc;
  uint64_t end_tsc;
  uint64_t sum;
  while(1){
    start_tsc = rdtsc();
    ssize_t bytes = read(fd, buf, 4096);
    if(bytes <= 0){
      break;
    }
    end_tsc = rdtsc();
    sum += end_tsc - start_tsc;
  }
  close(fd);
  double blocks = FILESIZE / 4096;
  cout << sum / blocks / 2.6 / 1000 << endl;

}

void readFileRandomly(int index){
  void *buf = malloc(4096);
  int fd = open(files[index], O_RDONLY);
  if(fcntl(fd, F_NOCACHE, 1) == -1) {
    exit(1);
  }

  uint64_t start_tsc;
  uint64_t end_tsc;
  uint64_t sum;

  off_t blocks = FILESIZE / 4096;
  off_t *access_list = (off_t*)malloc(blocks * sizeof(off_t));

  for (int i = 0; i < blocks; i++) 
  {
     access_list[i] = rand() % blocks;
  }

  for (int i = 0; i < blocks; i++) {
    start_tsc = rdtsc();
    lseek(fd, access_list[i] * 4096, SEEK_SET);
    read(fd, buf, 4096);
    end_tsc = rdtsc();
    sum += end_tsc - start_tsc;
  }

  close(fd);
  cout << sum / (double)blocks / 2.6 / 1000;
}

int main(int argc, char const *argv[])
{
  FILESIZE = atoll(argv[1]);
  srand((unsigned int)time(NULL));

  pid_t pids[10];
  int processes = atoll(argv[2]);
  
  for (int i = 0; i < processes; i++) {
    if ((pids[i] = fork()) < 0) {
      perror("fork");
      exit(1);
    }
    else if (pids[i] == 0) {
      readFile(i);
      exit(0);
    }
    else {
      wait(NULL);
    }
  }

  for (int i = 0; i < processes; i++) {
    if ((pids[i] = fork()) < 0) {
      perror("fork");
      exit(1);
    }
    else if (pids[i] == 0) {
      readFileRandomly(i);
      exit(0);
    }
    else {
      wait(NULL);
    }
  }

  return 0;
}
