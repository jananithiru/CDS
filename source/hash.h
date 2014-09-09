/* Header file for implementing hash tables*/


/*
In any function if the return type is int and
it is expected to return the status then,
on failure return 0
on success return 1

*/

#define MAXBUCKETS 100

struct hashTable
{
int numBuckets;
struct llNode *buckets[MAXBUCKETS] ;
};

/* Allocate the memory and initialize the hash table.*/
void hashInit(struct hashTable *hash,int numBuckets);

/*Use your own hash function to calculate the hask value*/
int calcHash( char *key /* or int key; depending on the secondary index type*/);

/*Inserting a given key in a hash table.Return 1 on success and 0 on failure*/
int hashInsert(struct hashTable *hash, struct secondaryIndex*  data);


/*Search for the node and mark as deleted by setting the flag*/
int hashMarkDeleted(struct hashTable *hash, struct secondaryIndex*  detail);

/*Deleting the keys from the hash table.Return 1 on success and 0 on failure*/
int hashDeleteNode(struct hashTable *hash, struct secondaryIndex*  detail);

/*
Searching for the key and create a new linked list containing the data maching the key.
If nothing is found return NULL
*/
struct llNode*  hashSearchCollection (struct hashTable *hash,  char *key /* or int key; depending upon the secondary index type*/ );

/*
Searching for a unique key anf returns a pointer to the secondary index.
If not found return NULL
*/
struct secondaryIndex* hashSearchUnique (struct hashTable *hash,  char *key /* or int key; depending upon the secondary index type*/, int offset );

/*
It loads the hash table from the file on to the main memory.
It would be called in the loadCds() function during your integration
This gets the file pointer fp in read mode. If it finds eof at the current file
pointer then return 0  else 1
*/
int hashLoadFromFile(FILE *fp, struct hashTable *hash );

/*
Persist the hash table to the file after making all the changes.
The file pointer which is passed is in write mode. (In cds integration
the call to this function is done after persistStack function with the same fp).
*/
int hashPersist(FILE *fp,  struct hashTable *hash );
