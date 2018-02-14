#include <stdlib.h>
#include <stdio.h>
#include <dict.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Rob Wooner
 */
// creates new dictionary based on hashsize
Dict* newDict(unsigned int hashSize) {
    Dict * new_dict =(Dict*) malloc(sizeof(Dict));
    new_dict->buckets = (buckets*) malloc(sizeof(buckets)*hashSize);
    new_dict->size = hashSize;
    for(int i = 0; i < hashSize; i++) {
        new_dict->buckets[i].code = 0;
        new_dict->buckets[i].key = NULL;
        new_dict->buckets[i].next = NULL;
    }
    return new_dict;
}

//deletes the dict...deep
void deleteDictDeep(Dict* dict) {
    for(int i = 0; i < dict->size; i++) {
        buckets * tempBucket = &(dict->buckets[i]);
        if(tempBucket->next != NULL) {
            deleteBuckets(tempBucket->next);
            deleteSequence(tempBucket->key);
        }else {
            if(tempBucket->key != NULL) {
                deleteSequence(tempBucket->key);
            }
        }
    }   
    free(dict->buckets);
    free(dict);
}

//helper function to recursively frees the linked list
void deleteBuckets(buckets * tempBucket) {
    if(tempBucket->next != NULL) { 
        deleteBuckets(tempBucket->next);
    }
    deleteSequence(tempBucket->key);
    free(tempBucket);
} 

//hash function
static unsigned long hashTag(Sequence * key) {
    unsigned long h = 0;
    int i;
    for (i = 0; i < key->length; i++) {
        h ^= (h << 5) + (h >> 2) + key->firstByte[i];
    }
    return h;
}
//searches the dictionary by comparing sequences 
bool searchDict(Dict* dict, Sequence* key, unsigned int* code) {
    unsigned long h = hashTag(key) % dict->size;
    buckets * temp = &(dict->buckets[h]);
    while (temp->key != NULL) {
        if(identicalSequences(temp->key, key)) {
            *code = temp->code;
            return true;
        } else {
            if(temp->next != NULL) {
                temp = temp->next;
            } else {
                break;
            }
                
        }
    }
    return false;
}


void insertDict(Dict* dict, Sequence* key, unsigned int code) {
    unsigned long h = hashTag(key) % dict->size;
    if (dict->buckets[h].key == NULL) {
        dict->buckets[h].key = key;
        dict->buckets[h].code = code;
        dict->buckets[h].next = NULL;
    } else {
        buckets * temp = &(dict->buckets[h]);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = (buckets*) malloc(sizeof(buckets));
        temp = temp->next;
        temp->key = key;
        temp->code = code;
        temp->next = NULL;
    }

}
