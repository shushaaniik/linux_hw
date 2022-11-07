#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    std::cerr << "Not appropriate arguments\n";
    return 1;
  }

  int n = atoi(argv[1]);
  char* text_buf = argv[2];
  std::string text;
  text += text_buf;
  text += ' ';
  //std::cout << text;
  std::string path = "file_";

  for(int i = 1; i <= n; ++i)
  {
    std::string i_str = std::to_string(i);
    std::string i_path = path;
    i_path += i_str;
    i_path += ".txt";
    int i_path_len = i_path.length();
    std::string i_text = text;
    i_text += i_str;
    int i_text_len = i_text.length();

    char* char_path = new char[i_path_len];
    strcpy(char_path, i_path.c_str());
    char* char_text = new char[i_text_len];
    strcpy(char_text, i_text.c_str());

    int fd = open(char_path, O_CREAT | O_WRONLY, 0644);

    if(fd < 0)
    {
      std::cerr << "Error: " << strerror(errno) << std::endl;
      return errno;
    }

    ssize_t size = write(fd, char_text, i_text_len);
    close(fd);

    delete[] char_text;
    delete[] char_path;
  }

  return 0;
}
