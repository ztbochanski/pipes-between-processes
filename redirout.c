#include <stdio.h>  // for printf(), perror()
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork(), execlp(), close()
#include <fcntl.h>  // for open()

char *new_file = NULL;

int main(int argc, char **argv)
{

  // 1. command line arguments
  char *new_file = argv[1];
  char *command = argv[2];
  char *option1 = argv[3];
  char *option2 = argv[4];

  // 2. open the output file

  // 3. create a pipe

  // 4. fork the child process to run command
}
