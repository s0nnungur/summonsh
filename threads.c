/* ========================================================================= */
/*  ░██████╗██╗░░░██╗███╗░░░███╗███╗░░░███╗░█████╗░███╗░░██╗░██████╗██╗░░██╗ */
/*  ██╔════╝██║░░░██║████╗░████║████╗░████║██╔══██╗████╗░██║██╔════╝██║░░██║ */
/*  ╚█████╗░██║░░░██║██╔████╔██║██╔████╔██║██║░░██║██╔██╗██║╚█████╗░███████║ */
/*  ░╚═══██╗██║░░░██║██║╚██╔╝██║██║╚██╔╝██║██║░░██║██║╚████║░╚═══██╗██╔══██║ */
/*  ██████╔╝╚██████╔╝██║░╚═╝░██║██║░╚═╝░██║╚█████╔╝██║░╚███║██████╔╝██║░░██║ */
/*  ╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝ */ 
/* ========================================================================= */
/* Author : s0nnungur  (José Miguel Santos)                                  */
/* Date   : 11-05-2026                                                             */
/* Desc   : Unix shell written in C                                          */
/* ========================================================================= */
#include "shell.h"
char strings[MAX][130];
int k = 0;

void aviso (char *msg, int tempo) {
    while (tempo >0) {
        sleep (1);
        tempo--;
    }
    fprintf(stderr, "Aviso : %s\n", msg);
}

void * avisowrapperMAU(void *args) {
    char ** pargs = (char **)args;
    aviso(pargs[1], atoi(pargs[2]));
    return NULL;
}

void * avisowrapper(void *args) { //unwrap it
    aviso_t * ptr = (aviso_t *)args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    return NULL;
}

void * cpWrapper(void *args) {
    //receives void *args and casts to type copiar_t
    copiar_t *fi = (copiar_t *)args;
    //call socp with struct fields
    socp(fi->src,fi->dest,fi->blksize);

    time_t tempoAtual;
    time(&tempoAtual);

    //converts to readable string
    char *diaHora = ctime(&tempoAtual);

    //removes '\n' from string end
    if ('\n' == diaHora[strlen(diaHora)-1]) 
        diaHora[strlen(diaHora)-1] = '\0';

    //writes entry to global array
    sprintf(strings[k++%MAX], "%s %s -> %s", diaHora, fi->src, fi->dest);

    free(fi);
    return NULL;
}
