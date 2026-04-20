#include "shell.h"

int isjpeg (int fileDescriptor) {
    /* ficheiro tem que estar aberto */
    unsigned char b[4];
    int n = read(fileDescriptor,b,4);
    if(n < 4)
      return 0;

    lseek(fileDescriptor, 0, SEEK_SET);
      
    //detetar ..
    if ( 0xff == b[0] && 0xd8==b[1] && 0xff==b[2] && (0xe0==b[3] || 0xe1 == b[3] || 0xe2 == b[3] || 0xe8 == b[3]))
      return 1;   //built-in function
    
    return 0;     //failed
    }