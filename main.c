#include "shell.h"

char prompt[100];

int main () {
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL)
    {
      printf ("\n");
      exit (0);
    }
    len = strlen (linha);
    if (1 == len)
      continue;/* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    parse (linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute (args);/* executa o comando */
    }
  return 0;
}

int builtin (char **args)
{
  /* Toda a funcionalidade embutida deverá devolver 1*/
  if (strcmp (args[0], "sair") == 0) {
    exit (0);
    return 1; /* funcionalidade embutida */
  }

  if (strncmp (args[0], "42", 2) == 0) {
    printf("42 is the answer to life the universe and everything\n");
    printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
    return 1;/* funcionalidade embutida */
  }

  if (0==strcmp(args[0], "obterinfo")) {
    printf("SO Shell 2025 versão 1.0\n");
    return 1; // funcionalidade embutida
  }

  if (strlen(args[0])>4 && 0==strncmp(args[0], "PS1=", 4) ) {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    char *pos = strstr(args[0]+4, "\\h");

    if (pos == NULL) {
      strcpy(prompt,args[0]+4);
    } else {
      strncpy(prompt, args[0]+4, pos - (args[0]+4));      //  parte antes do \h
      prompt[pos - (args[0]+4)] = '\0';                   //  terminar o string
      strcat(prompt, hostname);                           //  juntar hostname
      strcat(prompt, pos + 2);                            //  parte depois do \h
    }

    return 1; // funcionalidade embutida
  }



  /* IMPORTANTE : 
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
