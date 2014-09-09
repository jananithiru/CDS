#include "headers.h"
extern FILE *logfiledesc;
//This is the global variable defined in globals.c and to be
//used by various files.
extern struct colDataStore cdsInfo;
 //colname is the columnname as in .sch. If the column is a int then type cast the char to int.
int selectByColumnName(char *colname,char *value,LISTCOLLECTION *resultset)
{
	if(cdsInfo.state==CDS_CLOSED)
		return SELECT_COLNAME_FAIL;
	int i;
	int flag=0;

	//Looping through to find out whether or not such a column is present
	for(i=0;i<cdsInfo.numCols;i++)
	{
		if(strcmp(cdsInfo.fileregister[i].colname,colname)==0)
		{
			flag=1;
			break;
		}
	}

	if(flag==0) return SELECT_COLNAME_FAIL; //There is no such colname

	fseek( cdsInfo.fileregister[i].fptr , 0 , SEEK_SET );
	
	
	int offset=0;
	if(LC_init(resultset)!=SUCCESS)
		return SELECT_COLNAME_FAIL;
		
	char *fileValue,*primaryKey;
	while(!feof(cdsInfo.fileregister[i].fptr))
	{
		fileValue=readString(cdsInfo.fileregister[i].fptr,cdsInfo.fileregister[i].length*offset,cdsInfo.fileregister[i].length);
		if(strcmp(fileValue,value)==0)
		{
			primaryKey=readString(cdsInfo.fileregister[0].fptr,cdsInfo.fileregister[0].length*offset,cdsInfo.fileregister[0].length);
			struct dataRecord *record=(struct dataRecord*)malloc(sizeof(struct dataRecord));
			createEmptyRecord(record);
			if(selectByKey(primaryKey,record)==RECORD_FOUND)
 				LC_insertHead(resultset,record);
		}
		offset++;
	}
	return SELECT_COLNAME_SUCCESS;
}



	

	
	
