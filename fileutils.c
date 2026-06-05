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
        perror(f1); // prints: "f1: No such file or directory"
        return;
    }
    
    if(stat(f2, &statbuf2) < 0) {
        perror(f2); // prints: "f1: No such file or directory"
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

void setx(char *file) {
    struct stat statbuf;

    if (stat(file, &statbuf) < 0) {
        perror(file); // prints: "file: No such file or directory"
        return;
    }

    int execute_mode = statbuf.st_mode | S_IXUSR;
    
    if(chmod(file, execute_mode) < 0) {
        perror(file);
        return;
    }

    printf("\nExecution permissions added to %s\n", file);
}

void removerl(char *file) {
    struct stat statbuf;

    if (stat(file, &statbuf) < 0) {
        perror(file); // prints: "file: No such file or directory"
        return;
    }

    int mask = S_IRGRP | S_IROTH;
    int remove_read = statbuf.st_mode & ~mask;

    if (chmod(file, remove_read) < 0) {
        perror(file);
        return;
    }

    printf("\nReading permission removed for group/others in %s\n", file);
}
