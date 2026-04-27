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

    args[numargs-2] = NULL; //anular apontador para o simbolo de 2> etc
    return ( numargs-2 ); //dois argumentos foram consumidos
}
