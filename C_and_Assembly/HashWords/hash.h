//Robert Wooner
//assignment 4
#ifndef HASH_H
#define HASH_H
#define TABLE_SIZE 10
#define MAX_WORD_SIZE 256

typedef struct storage {
	char *key;
	void *value;
	struct storage *next;
}storage;

typedef struct dict {
	storage *box;
	int size;
	double resize;
	int binCount;
	int collCount;
}dict;

//creates a box for storing in the hashtable
storage *createBox(char *key, void *value);

//makes table
dict *newTable();

//helps free stuff
void freeB(storage *box);

//inserts words read from file into the harsh table
void insert(char *key, void *value, dict *table);

//searchs for key in hashtable
void *boxSearch(char *key, dict *table);

//frees up malloced space
void freeSpace(dict *table);

//helper for freeSpace 
void freeT(storage *box);

//hashes the key for hashtable
unsigned long getHashed(char *key, int size);

void makeAnother(char *key, void *vlaue, storage *list);
//prints
void otherPrint(int numLine, storage  *arr, int bincount);

//takes the hashtable and function you calling on the hashtable
//applies function to the table
void applylist(dict *table, void(*func)(char *key, void *value, storage *list),storage *list);

//helper function
int compareBin(const void *bina, const void *binb);

//resizes the hashtable
void upgrade(dict *table);
#endif
