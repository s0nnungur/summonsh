/* ========================================================================= */
/*  ░██████╗██╗░░░██╗███╗░░░███╗███╗░░░███╗░█████╗░███╗░░██╗░██████╗██╗░░██╗ */
/*  ██╔════╝██║░░░██║████╗░████║████╗░████║██╔══██╗████╗░██║██╔════╝██║░░██║ */
/*  ╚█████╗░██║░░░██║██╔████╔██║██╔████╔██║██║░░██║██╔██╗██║╚█████╗░███████║ */
/*  ░╚═══██╗██║░░░██║██║╚██╔╝██║██║╚██╔╝██║██║░░██║██║╚████║░╚═══██╗██╔══██║ */
/*  ██████╔╝╚██████╔╝██║░╚═╝░██║██║░╚═╝░██║╚█████╔╝██║░╚███║██████╔╝██║░░██║ */
/*  ╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝ */ 
/* ========================================================================= */
/* Author : s0nnungur  (José Miguel Santos)                                  */
/* Date   : 06-05-2026                                                       */
/* Desc   : Unix shell written in C                                          */
/* ========================================================================= */

#include "shell.h"

void maior(char *f1, char *f2) {
    struct stat statbuf1, statbuf2;
    long int size1,size2;

    if (stat(f1, &statbuf1) < 0) {
        perror(f1); // imprime: "f1: No such file or directory"
        return;
    }
    
    if(stat(f2, &statbuf2) < 0) {
        perror(f2); // imprime: "f1: No such file or directory"
        return;
    }

    size1=statbuf1.st_size / 1024;
    size2=statbuf2.st_size / 1024;

    if(size1 > size2) {
        printf("\n%s : %ldKB is the bigger file\n", f1, size1);
    } else if(size1 < size2) {
        printf("\n%s : %ldKB is the bigger file\n", f2, size2);
    } else
        printf("\nBoth files have the same size: %ldKB\n", size1);
}