#include <sequence.h>
#include <bitStream.h>
#include <lzw.h>
#include <stdlib.h>
#include <stdio.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Rob Wooner
 */

bool lzwDecode(unsigned int bits, unsigned int maxBits,
               int (*readFunc )(void* context), void* readContext,
               int (*writeFunc)(unsigned char c, void* context), void* writeContext) {
    if (bits < 8 || maxBits > 24 || bits > maxBits) {
        printf("Check your bits or maxbits parameter for decode\n");
        return false;
    }
    Sequence **seqArray;
    seqArray = malloc(sizeof(Sequence*) * 1<<maxBits);
    for (int i = 0; i < 256; i++) {
        seqArray[i] = newSequence((char) i, 1);
    }
    unsigned int currBits = bits;
    unsigned int currSize = (1<<currBits);
    unsigned int* previousCode = (unsigned int*) malloc(sizeof(unsigned int));
    unsigned int* currentCode = (unsigned int*) malloc(sizeof(unsigned int));
    int nextCode = 256;
    unsigned char c;
    BitStream * bitstream = openInputBitStream(readFunc,readContext);
    Sequence * w;
    readInBits(bitstream, currBits, previousCode);
    outputSequence(seqArray[*previousCode],writeFunc, writeContext);
    if(nextCode == currSize) {
        if(currBits < maxBits) {
            currBits++;
            currSize = (1<<currBits);
        }
    }
    while (readInBits(bitstream,currBits,currentCode)) {
        if ( nextCode > *currentCode) { 
            c = (*(seqArray[*currentCode]->firstByte));
        } else {
             c = (*(seqArray[*previousCode]->firstByte));
        }
        if (nextCode < (1<<maxBits)) { 
            w = copySequenceAppend(seqArray[*previousCode],c);
            seqArray[nextCode++] = w;
        }
        outputSequence(seqArray[*currentCode],writeFunc,writeContext);
        *previousCode = *currentCode;
        if(nextCode >= currSize) {
            if(currBits < maxBits) {
                currBits++;
                currSize = (1<<currBits);
            }
        }
    }
    for (int i = 0; i < nextCode; i++) {
        deleteSequence(seqArray[i]);
    }
    free(seqArray);
    closeAndDeleteBitStream(bitstream);
    free(previousCode);
    free(currentCode);
    // deleteSequence(w);


    return true;
}
