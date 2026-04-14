#include "shell.h"
#define BUFSIZE 4096

void ioCopy(int IN, int OUT) {
    int n;
    char buf[BUFSIZE];
    while ((n=read(IN,buf,BUFSIZE))>0) {
      if(write(OUT,buf,n) != n) 
        perror("write error");
    }
    if (n<0)
      perror("read error");

    // loop: read -> write até não haver mais dados
    // tratamento de erros com perror
}

void socp(char *fonte, char *destino) {
  int fdIn = open(fonte, O_RDONLY);
    if (fdIn < 0) {
        perror("Erro a abrir o ficheiro de fonte");
        return;
    }

  int fdOut = creat(destino, S_IRUSR | S_IWUSR);
    if (fdOut < 0) {
        perror("Erro a abrir o ficheiro de destino");
        close(fdIn);
        return;
    }

  ioCopy (fdIn, fdOut);
  close(fdIn);
  close(fdOut);
}