// Zachary Bochanski
// Use pipe system call for interprocess communication between ls utility and wc utility
// This file is litered with comments for personal learning/note taking

#include <stdio.h>  // for printf(), perror()
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork(), execlp(), close()

int fd[2];
char *path = NULL;

void exec_first_command()
{
  dup2(fd[1], 1); // copy write end of pipe to std out slot of file descriptor
  close(fd[0]);
  execlp("ls", "ls", "-1a", path, NULL); // std out gets the output
}

void exec_second_command()
{
  dup2(fd[0], 0); // copy the read end of the pipe to the std input slot in the file descriptor
  close(fd[1]);
  execlp("wc", "wc", "-l", NULL); // wc command gets reads from read end of pipe
}

int main(int argc, char **argv)
{
  pid_t proccess_id;
  int count;

  // 1. parse the command line
  for (count = 0; count < argc; count++)
  {
    if (count == 1)
    {
      path = argv[count];
    }
  }

  // 2. make a pipe
  if (pipe(fd) == -1) // create pipe file in os with an [0] read end [1] write
  {
    perror("failed to create pipe");
    exit(1);
  }

  // 3. fork the process for the first argument of the fist pipe
  if ((proccess_id = fork()) == -1)
  {
    perror("failed to fork process");
    exit(1);
  }
  else if (proccess_id == 0)
  {
    exec_first_command();
  }

  // 5. parent process executes and reads from the pipe cache
  exec_second_command();
}
