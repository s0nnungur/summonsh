#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void ftype(char* filename);

int main(int argc, char **argv) {
    if(argv[1]!=NULL)
        ftype(argv[1]);
    else printf("Syntax error! usage: ./ftype <filename>\n");
}

void ftype(char* filename) {
    struct stat buf;

    if(stat(filename, &buf)==0) {
        if(S_ISDIR(buf.st_mode))        // ou entao  manual:"if ((buf.st_mode & S_IFMT) == S_IFDIR)""
            printf("%s is a directory\n", filename);
        else if(S_ISREG(buf.st_mode))    // ou entao manual: "if ((buf.stmode & S_IFREG) == S_IFREG)"
            printf("%s is a regular file\n", filename);
        else 
            printf("%s is something else lol!\n", filename);
    } else perror(filename);              // imprime filename: no such file/dir
}