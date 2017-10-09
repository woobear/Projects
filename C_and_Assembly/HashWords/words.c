//Robert Wooner
//Assignment 2
//CS261
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_WORD_SIZE 256
#include "hash.h"

char* getNextWord(FILE *fd){
	int index = 0;
	int c;
	char letters[MAX_WORD_SIZE];
  for ( int j = 0; j < MAX_WORD_SIZE; j++){
		letters[j] = 0;
	}
	while ( (c = fgetc(fd)) != EOF) {
		if (isspace(c)) {
			letters[index] = '\0';
			if ( index > 0 ){
				letters[index] = '\0';
				return strdup(letters);
			} else {
				c = fgetc(fd);
			}
		} if (((isalnum(c)))){
				if (index == MAX_WORD_SIZE -1) {
					return strdup(letters);
				}
				letters[index] = tolower(c);
				index++;
			} 
	}
	return NULL;
}

int main( int argc, char *argv[]) {
	dict *table = newTable();
	storage *bin = NULL;
	int i = 0;
	int numLine = strtol(argv[1],NULL,10);
	if (argc >=  2){
		for ( i = 1 ; i < argc; i++) {
			if (numLine < 0){
				numLine = numLine * -1;
				i++;
			}
			FILE *fd =fopen(argv[i],"r");
			char *buffer;
			if ( fd == NULL ) {
				fprintf(stderr,"The file %s is bad news\n",argv[i]);
				printf("if you are trying for optional argument for the top number of word values, here is an example '-20'");
				return 1;
			}else {
				while (1){
					int *value = malloc(sizeof(int));
					*value = 1;
					buffer = getNextWord(fd);
					if (buffer != NULL){
						insert(buffer, value, table);
						if (table->collCount >= table->size) {
							upgrade(table);
						}
					}else {
						free(value);
						break;
					}
				}
			fclose(fd);
			}
		}
	}else {
		fprintf(stderr, "Needs Arguments");
	}
	bin = (storage*)malloc(sizeof(storage)* table->binCount);
	for (int i = 0; i < table->binCount; i++){
		bin[i].key = NULL;
		bin[i].value = NULL;
		bin[i].next = NULL;
	}
	applylist(table,makeAnother, bin);
	qsort(bin, table->binCount, sizeof(storage), compareBin);
	otherPrint(numLine, bin, table->binCount);
	printf("totaly number of words %d\n",table->binCount);
	free(bin);
	freeSpace(table);
	return 0;
}
