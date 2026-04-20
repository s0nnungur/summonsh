#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <pwd.h>
#include <grp.h>
#include <float.h>


int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args);

void socp(char *fonte, char *destino);

void ioCopy(int IN, int OUT);

int ultimo(int *numargs, char **args);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1