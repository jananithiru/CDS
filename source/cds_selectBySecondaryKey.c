#include "headers.h"

//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;
extern FILE *logfiledesc;

//return any error code , 0 on success
//LISTCOLLECTION is a LIST which can can take generic type.
//Implemented LISTCOLLECTION will be added shortly

int selectBySecondaryKey(char *key,LISTCOLLECTION *resultset)
{
	struct llNode *list = hashSearchCollection(cdsInfo.secondaryNdx,key);
	char *bstKey;
	if(LC_init(resultset)!=SUCCESS)
		return SELECT_SECONDARY_KEY_FAIL;
	if(list==NULL)
		RECORD_NOTFOUND;
	while(list!=NULL)
	{
		int offset=list->data->offset;
		bstKey=readString(cdsInfo.fileregister[0].fptr,cdsInfo.fileregister[0].length*offset,cdsInfo.fileregister[0].length);
		struct dataRecord *record=(struct dataRecord*)malloc(sizeof(struct dataRecord));
		createEmptyRecord(record);
		if(selectByKey(bstKey,record)==RECORD_FOUND)
 			LC_insertHead(resultset,record);
		list=list->next;
	}
	return SELECT_SECONDARY_KEY_SUCCESS;
}
	

