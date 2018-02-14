//Robert Wooner
//Assignment 2
//cs 360
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

bool search(int file, char* word) {
    int left = 0;
    char * buffer = (char*) malloc(sizeof(char)*16); 
    int w_count = lseek(file, 0, SEEK_END)/16;
    int right = w_count;
    //Binery search implementation
    while (left <= right ) {
        int middle = ((right + left)/2);

        if(lseek(file, (middle*16), SEEK_SET) == -1) {
            fprintf(stderr,"Failed to Run file");
             exit(-1); 
        }
        read(file, buffer, 16);
        int cmp = strncmp(word,buffer,16);

        if (cmp < 0) {
            right = middle -1 ;
        }else if (cmp > 0) {
            left = middle +1;
        }else{
            free(buffer);
            return true;
        }
    }
    free(buffer);
    return false;
}

// creates a to fit the 16 bit space
char* createWord(char* c) {
    int word_len = strlen(c);
    char * word = (char*) malloc(sizeof(char) * 16);

    if (word_len > 15) {
        printf("No");
    }
    
    for(int i = 0; i < 15;i++){
        if (i < word_len) {
            word[i] = c[i];
        }else {
            word[i] = ' ';
        }
    }

    word[15] = '\n';
    return word;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect amount of Arguments");
    }
    int readFile = open("./encs_share/cs/class/cs360/lib/webster", O_RDONLY);
    char* word = createWord(argv[1]);

    if (search(readFile, word)) {
        printf("yes\n");
    }else {
        printf("no\n");
    }
    close(readFile);
    free(word);
    return 0;
    
   
}

