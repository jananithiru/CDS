//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;

/*
This function adds a new record to the cds
1) check if any key is there in the freelist.
2) if a offset is not available then find the new offset using the dat files
3) create a new primary index with the key and the offset and try inserting
   into the BST
4) If not successful then push the offset (if it was poped out earlier) to
   the stack and return failure
5) If successfull then create a secondary entry and inset it to the hash.
   if not successfull then revert all the changes
6) If successful then for each dat files seek to the offset position and
   write the respective column value and then 0 on success
7) If not then revert all the changes and remove the things from the indices
   too and return a specific error
*/
int cds_addUniqueRecord(struct dataRecord *record);
