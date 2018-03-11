#define _XOPEN_SOURCE 500

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[]) {

  struct stat file_stat;
  DIR *d;
  struct dirent *dir;
  if(argc == 1) d = opendir(".");
  else if(argc == 2) d = opendir(argv[1]);

  while((dir = readdir(d)) != NULL) {

    if(dir->d_name[0] == '.') continue;

    int s = lstat(dir->d_name,&file_stat);
    if(s != 0) {

      printf("Something went wrong.");
      exit(1);
    }

    if(S_ISREG(file_stat.st_mode))
    printf("-");
    else if(S_ISDIR(file_stat.st_mode))
    printf("d");
    else if(S_ISCHR(file_stat.st_mode))
    printf("c");
    else if(S_ISBLK(file_stat.st_mode))
    printf("b");
    else if(S_ISFIFO(file_stat.st_mode))
    printf("f");
    else if(S_ISLNK(file_stat.st_mode))
    printf("l");
    else if(S_IFSOCK & file_stat.st_mode)
    printf("s");

    printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %-5d %-5d",file_stat.st_uid,file_stat.st_gid);
    printf(" %-9lld",(long long)file_stat.st_size);
    char buf[70];
    strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M", localtime(&file_stat.st_mtime));
    printf(" %s",buf);
    printf(" %s\n",dir->d_name);
  }

  closedir(d);
  return 0;
}
