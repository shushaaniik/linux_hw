// used classwork materials for this

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int is_file(char* path)
{
  struct stat st_buf;
  int ret_code = stat(path, &st_buf);
  if(ret_code != 0) 
  { 
    printf("not a file:%s\n", path);
  }

  if(S_ISREG(st_buf.st_mode)) { return 1; } 
  else { return 0; }
}

int cat(char* path)
{
  int fd = open(path, O_RDONLY);
  if(fd < 0){ return -1; }

  off_t length = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char* content = malloc(length*sizeof(char));
	
  size_t status = read(fd, content, length);
  if(status != length)
  {
    printf("%d, %s\n", errno, strerror(errno));
    return -1;
  }
	
  printf("Path : %s\n, Content:  %s\n", path, content);

  free(content);
  close(fd);
}

int show_dir(const char* path)
{
  DIR* od = opendir(path);
  if(od == NULL)
  {
    printf("invalid directory:%s \n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  struct dirent* dir_s;
	
  while((dir_s = readdir(od)) != NULL)
  {
    char full_path[250];

    if (dir_s->d_name[0] == '.'){ continue; }
	
    strcat(full_path, path);
    if (full_path[strlen(path)-1] != '/')
    {
      strcat(full_path,"/");	
    }
    strcat(full_path, dir_s->d_name);
    if (is_file(full_path) == 1)
    {
      cat(full_path);	
    }
    memset(full_path, 0, 250);
  }

  return 1;
}

int main(int argc, char** argv)
{
  if(argc > 2 || argc == 0)
  {
    perror("invalid arg");
    exit(EXIT_FAILURE);
  }
  if(argc == 1)
  {
    show_dir(".");
  }
  show_dir(argv[1]);
  return 0;
}

