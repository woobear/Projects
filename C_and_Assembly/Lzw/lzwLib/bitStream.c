#include <stdlib.h>
#include <stdio.h>
#include <bitStream.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Rob Wooner
 */

//mallocs bitstream for reading in bits
BitStream* openInputBitStream(int (*readFunc)(void* context), void* context) {
    BitStream* new_bitStream = (BitStream*) malloc(sizeof(BitStream));
    new_bitStream->input = NULL;
    new_bitStream->readFunc = readFunc;
    new_bitStream->writeFunc = NULL;
    new_bitStream->context = context;
    new_bitStream->buffer = 0;
    new_bitStream->bufferSize = 0;
    return new_bitStream;
}

//mallocs bitstream to write bits
BitStream* openOutputBitStream(int (*writeFunc)(unsigned char c,void* context),void* context) {
    BitStream* new_bitStream = (BitStream*) malloc(sizeof(BitStream));
    new_bitStream->input = NULL;
    new_bitStream->readFunc = NULL;
    new_bitStream->writeFunc = writeFunc;
    new_bitStream->context = context;
    new_bitStream->buffer = 0;
    new_bitStream->bufferSize = 0;
    return new_bitStream;
}

void closeAndDeleteBitStream(BitStream* bs) {
    if(bs->bufferSize > 0 && bs->readFunc == NULL){
        bs->writeFunc((bs->buffer << (8 - bs->bufferSize)),bs->context);
    }
    free(bs);
}


void outputBits(BitStream* bs, unsigned int nBits, unsigned int code) {
    bs->buffer <<= nBits;
    //add code to least significant bits
    bs->buffer += code;
    bs->bufferSize += nBits;
    while(bs->bufferSize >= 8) {
        //write new code as long as there is something to write
        bs->writeFunc((bs->buffer>>(bs->bufferSize-8)),bs->context);
        bs->bufferSize -= 8;
    }
 }

bool readInBits(BitStream* bs, unsigned int nBits, unsigned int* code) {
    int store = 0;
    while(bs->bufferSize < nBits){
        if((store = bs->readFunc(bs->context)) == -1 ){
            return false;
        }
        //add to the buffer as it read in the bits
        bs->buffer = (bs->buffer << 8);
        bs->buffer += store;
        bs->bufferSize += 8;
    }
    //shift the bits back and give them back as codes 
    *code = bs->buffer >> (bs->bufferSize - nBits);
    bs->bufferSize -= nBits;
    bs->buffer = bs->buffer & ((1 << (bs->bufferSize)) - 1);
    return true;
}
