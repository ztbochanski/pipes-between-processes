#include <stdio.h>  // for printf(), perror()
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork(), execlp(), close()
#include <fcntl.h>  // for open()

int pipe_file_descriptors[2];

// dup2(pipe_file_descriptors[1], 1); // write end of pipe to std out
// close(pipe_file_descriptors[0]);
// execvp(command, options);

int main(int argc, char **argv)
{
  pid_t process_id;

  // 0. check if correct number of args (file specified and command are minimum reqs)
  if (argc < 3 || argc > 5)
  {
    perror("Invalid number of arguments");
    exit(1);
  }
  // 1. command line arguments
  char *new_file = argv[1];
  char *command = argv[2];
  char *option1 = argv[3];
  char *option2 = argv[4];

  // 2. open the output file
  int output_file = open(new_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);

  // 3. create a pipe
  if (pipe(pipe_file_descriptors) == -1)
  {
    perror("pipe failed");
    exit(1);
  }

  // 4. fork the child process to run command
  if ((process_id = fork()) == -1)
  {
    perror("fork failed");
    exit(1);
  }
  else if (process_id == 0)
  {
    char *options[3] = {option1, option2, NULL};
    dup2(pipe_file_descriptors[1], 1); // write end of pipe to std out
    close(pipe_file_descriptors[0]);
    execvp(command, options);
  }

  // 6. in the parent read output and write to output file
  close(pipe_file_descriptors[1]); // close output end of pipe
  char buffer[2048];
  int number_of_bytes_read;
  while ((number_of_bytes_read = read(pipe_file_descriptors[0], &buffer, sizeof buffer)) > 0)
  {
    write(output_file, &buffer, number_of_bytes_read);
  }

  close(pipe_file_descriptors[0]);
  close(output_file);
}
