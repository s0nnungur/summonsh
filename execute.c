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

// execute . cria um processo progénito e executa um programa

#include "shell.h"

void execute (int numargs, char **args) {
  int pid, status, fd[2];
  int code = ultimo(&numargs, args);

  if ((pid = fork ()) < 0) {  // creates child process
    perror ("forks");         // NOTE: perror() produces error msg to stream
    exit (1);                 // stderr which describes last found error during syscall ou lib function
  }

  if (pid == 0) {
    int index = containsPipe(numargs, args);

    if(index>0) {
      //tem pipe -> criar pipe, fork, dup2, execvp nos dois casos
      args[index]=NULL; //removes pipe symbol
      pipe(fd);
      int pidChild = fork();

      if(pidChild==0) {     // grandchild
        numargs = index;
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[0]); close(fd[1]);

        numargs = redirects(numargs, args);
        execvp(*args, args);
      } else {
        args = args + index + 1;
        numargs= numargs - index - 1;
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); close(fd[1]);
        numargs = redirects(numargs, args);
        execvp (*args, args);
      }
      
    } else { 
      //sem pipe -> atual
      numargs = redirects(numargs, args);
      execvp (*args, args);
      perror (*args);           // number of args isn't known. args of execv() e execvp() are file name
      exit (1);                 // to be executed and a string vector that contains args
    }  
  }                     

  if (code == FG)            
    while (wait (&status) != pid)
  return;
}

int ultimo (int *numargs, char **args) {
  if (args[*numargs-1][0]=='&') {
    *numargs=*numargs-1;
    args[*numargs]=NULL;
    return BG;
  }
  return FG;                  /* return FG (foreground) or BG (background) defined in shell.h */
}

int containsPipe (int numArgs, char **args) {
    for (int index = 0; index < numArgs; index++){
        if ( '|' == args[index][0] ) {
            return index;
        }
    }
    return -1;
}