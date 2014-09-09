#include "headers.h"

extern struct colDataStore cdsInfo;
extern FILE *logfiledesc;

int selectByKey(char *key,struct dataRecord *record)
{
	struct primaryIndex *bstData=bstSearchNode(cdsInfo.primaryNdx,key);
		
	
	//Either such a node doesnot exist or exists but its marked for deleted
	if(bstData==NULL || bstData->flag=='1')
		{
		LOG_INFO("Didn't find Key\n");
		return RECORD_NOTFOUND;
		}
	LOG_INFO("Found record for requested key \n");

	int offset = (bstData->offset);

	int flag=0;

	int i;
	char *fileValue;
	for(i=0;i<cdsInfo.numCols;i++)
	{
		fileValue=readString(cdsInfo.fileregister[i].fptr,cdsInfo.fileregister[i].length*offset,cdsInfo.fileregister[i].length);
		strcpy(record->values[i],fileValue);
	}

	return RECORD_FOUND;
}

