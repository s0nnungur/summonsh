#include "shell.h"

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