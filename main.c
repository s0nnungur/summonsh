#include "shell.h"

char prompt[100];
char hostname[256];
char *user;
char prev_dir[1024] = "";

int main () {
  int len;
  char linha[1024];                                       /* one command */
  char *args[64];                                         /* with a max of 64 arguments */

  strcpy (prompt, "SOSHELL: prompt>");
  gethostname(hostname, sizeof(hostname));
  user = getenv("USER");
  getcwd(prev_dir, sizeof(prev_dir));                     /* initialize previous dir */

  while (1) {
    char cwd[1024];                                       /* current working directory array */
    getcwd(cwd, sizeof(cwd));
    printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m %s> ", user, hostname, cwd, prompt);
    // printf ("%s", prompt);

    if (fgets (linha, 1023, stdin) == NULL) {
      printf ("\n");
      exit (0);
    }

    len = strlen (linha);
    
    if (1 == len)
      continue;                                           /* line is just \n */
    
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
  
    int numargs = parse (linha, args);                                  /* partitions the string into arguments */

    if (!builtin (args))
      execute (numargs, args);                                     /* executes the command */
    }
  return 0;
}


int builtin (char **args) {
                                                          /* every built in function must return 1*/
  if (strcmp (args[0], "sair") == 0) {
    exit (0);
    return 1;                                             /* built-in functionality */
  }

  if (strncmp (args[0], "42", 2) == 0) {
    printf("42 is the answer to life the universe and everything\n");
    printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
    return 1;                                             /* built-in functionality */
  }

  if (0==strcmp(args[0], "obterinfo")) {
    printf("SO Shell 2025 versão 1.0\n");
    return 1;                                             /* built-in functionality */
  }

  if (strlen(args[0])>4 && 0==strncmp(args[0], "PS1=", 4) ) {
    
    char *pos = strstr(args[0]+4, "\\h");

    if (pos == NULL) {
      strcpy(prompt,args[0]+4);
    } else {
      strncpy(prompt, args[0]+4, pos - (args[0]+4));      //  starts before \h
      prompt[pos - (args[0]+4)] = '\0';                   //  finishes the string
      strcat(prompt, hostname);                           //  appends hostname
      strcat(prompt, pos + 2);                            //  starts after \h
    }

    return 1; // built-in functionality
  }

  if(0==strcmp(args[0], "quemsoueu")) {

    int n = getgroups(0,NULL);                            // checks how many groups exist
    gid_t lista[n];                                       // define array for group ids 
    getgroups(n,lista);                                   // fills array with ids

    uid_t uid = getuid();                                 // GetUser ID as int
    struct passwd *pw = getpwuid(uid);                    // get user info

    gid_t gid = getgid();                                 // GetGroup ID as int
    struct group *gr = getgrgid(gid);                     // get group info
    
    if (pw) 
      printf("uid=%d(%s)\n", uid, pw->pw_name);
    else perror("quemsoueu erro");

    if (gr)
      printf("gid=%d(%s) ", gid, gr->gr_name);
    
    printf ("groups=");
    for (int i=0;i<n;i++) {
      struct group *g = getgrgid(lista[i]);
      if (i>0) printf(",");
      if (g)
        printf("%d(%s)", lista[i], g->gr_name);
      else
        printf("%d", lista[i]);
    }
    printf("\n");
      return 1;                                            // built-in functionality
  }

  if (0 == strcmp(args[0], "cd")) {

    int err;
    char *destino;
    char temp[1024];

    if (NULL == args[1] || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)  {
      destino = getenv("HOME");                           // finds home directory
    } else if (0 == (strcmp(args[1], "-"))) {
      if (0 == (strlen(prev_dir))) {
        printf("cd: OLDPWD not set\n");
        return 1;
      }
      destino = prev_dir;
    } else 
      destino = args[1];

    // saves current dir before changing
    getcwd(temp, sizeof(temp));

    // change
    err = chdir(destino);

    // updates prev_dir after changing
    strcpy(prev_dir, temp);

    if (err < 0) 
      perror (args[1]);

    return 1;                                              // built-in functionality
  }

  if(0 == strcmp(args[0], "socp")) {
    if (args[1] != NULL && args[2] != NULL)
      socp(args[1], args[2]);
    else 
      printf("Incorrect syntax. Usage: socp source destination\n");

    return 1;                   
  }

  if(0 == strcmp(args[0], "epsilon")) {
      printf("Biblioteca %10e %10e\n",FLT_EPSILON, DBL_EPSILON);
      float eps = 1.0f; 
      while ((1.0f + eps / 2.0f) != 1.0f) eps /= 2.0f;
      printf("calculado: %10e\n",eps);

    return 1; //funcao embutida
  }

  /* IMPORTANT: 
   Return 0 to indicate that there's no built in functionality and that 
   it will be executed through exec() within the funciton execute.c
  */

  return 0;
}
