//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;

/*
returns 0 on success, 1 on general failure and 2 if no record is found for the key
1) gets the primary node
2) moves to each dat files and populates the coulmn value
3) store the record in the variable 'record'
4) the getnode return NULL then return NULL

*/
int selectByKey(char * key,struct dataRecord *record);
