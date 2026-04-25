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
    printf("\033[1;34m%s\n%s\033[0m\033[1;32m@%s\033[0m %s> ", cwd, user, hostname, prompt);
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
                       
  //exit /* every built in function must return 1*/
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

  if (strlen(args[0])>4 && strncmp(args[0], "PS1=", 4) == 0) {
    
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
    else perror("ERROR! quemsoueu ");

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
      printf("Incorrect syntax: Usage: socp source destination\n");

    return 1;                   
  }


  // p5 - teste pratico

  if(strcmp(args[0], "epsilon")==0) {
      printf("Library %10e %10e\n",FLT_EPSILON, DBL_EPSILON);
      float eps = 1.0f; 
      while ((1.0f + eps / 2.0f) != 1.0f) eps /= 2.0f;
      printf("calculated: %10e\n",eps);

    return 1;                           //built in function
  }

  if(strcmp(args[0], "calc")==0 && args[1]!= NULL && args[2] != NULL && args[3] != NULL) {
    //chamar funcao calc
    calc(args[1],args[2],args[3]);

    return 1;                            // built-in function
  }

  if(strcmp(args[0], "bits")==0 && args[1]!= NULL && args[2] != NULL && args[3] != NULL) {
    //chama funcao bits
    bits(args[1],args[2],args[3]);

    return 1;                            // built-in function
  }

  if(strcmp(args[0], "isjpeg") == 0 && args[1] != NULL) {
    int fd = open(args[1], O_RDONLY);     // open file for reading
    if (fd<0) {
      perror(args[1]);
      return 1;
    } 
    if (isjpeg(fd))
        printf("%s is JPEG!\n", args[1]);
    else
        printf("%s isn't JPEG!\n", args[1]);
    close(fd);
    return 1;                   // built-in function
    }

  if(strcmp(args[0], "isgif") == 0 && args[1] != NULL) {
    int fd = open(args[1], O_RDONLY);
    if (fd<0) {
      perror(args[1]);
      return 1;
    }
    if (isgif(fd))
        printf("%s is a GIF!\n", args[1]);
    else
        printf("%s isn't a GIF!\n", args[1]);
    close(fd);
    return 1;               // built-in function
  }  

  if(strcmp(args[0], "isValid")==0) {
    if (NULL!=args[1]) {
      int fd=atoi(args[1]);
      printf("%s is %s valid\n", fd, fd_is_valid(fd)? "": "nope");
    }
    return 1;               // built-in function
  }
  
   if(strcmp(args[0], "close")==0) {
    if(NULL!=args[1]) {
      closefd(atoi(args[1]));
    }
    return 1;               // built-in function
  }

  if(strcmp(args[0], "openfile")==0) {
    if(NULL!=args[1]) {
      openfile(args[1]);
    }
    return 1;               // built-in function
  }

  if(strcmp(args[0], "read")==0) {
    if (NULL!=args[2] && strlen(args[2])>0) {
      int fd = atoi(args[1]);
      int nbytes = atoi(args[2]);
      readfd(fd, nbytes);
    } else
      printf("ERROR! Incorrect syntaxe. Usage: read <file_descriptor> <number_of_bytes>\n");
    return 1;               // built-in function
  }

  if (strcmp(args[0], "fileinfo") == 0) {
    fileinfo();
    return 1;               // built-in function
  }











  /* IMPORTANT: 
   Return 0 to indicate that there's no built in functionality and that 
   it will be executed through exec() within the funciton execute.c
  */

  return 0;
}
