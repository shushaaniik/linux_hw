#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int num;

void* magic()
{
  srand(time(NULL));
  num = rand();
}


int main()
{
  pthread_t th;
  if(pthread_create(&th, NULL, &magic, NULL) != 0)
  {
    perror("Failed to create a thread.");
    return 1;
  }
  if(pthread_join(th, NULL) != 0)
  {
    return 1;
  }
  printf("The magic number is %d\n", num);
  return 0;
}
