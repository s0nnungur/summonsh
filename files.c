#include "shell.h"

int fd_is_valid(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

void openfile(char *nome){
    int fd = open(nome, O_RDONLY);
    if (fd >= 0)
        printf("Opened %s for reading. File number: %d\n", nome, fd);
    else
        perror("ERROR! can't open file\n");
}

void closefd(int fd) {
    if (close(fd) < 0)
        perror("ERROR! can't close file\n");
    else
        printf("%d closed OK\n", fd);
}

void readfd(int fd, int nbytes) {
    char buf[nbytes];
    
                                                
    if (!fd_is_valid(fd)) {                             //verificar se fd é válido e se o ficheiro está aberto
        fprintf(stderr, "File number %d isn't valid\n", fd);
        return;
    }

    int a = read(fd, buf, nbytes);
    if (a < 0) {
        perror("ERROR! can't read file\n");
        return; 
    }

    for(int i=0;i<a;i++) {                              // chars
        if(isprint(buf[i]))                             // é letra, num, espaço, etc (byte imprimivel)?
            printf("%c ", buf[i]);                      // imprime o char correspondente
        else
            printf(". ");                               // byte não imprimível, placeholder
    }
    printf("\n");
    
    for(int i=0;i<a;i++)                                // hex
        printf("%02x ", (unsigned char)buf[i]);         // imprime o valor hexadecimal do byte

    printf("\n");

}

void fileinfo() {
    if (stdout == NULL) {
        printf("ERROR! stdout isn't open\n");
    } else {
        int fd = fileno(stdout);                        // identifica fd associado a stdout
        printf("STDOUT is open: file number %d\n", fd);
    }

    //long max_files = sysconf(_SC_OPEN_MAX);             // alternativa para obter limite de ficheiros abertos
    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE, &rl);
    printf("Current Process has %ld File limit\n", (long)rl.rlim_cur);

    int count=0;                   // fds abertos e contador

    printf("Open files: ");
    for (int i=0;i<(int)rl.rlim_cur;i++) {
        if (fd_is_valid(i)) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\nProcess has %d open files\n", count);
}