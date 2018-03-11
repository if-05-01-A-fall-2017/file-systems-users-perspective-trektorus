#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  if (argc != 3) {
    printf("Wrong arguments!\n");
    exit(1);
  }

  char* src_path = argv[1];
  char* dst_path = argv[2];

  int src_fd = open(src_path, O_RDONLY);
  if (src_fd == -1) {
    printf("Wrong source file!\n");
    exit(1);
  }

  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int dst_fd = open(dst_path, O_WRONLY|O_CREAT|O_TRUNC, mode);
  if (dst_fd == -1) {
    printf("Forbidden characters in dest file name!\n");
    exit(1);
  }

  char buf[1024];

  int size = 0;
  while ((size = read(src_fd, buf, 1024)) != 0) {
    write(dst_fd, buf, size);
  }

  return 0;
}
