//Robert Wooner
//CS261
//Assignment 4
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"

storage* createBox(char *key, void *value) {
	storage* box = (storage*)malloc(sizeof(storage));
	box->key = key;
	box->value = value;
	box->next = NULL;
	return box;
}

dict *newTable() {
	storage *store = (storage*)malloc(sizeof(storage)*TABLE_SIZE);
	dict *newTable = (dict*)malloc(sizeof(dict));
	for (int i = 0; i < TABLE_SIZE; i++){
		store[i].key = NULL;
		store[i].value = NULL;
		store[i].next = NULL;
	}
	newTable->collCount = 0;
	newTable->binCount = 0;
	newTable->resize = 1;
	newTable->box = store;
	newTable->size = TABLE_SIZE;
	return newTable;
}


unsigned long getHashed(char *key, int size) {
	unsigned long	hash = 5381;
	int c;
	while ((c = *key++)){ 
		hash = ((hash << 5) + hash) + c;
	}
	return hash % size;
}

void insert(char *key, void *value, dict *table) {
	int h = getHashed(key, table->size);
	storage *bin = &table->box[h];
	if (bin->key  == NULL) {
		bin->key = key;
		bin->value = value;
		bin->next = NULL;
	  table->binCount++;	
		return;
	}
	while (1) {
		if (bin->next == NULL) {
			if (strcmp(bin->key,key) == 0) {
				int *count = (int*)bin->value;
				free(key);
				free(value);
				(*count)+=1;
				return;
			}else {
				storage *anotherBox = createBox(key,value);
				bin->next = anotherBox;
				table->binCount +=1;	
				int *count = (int*)bin->value;
				(*count) = 1;
				table->collCount++;
				return;
			}
		}
		if (strcmp(bin->key,key) == 0) {
			int *count = (int*)bin->value;
			free(key);
			free(value);
			 (*count)++;
					return;
			}else {
				bin = bin->next;
			}
		}
}

void upgrade(dict *table) {
	storage *newStore = (storage*)malloc(sizeof(storage)*(table->size*3));
	storage *oldStore = table->box;
	storage *temp;
	table->binCount = 0;
	int oldSize = table->size;
	table->size = table->size*3;
	for (int i = 0; i < table->size; i++){
		newStore[i].key = NULL;
		newStore[i].value = NULL;
		newStore[i].next = NULL;
	}
	table->box = newStore;
	for ( int i = 0; i < oldSize; i++) {
		temp = &oldStore[i];
		if (temp->key == NULL) {
			continue;
		}else {
			while (1){
				if (temp == NULL){
					break;
				}else {
				insert(temp->key, temp->value, table);
				temp = temp->next;
				}
			}
		}
	}
	for (int i = 0; i < oldSize; i++){
		temp = &oldStore[i];
		if (temp->next != NULL){
			freeB(temp->next);
		}
	}
	free(oldStore);
}

void *boxSearch(char *key, dict *table) {
	int h = getHashed(key, table->size);
	storage *bin = &table->box[h];
	while (bin != NULL) {
	 if(bin->key == NULL){
		 fprintf(stderr, "There is nothing in this bin");
	}else if (strcmp(bin->key,key) == 0) {
			return bin->value;
		}else {
			bin = bin->next;
		}
	}	
	fprintf(stderr,"Key was not found, soorry boot that");
	return 0;
}

void otherPrint(int numLine, storage *arr,int bincount) {
	if (numLine == 0){
		for (int i = 0; i < bincount; i++){
			if (arr[i].key != NULL){
				printf("key is %s, value is %10d\n",arr[i].key, *((int*)arr[i].value));  
			}else {
				return;
			}
		}
	}
	for (int i = 0 ; i < numLine; i++){
  	printf("key is %s, value is %10d\n",arr[i].key, *((int*)arr[i].value));  
	}
}


void applylist(dict *table,void (*func)(char *key, void *value, storage *list), storage *list) {
	storage *temp;
	for (int i = 0; i < table->size ; i++) {
		temp = &table->box[i];
		while (temp != NULL) {
			if (temp->key != NULL){
				func(temp->key,temp->value,list);
				temp = temp->next;
			}else { 
			  break;
			}
		}
	}
}

void makeAnother(char *key, void *value, storage *list) { 
	int i  = 0;
	while (1) {
		if (list[i].key != NULL){
			i++;
		}else {
			list[i].key = key;
			list[i].value = value;
			return;
		}
 }
}

int	compareBin(const void *bina, const void *binb) {
    storage *bin = (storage*) bina;
    storage *bin1 = (storage*) binb;
    return (*((int*)bin1->value) - *((int*)bin->value));
}

void freeB(storage *box){
	if (box->next != NULL){
		freeB(box->next);
	}
	free(box);
}
 
void freeT(storage *box){ 
    if (box->next == NULL){
       return;
    }
		freeT(box->next);
		free(box->key);
		free(box->value);
		free(box);
}

void freeSpace(dict *table){ 
    int i = 0;
    while (i < table->size){
			if (table->box[i].next != NULL){
      freeT(table->box[i].next);
			free(table->box[i].key);
			free(table->box[i].value);
			} else if (table->box[i].key != NULL){
				free(table->box[i].key);
				free(table->box[i].value);
    }
			i++;
		}
    free(table->box);
    free(table);
}


