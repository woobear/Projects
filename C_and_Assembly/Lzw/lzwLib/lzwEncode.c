#include <stdlib.h>
#include <sequence.h>
#include <stdio.h>
#include <bitStream.h>
#include <dict.h>
#include <lzw.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Rob Wooner
 */

bool lzwEncode(unsigned int bits, unsigned int maxBits,
               int (*readFunc )(void* context), void* readContext,
               int (*writeFunc)(unsigned char c, void* context), void* writeContext) {
    if (bits < 8 || maxBits > 24 || bits > maxBits) {
        printf("Check your bits or maxbits parameter for encode\n");
        return false;
    }
    BitStream * bitstream = openOutputBitStream(writeFunc, writeContext);
    Dict* dict = newDict(1<<24);
    for (int i = 0; i < 256; i++) {
        insertDict(dict,newSequence(i,1),i);
    }
    char c;
    unsigned int currBits = bits;
    unsigned int currSize = (1<<currBits);
    unsigned int* passCode = (unsigned int*) malloc(sizeof(unsigned int));
    int nextCode = 256;
    Sequence * w = newSequence((readFunc(readContext)),1);
    Sequence * x;
    while ( (c = readFunc(readContext)) != -1) {
        x = copySequenceAppend(w,c);
        if (searchDict(dict,x,passCode)) {
            deleteSequence(w);
            w = x;
        }else {
            searchDict(dict,w,passCode);
            outputBits(bitstream,currBits,*passCode);
            if(nextCode == currSize) {
                if(currBits < maxBits) {
                    currBits++;
                    currSize = (1<<currBits);
                }
            }
            if(nextCode < (1 << maxBits)) {
                insertDict(dict,x, nextCode);
                nextCode += 1;
            }else {
                deleteSequence(x);
            }
            deleteSequence(w);
            w = newSequence(c,1);
        }
    }
    searchDict(dict,w,passCode);
    outputBits(bitstream,currBits,*passCode);
    closeAndDeleteBitStream(bitstream);
    deleteSequence(w);
    deleteDictDeep(dict);
    free(passCode);
    return true;

}
