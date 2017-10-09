//Robert Wooner
//Assignment 9
//CS261
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 30

int strgt(char *s1, char *s2);

int main (int argc, char *argv[] ) {
	int num;
	char a[BUFFER];
	char b[BUFFER];
	printf("Enter string 'a': \n");
	fgets(a, BUFFER, stdin);
	printf("Enter string 'b': \n");
	fgets(b, BUFFER, stdin);
	num = strgt(a, b);
	if(num == 0) {
		printf("False, string 'a' is not greater than string 'b'\n");
	}else {
	  printf("True, string 'a' is greater than string 'b'\n");
	}
}
