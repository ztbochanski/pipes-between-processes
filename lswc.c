#include <stdio.h>  // for printf(), perror()
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork(), execlp(), close()

// 1. parse the command line
// 2. make a pipe in the parent
// 3. fork
// 4. run word count with the child
// 5. parent runs ls
