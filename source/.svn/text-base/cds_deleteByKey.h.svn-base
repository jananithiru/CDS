//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;

/*
This function deltes a record from the cds
1) First selects the record using selectByKey.This is get the secondary key
2) get the primary Index value inorder to get the offset value
3) mark the bst node for deletion
4) mark the hash node for deletion
5) push the offset to the freelist
*/
int cds_deleteByKey(char * key);
