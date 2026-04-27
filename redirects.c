#include "shell.h"

//closes fdold, duplicates fd on top of fdold and then closes fd
//annulls pointer to redirect symbol returns the number of arguments-two
//pre condition numargs >=3

int dupandclose(int fd, int fdold, int numargs, char *args[]) {

    if (fd < 0 || fdold < 0) {
        perror("Invalid fds");
        exit(1); /*indicar um erro*/
    }

    dup2(fd, fdold);
    close(fd);

    args[numargs-2] = NULL; // args[1] = NULL, removes from args[]
    return (numargs-2); // only initial command (args[0]) remains
}

// redirects.c tratamento dos simbolos de redirecionamento
// por ordem inversa: i) 2> ii) > OU >> iii) <

int redirects(int numargs, char *args[]) {
    // redirect "2>"
    if ( numargs>=3 && strcmp(args[numargs-2], "2>") == 0) {
        int fd = creat(args[numargs - 1], FILE_MODE);
        numargs = dupandclose(fd, STDERR_FILENO, numargs, args);
    }

        // redirect ">"
    if (numargs>=3 && strcmp(args[numargs-2], ">")==0) {
        int fd = creat(args[numargs-1], FILE_MODE);
        numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);

        // redirect ">>"
    } else if (numargs>=3 && strcmp(args[numargs-2], ">>")==0) {
        int fd = open(args[numargs-1], O_CREAT|O_APPEND|O_WRONLY, FILE_MODE);
        numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
    }
    
    if (numargs>=3 && strcmp(args[numargs-2], "<")==0) {
        int fd = open(args[numargs-1], O_RDONLY, FILE_MODE);
        numargs = dupandclose(fd, STDIN_FILENO, numargs, args);
    }

return numargs; //devolver nº de argumentos a passar para exec(…)
}