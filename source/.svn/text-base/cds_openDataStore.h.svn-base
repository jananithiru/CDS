//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;


/*
  The function takes a database name(without any extension) and reads the corresponding sch file
  and parses it to find the ndx files. Then it opens the primary and secondary files and builds the
  freelist,bst,hashtable and closes the ndx file. This also needs to parse the sch file to get the
  column names and store the column names in the cdsInfo.fileregister[i].colname and open the
  corresponding column dat files in wb+ mode and assigns the cdsInfo.fileregister[i].fptr

  In short this function populates the different structures and the cdsInfo variable.
  return 0 on success and 1 on failure to load and 2 if a datastore is already open and without
  unload datastore being called this function is called once again.

*/

int cds_openDataStore(char *database);
