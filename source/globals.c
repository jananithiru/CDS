#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "bst.h"
#include "cds.h"
struct colDataStore cdsInfo;

void createEmptyRecord(struct dataRecord *newRecord)
{
	int i;
	for( i=0; i < cdsInfo.numCols; i++ )
		newRecord->values[i] = (char *) malloc(sizeof(char)*(cdsInfo.fileregister[i].length+1));
	newRecord->numCols=cdsInfo.numCols;
}

/* Internal function */
static void printAllRecords( struct bstNode *node );

int cds_printRecord( struct dataRecord* record )
{
	int count;

	if( record == NULL ){
		fprintf(stderr, "\nERROR: NULL record given for print\n");
		return PRINT_ERROR;
	}

	for ( count=0; count < cdsInfo.numCols; count++ ){
		printf("%s: ", cdsInfo.fileregister[count].colname);
		printf("%s\t\t", record->values[ count ]);
	}
	printf("\n");
	return 0;
}

int cds_printCollection( LISTCOLLECTION *recordset )
{
	struct node *curr;
	struct dataRecord* record;

	if( recordset == NULL ){
		fprintf(stderr, "\nERROR: NULL recordset given for print\n");
		return PRINT_ERROR;
	}

	printf("Recordset contains %d records\n", recordset->count);
	curr = recordset->head;
	while( curr != NULL ){
		record = (struct dataRecord*) curr->data;
		cds_printRecord(record);
		curr = curr->next;
	}	
	return 0;
}

int cds_printDatabase()
{
	struct bstNode *root = cdsInfo.primaryNdx;

	if( cdsInfo.state == CDS_CLOSED ){
		fprintf(stderr, "\nERROR: Closed database given for print\n");
		return PRINT_ERROR;
	}
	else if( root == NULL ){
		fprintf(stderr, "\nERROR: NULL BST root given for print\n");
		return PRINT_ERROR;
	}

	printf("\n----------------BEGIN PRINTING %s-------------------------\n", cdsInfo.database);
	printAllRecords( root ); 
	printf("\n----------------END PRINTING %s-------------------------\n", cdsInfo.database);
	return 0;
}

/* Internal function */
static void printAllRecords( struct bstNode *node )
{
	int status;
	struct dataRecord *record;

	if ( node == NULL )
		return;

	record = (struct dataRecord *) malloc( sizeof(struct dataRecord) );	

	createEmptyRecord(record);

	status = selectByKey( node->data->key, record );
	/*if( status != 0 ){
		fprintf(stderr, "\nERROR: Unable to get record for key = %s\n", node->data->key);
	}*/
	if(status==0)
		cds_printRecord( record );
	free( record );

	printAllRecords( node->leftChild );
	printAllRecords( node->rightChild );
}

int writeString( FILE *fp, int position, char *str, int maxsize )
{
	char *wstr;

	wstr = (char *) malloc(sizeof(char)*maxsize + 1);
	memset(wstr, '\0', maxsize+1);

	if( fp == NULL || position < 0 || str == NULL || maxsize < 0 ){
		fprintf(stderr, "\nERROR: Invalid arguments given for writeString\n");
		return STRING_WRITE_ERROR;
	}

	if( strlen(str) > maxsize ){
		/* Truncate string */
		fprintf(stderr,"\nWarning: Input string %s is going to be truncated\n",str);
	}

	strncpy(wstr, str, maxsize);

	fseek(fp, position, SEEK_SET);

	/* Do not forget to write the string with '\0'. */
	fwrite(wstr, sizeof(char), maxsize, fp);
	return SUCCESS;
}

/*
When reading, read the actual string length first and then read only that many bytes. 
Do not forget to read the string with '\0'.
*/

char *readString( FILE *fp, int position, int maxsize )
{
	char *str;

	if( fp == NULL || position < 0  || maxsize < 0 ){
		fprintf(stderr, "\nERROR: Invalid arguments given for readString\n");
		return NULL;
	}
	fseek(fp, position, SEEK_SET);
	str = (char *) malloc(sizeof(char)*maxsize + 1);

	/* Do not forget to read the string with '\0'. */
	fread( str, sizeof(char), maxsize, fp );
	return str;
}
