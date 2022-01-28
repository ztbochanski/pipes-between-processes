// Zachary Bochanski
// Use pipe system call for interprocess communication between ls utility and wc utility
// This file is litered with comments for personal learning/note taking

#include <stdio.h>  // for printf(), perror()
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork(), execlp(), close()

int main(int argc, char **argv)
{
  // 1. parse the command line
  int count;
  for (count = 0; count < argc; count++)
    printf("argv[%d] => %s\n", count, argv[count]);

  // 2. make a pipe in the parent
  int fd[2];

  // 3. fork
  // 4. run word count with the child
  // 5. parent runs ls
}