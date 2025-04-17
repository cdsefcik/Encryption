#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


/* 
Simple encryption using a XOR. This is not intended for production as it is very easy to break. Takes three parameters from the command line.

Usage:  crypto key    input_file      output_file 

*/

int main(int argc, char* argv[])

{
    FILE* fi, * fo;
    char* cp;
    int c;

    if ((cp = argv[1]) && *cp != '\0') {
        if ((fi = fopen(argv[2], "rb")) != NULL) {
            if ((fo = fopen(argv[3], "wb")) != NULL) {
                while ((c = getc(fi)) != EOF) {
                    if (!*cp) cp = argv[1];
                    c ^= *(cp++);
                    putc(c, fo);
                }
                fclose(fo);
            }
            fclose(fi);
        }
    }
}
