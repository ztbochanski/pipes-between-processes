#include <stdio.h>  // for printf(), perror()
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork(), execlp(), close()
#include <fcntl.h>  // for open()

char *path = NULL;

int main(int argc, char **argv)
{
  int count;

  // 1. parse the command line
  for (count = 0; count < argc; count++)
  {
    if (count == 1)
    {
      path = argv[count];
    }
  }
}
