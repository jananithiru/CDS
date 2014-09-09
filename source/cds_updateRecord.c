#include "headers.h"

//This is the global variable defined in globals.c and to be
//used by various files.
extern FILE *logfiledesc;
extern struct colDataStore cdsInfo;

//key is the bst key. newRecord has the new updated values.
int updateRecord(char* key,struct dataRecord *newRecord)
{
	struct primaryIndex *bstData;
	
	if((bstData=bstSearchNode(cdsInfo.primaryNdx,key))==NULL)	
		return UPDATE_FAIL;
		
	struct dataRecord *oldRecord=(struct dataRecord*)malloc(sizeof(struct dataRecord));
	createEmptyRecord(oldRecord);
	selectByKey(key,oldRecord);
	
	if(cds_deleteByKey(key)==DELETE_KEY_FAIL)
		return UPDATE_FAIL;
		
	if(cds_addUniqueRecord(newRecord)==ADDKEY_FAIL)
		return UPDATE_FAIL;
	return UPDATE_SUCCESS;
}
	
	
	/*struct primaryIndex *bstData;
	if((bstData=bstSearchNode(cdsInfo.primaryNdx,key))==NULL)
		return UPDATE_FAIL;
		
	int offset=bstData->offset;
	
	struct dataRecord *oldRecord=(struct dataRecord*)malloc(sizeof(struct dataRecord));
	createEmptyRecord(oldRecord);
	selectByKey(key,oldRecord);
	
	struct secondaryIndex *hashData=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));
	strcpy(hashData->key,oldRecord->values[1]);
	hashData->offset=offset;
	hashData->flag='0';
	
	if(hashMarkDeleted(cdsInfo.secondaryNdx,hashData)!=HASH_SUCCESS)
		return UPDATE_FAIL;
		
	struct secondaryIndex *hashData1=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));
	strcpy(hashData1->key,newRecord->values[1]);
	hashData1->offset=offset;
	hashData1->flag='0';
	
	if(hashInsert(cdsInfo.secondaryNdx,hashData1)!=HASH_SUCCESS)
		return UPDATE_FAIL;//Also unmark it in hash
		
	int i=0;
	for(i=0;i<cdsInfo.numCols;i++)
		writeString(cdsInfo.fileregister[i].fptr,cdsInfo.fileregister[i].length*offset,newRecord->values[i],cdsInfo.fileregister[i].length);
	return UPDATE_SUCCESS;
}*/
	
