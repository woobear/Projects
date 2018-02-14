#include <stdlib.h>
#include <sequence.h>
#include <stdio.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Rob Wooner
 */
//creates new sequence
Sequence* newSequence(unsigned char firstByte, int length) {
    Sequence * sequence = (Sequence*) malloc(sizeof(Sequence));
    sequence->firstByte = (char *) malloc(sizeof(firstByte));
    *(sequence->firstByte) = firstByte;
    sequence->length = length;
    return sequence;
}

//free's sequence 
void deleteSequence(Sequence* sequence) {
    free(sequence->firstByte);
    free(sequence);
} 

//copys intiial sequences and appends to newSequence along with the additional bit
Sequence* copySequenceAppend(Sequence* sequence, unsigned char addByte) {
    Sequence * newSequence = (Sequence*) malloc(sizeof(Sequence));
    newSequence->firstByte = (char *) malloc(sizeof(char) * sequence->length+1);
    newSequence->length = sequence->length+1;
    for (int i = 0; i < sequence->length; i++) {
         newSequence->firstByte[i] = sequence->firstByte[i];
    }
    newSequence->firstByte[newSequence->length-1] = addByte;
    return newSequence;
}

//writes sequences to file
void outputSequence(Sequence* sequence,
                    int (*writeFunc)(unsigned char c, void* context), void* context) {
        for (int i = 0; i < sequence->length; i++ )  {
            writeFunc(sequence->firstByte[i], context);
        }
}

//compares sequences 
bool identicalSequences(Sequence* a, Sequence* b) {
    if (a->length == b->length) {
        for(int i = 0; i < a->length; i++){
            if(a->firstByte[i] == b->firstByte[i]) {
                continue;
            }else {
                return false;
            }    
        }
        return true;   
    }else {
        return false;
    }
}
