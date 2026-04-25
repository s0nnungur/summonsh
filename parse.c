/* ========================================================================= */
/*  ░██████╗██╗░░░██╗███╗░░░███╗███╗░░░███╗░█████╗░███╗░░██╗░██████╗██╗░░██╗ */
/*  ██╔════╝██║░░░██║████╗░████║████╗░████║██╔══██╗████╗░██║██╔════╝██║░░██║ */
/*  ╚█████╗░██║░░░██║██╔████╔██║██╔████╔██║██║░░██║██╔██╗██║╚█████╗░███████║ */
/*  ░╚═══██╗██║░░░██║██║╚██╔╝██║██║╚██╔╝██║██║░░██║██║╚████║░╚═══██╗██╔══██║ */
/*  ██████╔╝╚██████╔╝██║░╚═╝░██║██║░╚═╝░██║╚█████╔╝██║░╚███║██████╔╝██║░░██║ */
/*  ╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝ */ 
/* ========================================================================= */
/* Author : s0nnungur  (José Miguel Santos                                   */
/* Date   : 2026                                                             */
/* Desc   : Unix shell written in C                                          */
/* ========================================================================= */


#include "shell.h"

/*
    parse . particiona o comando (armazenado em ptrLinha) em argumentos
    exemplo ptrLinha -> "ls  -l /etc/passwd & "
    O string contem caracteres e espaços e é terminado com um \0
*/

int parse (char *ptrLinha, char **args) {
  int cnt=0;
  while ('\0' != *ptrLinha) {    
      /* saltar whitespace. Substituimos whitespace por um \0 */
      while (isspace ((unsigned char) *ptrLinha))
        *ptrLinha++ = '\0';
      *args++ = ptrLinha;         /* salvaguarda argumento */
      cnt++;

      /* salta sobre os caracteres do argumento ou encontrar o fim da linha*/
      while ((*ptrLinha != '\0') && (!isspace ((unsigned char) *ptrLinha)))
        ptrLinha++;
    }
  *args = (char *) NULL;          /* Inserir o ultimo argumento igual a NULL */
  return cnt;
}
