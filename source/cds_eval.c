#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cds.h"

int cds_createDataStore(char *database);//This is the global variable defined in globals.c and to be
int cds_addUniqueRecord(struct dataRecord *record);
int cds_deleteByKey(char * key);/*Structures to be used in CDS*/
int cds_printRecord( struct dataRecord* record );
int cds_printCollection( LISTCOLLECTION* recordset );
int cds_printDatabase();
int selectByColumnName(char *colname,char *value,LISTCOLLECTION *resultset);
int selectByKey(char* key,struct dataRecord* record);
int selectBySecondaryKey(char *key, LISTCOLLECTION *resultset);
int cds_unloadDataStore();
int updateRecord(char *key, struct dataRecord *newRecord);

/* Local functions */
int showmenu();
struct dataRecord *makeRecord( char *key, char *secondarykey );

#define logarg(msg, arg) fprintf(logfile, "\n%s: %s %s", __FILE__, msg, arg); \
	fprintf(stdout, "\n%s: %s %s", __FILE__, msg, arg);

FILE *logfiledesc;
FILE *logfile;

main()
{
	int choice, status;
	char dbname[30], col[30];
	struct dataRecord *record, *selrecord;
	LISTCOLLECTION *recordset;
	char *value=(char*)malloc(sizeof(char)*100);
	int currtime = time( NULL );
	char key[30],secondarykey[30];
	srand ( time(NULL) );

	logfile = (FILE*) fopen("cdseval.log", "a");
	logfiledesc = (FILE*) fopen("CDS_AllFiles.log", "a");
	if( logfile == NULL ){
		fprintf(stderr, "Unable to open cdseval.log in write mode");
		exit(1);
	}

	//logarg("LOG STARTED AT ",ctime(&currtime));
	strcpy(dbname, "");
	while( 1 ){
		choice = showmenu();
		switch(choice){
			case 0: /* Close Database and exit */
				status = cds_unloadDataStore();
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to unload database - ", dbname);
					exit(1);
				}
				else{
					logarg("++++++++++ SUCCESS: Database unloaded - ", dbname);
					exit(0);
				}
			break;
			case 1: /* Create Database */
				printf("Enter database name: ");
				scanf("%s", dbname);
				status = cds_createDataStore( dbname );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to create database - ", dbname);
				}
				else{
					logarg("++++++++++ SUCCESS: Database created - ", dbname);
				}
			break;
			case 3: /* Open Database */
				printf("Enter database name: ");
				scanf("%s", dbname);
				status = cds_openDataStore( dbname );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to open database - ", dbname);
				}
				else{
					logarg("++++++++++ SUCCESS: Database open - ", dbname);
				}
			break;
			case 2: /* Print database */
				status = cds_printDatabase();
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to print database - ", dbname);
				}
				else{
					logarg("++++++++++ SUCCESS: Database printed - ", dbname);
				}
			break;
			case 4: /* Add record */
				printf("Enter key for a random record: ");
				scanf("%s", key);
				printf("Enter secondary key for a random record: ");
				scanf("%s", secondarykey);
				if(strlen(key)<30 && strlen(secondarykey)<30)
				{
					record = makeRecord( key, secondarykey );
					status = cds_addUniqueRecord( record );
				}
				else
					status=!(SUCCESS);
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to add record with key - ", key);
				}
				else{
					logarg("++++++++++ SUCCESS: Added record with key - ", key);
				}
			break;
			case 5: /* Modify record */
				printf("Enter key of record to be modified: ");
				scanf("%s", key);
				strcpy(secondarykey, "somerandomvalue");
				record = makeRecord( key, secondarykey );
				status = updateRecord( key, record );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to modify record with key - ", key);
				}
				else{
					logarg("++++++++++ SUCCESS: Modified record with key - ", key);
				}
			break;
			case 6: /* Delete by key */
				printf("Enter key of record to be deleted: ");
				scanf("%s", key);
				status = cds_deleteByKey( key );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to delete record with key - ", key);
				}
				else{
					logarg("++++++++++ SUCCESS: Deleted record with key - ", key);
				}
			break;
			case 7: /* Select by key */
				printf("Enter key of record to be selected: ");
				scanf("%s", key);
				
				selrecord = (struct dataRecord *) malloc( sizeof(struct dataRecord) );

				createEmptyRecord(selrecord);
				status = selectByKey( key, selrecord );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to select record with key - ", key);
				}
				else{
					status = cds_printRecord(selrecord);
					if( status != SUCCESS ){
						logarg("---------- FAILURE: Unable to print record with key - ", key);
					}
					else{
						logarg("++++++++++ SUCCESS: Selected and printed record with key - ", key);
					}
				}
				free(selrecord);
			break;
			case 8:
				printf("Enter secondary key of records to be selected: ");
				scanf("%s", key);
				if(cdsInfo.secondaryNdx==NULL)
					printf("What the hell is this\n");
				displayHash(cdsInfo.secondaryNdx);
				recordset = (LISTCOLLECTION *) malloc( sizeof(LISTCOLLECTION) );
				status = selectBySecondaryKey( key, recordset );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to select record with key - ", key);
				}
				else{
					status = cds_printCollection(recordset);
					if( status != SUCCESS ){
						logarg("---------- FAILURE: Unable to print records with secondary key - ", key);
					}
					else{
						logarg("++++++++++ SUCCESS: Selected and printed records with secondary key - ", key);
					}
				}
				free(recordset);
			break;
			case 9:
				printf("Enter filter column name: ");
				scanf("%s", col);
				
				printf("Enter filter column value: ");
				scanf("%s", value);
				
				recordset = (LISTCOLLECTION *) malloc( sizeof(LISTCOLLECTION) );
				status = selectByColumnName( col, value, recordset );
				if( status != SUCCESS ){
					logarg("---------- FAILURE: Unable to select by column name - ", col);
				}
				else{
					status = cds_printCollection(recordset);
					if( status != SUCCESS ){
						logarg("---------- FAILURE: Unable to print records with column filter on  - ", col);
					}
					else{
						logarg("++++++++++ SUCCESS: Selected and printed records with column filter on - ", col);
					}
				}
				free(recordset);
			break;
			default:
				printf("Invalid input... enter value between 0-9\n"); 
			break;
		}
	}
}

struct dataRecord *makeRecord( char *key, char *secondarykey )
{
	int count;
	int randvalue;
	struct dataRecord *record = (struct dataRecord *) malloc( sizeof(struct dataRecord) );
	record->numCols = cdsInfo.numCols;

	for( count = 0; count < MAX_COL; count++ ){
		record->values[count] = (char *) malloc(sizeof(char)*30);
	}
	//createEmptyRecord(record);

	strcpy(record->values[0], key);
	strcpy(record->values[1], secondarykey);
	for( count = 2; count < record->numCols; count++ ){
		randvalue = rand() % 100 + 1;
		sprintf(record->values[count], "Some-random-string-%d", randvalue);
	}
	return record;
}

int showmenu()
{
	int choice = 0;

	printf("\nCDS Evaluation Program\n");
	printf("======================\n");
	
	printf("\t0) Exit\n\n");
	printf("\t1) Create Database\n\n");
	printf("\t2) Print Database\n\n");
	printf("\t3) Open Database\n\n");
	printf("\t4) Add Unique Record\n\n");
	printf("\t5) Modify Record\n\n");
	printf("\t6) Delete By Key\n\n");
	printf("\t7) Select By Key\n\n");
	printf("\t8) Select By Secondary Key\n\n");
	printf("\t9) Select By Column Name\n\n");

	printf("ENTER YOUR CHOICE (0-9): ");
	fflush(stdin);
	scanf("%d", &choice);

	return choice;
}

