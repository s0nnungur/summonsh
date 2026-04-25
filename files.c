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

int isjpeg (int fileDescriptor) {
    /* ficheiro tem que estar aberto */
    unsigned char b[4];
    int n = read(fileDescriptor,b,4);
    if(n < 4)
      return 0;

    lseek(fileDescriptor, 0, SEEK_SET); // volta ao inicio do ficheiro
      
    //detetar ..
    if ( 0xff == b[0] && 0xd8==b[1] && 0xff==b[2] && (0xe0==b[3] || 0xe1 == b[3] || 0xe2 == b[3] || 0xe8 == b[3]))
      return 1;   //built-in function
    
    return 0;     //failed
    }

int isgif (int fileDescriptor) {
    /* ficheiro tem que estar aberto */
    unsigned char b[6];  // 6 bytes para detetar GIF87a ou GIF89a
    int n = read(fileDescriptor,b,6);
    if(n < 6)
      return 0;

    lseek(fileDescriptor, 0, SEEK_SET);
      
    //detetar ..
    if ( 0x47 == b[0] && 0x49==b[1] && 0x46==b[2] && 0x38 == b[3] && (0x39 == b[4] || 0x37 == b[4]) && 0x61 == b[5])
      return 1;   //built-in function
    
    return 0;     //failed
}