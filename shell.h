/* ========================================================================= */
/*  ░██████╗██╗░░░██╗███╗░░░███╗███╗░░░███╗░█████╗░███╗░░██╗░██████╗██╗░░██╗ */
/*  ██╔════╝██║░░░██║████╗░████║████╗░████║██╔══██╗████╗░██║██╔════╝██║░░██║ */
/*  ╚█████╗░██║░░░██║██╔████╔██║██╔████╔██║██║░░██║██╔██╗██║╚█████╗░███████║ */
/*  ░╚═══██╗██║░░░██║██║╚██╔╝██║██║╚██╔╝██║██║░░██║██║╚████║░╚═══██╗██╔══██║ */
/*  ██████╔╝╚██████╔╝██║░╚═╝░██║██║░╚═╝░██║╚█████╔╝██║░╚███║██████╔╝██║░░██║ */
/*  ╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝ */ 
/* ========================================================================= */
/* Author : s0nnungur  (José Miguel Santos)                                  */
/* Date   : 2026                                                             */
/* Desc   : Unix shell written in C                                          */
/* ========================================================================= */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h> 
#include <pwd.h>
#include <grp.h>
#include <float.h>
#include <math.h>
#include <errno.h>

typedef unsigned short type;


int parse(char *buf, char **args); 
/* parses the input buffer and fills the arguments array */

void execute(int numargs, char **args);
/* executes the command specified by args[0] with the arguments in args[1], args[2], ..., args[numargs-1]. */

int builtin (char **args);
/* built-in function that checks if the command is a built-in command and executes it if so. */

void socp(char *fonte, char *destino);
/* built-in function that copies the content of a file (source) 
to another file (destination) using low-level I/O system calls (open, read, write, close). */

void ioCopy(int IN, int OUT); 
/* built-in function that copies the content of a file (source) 
to another file (destination) using low-level I/O system calls (open, read, write, close). */

int ultimo(int *numargs, char **args); 
/* built-in function that checks if the last argument
 is an ampersand (&) and if so, removes it from the arguments list and returns 1 to 
 indicate that the command should be executed in the background. 
 If the last argument is not an ampersand, 
 it returns 0 to indicate that the command should be executed in the foreground. */

void calc(char *value1, char *op, char *value2); 
/* built-in function that performs basic arithmetic operations 
(addition, subtraction, multiplication, division) on two numbers and prints the result. */

void bits(char *op1, char *op, char *op2); 
/* built-in function that performs bitwise operations (AND, OR, XOR) on two integers and prints the result in binary format. */

int isjpeg (int fileDescriptor); 
/* checks if a certain file is a jpg/jpeg */

int isgif (int fileDescriptor); 
/* checks if a certain file is a gif */

int fd_is_valid(int fd); 
/* checks if a given file descriptor is valid (i.e. if a file is open) */

void openfile(char *nome); 
/* opens a file with filename nome and reports the file descriptor. */

void closefd (int fd); 
/* closes a file with file descriptor fd */

void readfd(int fd, int nbytes); 
/* reads n bytes from file with file descriptor fd and prints them as char (if ascii) and also as hexadec values on the next line. */

void fileinfo(); 
/* returns information on the status of the stdout file pointer (FILE *stdout)
i.e. is it opened or not (NULL or not), and what file descriptor it is using,
and also the current max number of open files the current process can have,
the file descriptors that are open and the total number of opened file descriptors.
*/

//void printBitsLn(type num, type mask);
/* prints the bits of a number in a new line */

void printBits(type num, type mask);
/* prints the bits of a number */

void printRow(const char *expr, type num, type mask);
/* prints a row of the bit table */




/* useful constants*/

#define BG 0
#define FG 1
