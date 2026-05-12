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
    //receber void *args e cast para tipo copiar_t
    copiar_t *fi = (copiar_t *)args;
    //Chamar socp com os campos da struct
    socp(fi->src,fi->dest,fi->buffsize);
    //libertar memoria e devolver null
    free(fi);
    return NULL;
}

//syntax: socpthread src dest [blksize]
