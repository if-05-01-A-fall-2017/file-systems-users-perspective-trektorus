#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

int lstat(const char* file_path, struct stat* buf);
char* file_type(mode_t mode);
void print_file_permissions(mode_t mode);

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    printf("Wrong arguments!\n");
    exit(1);
  }

  struct stat file_stat;
  const char* file_path = argv[1];
  if (lstat(file_path, &file_stat) != 0) {

    printf("File does not exist.\n");
    exit(1);
  }

  printf("--------------------%s--------------------\n", file_path);
  printf("  File type: %s\n", file_type(file_stat.st_mode));
  printf("  Priviliges: ");
  print_file_permissions(file_stat.st_mode);
  printf("  inode-Number: %ju\n", (uintmax_t)file_stat.st_ino);
  printf("  Device numbers: dev=%ju; rdev=%ju\n", (uintmax_t)file_stat.st_dev, (uintmax_t)file_stat.st_rdev);
  printf("  Link count: %ju\n", (uintmax_t)file_stat.st_nlink);
  printf("  UID: %ju\n", (uintmax_t)file_stat.st_uid);
  printf("  GID: %ju\n", (uintmax_t)file_stat.st_gid);
  printf("  File size: %ju bytes\n", (uintmax_t)file_stat.st_size);
  printf("  Last access: %s", asctime(localtime(&(file_stat.st_atime))));
  printf("  Last modification: %s", asctime(localtime(&(file_stat.st_mtime))));
  printf("  Last inode change: %s", asctime(localtime(&(file_stat.st_ctime))));

  return 0;
}

char* file_type(mode_t mode) {

  switch (mode & S_IFMT) {

    case S_IFSOCK:
      return "Socket";
    break;

    case S_IFLNK:
      return "Symbolic link";
    break;

    case S_IFREG:
      return "Regular file";
    break;

    case S_IFBLK:
      return "Block special file";
    break;

    case S_IFDIR:
      return "Directory";
    break;

    case S_IFCHR:
      return "Character special file.";
    break;

    case S_IFIFO:
      return "FIFO";
    break;
  }

  return "";
}

void print_file_permissions(mode_t mode) {

  printf((S_ISDIR(mode)) ? "d" : "-");
  printf((mode & S_IRUSR) ? "r" : "-");
  printf((mode & S_IWUSR) ? "w" : "-");
  printf((mode & S_IXUSR) ? "x" : "-");
  printf((mode & S_IRGRP) ? "r" : "-");
  printf((mode & S_IWGRP) ? "w" : "-");
  printf((mode & S_IXGRP) ? "x" : "-");
  printf((mode & S_IROTH) ? "r" : "-");
  printf((mode & S_IWOTH) ? "w" : "-");
  printf((mode & S_IXOTH) ? "x" : "-");
  printf("\n");
}
