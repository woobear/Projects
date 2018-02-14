#include <lzw.h>
#include <stdio.h>

/*   Course:    CS 360 Spring 2018
 Assignment:    1
     Author:    Rob Wooner
 */
int read(void* context) {
    return fgetc((FILE*) context);
}

int write(unsigned char c, void* context) {
    return fputc((int) c, (FILE*) context);
}

int main(int argc, char* argv[]) {
    FILE* r = fopen("./alice.txt", "r");
    FILE* w = fopen("./test.lzw", "w");

    if (lzwEncode(8,8,read,r,write,w)) {
        printf("done\n");
    }
    fclose(r);
    fclose(w);

    r = fopen("./test.lzw", "r");
    w = fopen("./test2.txt", "w");

    if (lzwDecode(8,8,read,r,write,w)) {
        printf("done\n");
    }
    fclose(r);
    fclose(w);
    return 0;
}
