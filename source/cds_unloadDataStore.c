#include "headers.h"
extern struct colDataStore cdsInfo;
extern FILE *logfiledesc;
char* convert_to_filename(char *database,char *temp,char *format);

void print_record(struct dataRecord fd);


int cds_unloadDataStore()
{
	
	FILE *pndx,*sndx;

	char *temp0=(char *)malloc(sizeof(char)*(strlen(cdsInfo.database)+5));
	strcpy(temp0,cdsInfo.database);
	strcat(temp0,".sch");
	FILE *scf;//schema file
	scf=fopen(temp0,"rb");

	if(scf==NULL)
	{
	   LOG_ERROR("File doesn't exist\n");
	   return UNLOAD_FAIL;
	}

	//opening primary and secondary index file in write mode

	char *line = (char *)malloc(sizeof(char)*80);
	fgets(line,80,scf);
	char *temp=strtok(line,":");
	char *indexfilename=convert_to_filename(cdsInfo.database,temp,".ndx");    	
	pndx=fopen(indexfilename,"wb");
	
	if(pndx==NULL)
	{
	   LOG_ERROR("Primary .ndx file doesn't exist\n");
	   return UNLOAD_FAIL;
	}
	fgets(line,80,scf);
	char *temp1=strtok(line,":");
	char *indexfilename1=convert_to_filename(cdsInfo.database,temp1,".ndx");    	
	sndx=fopen(indexfilename1,"wb");
	
	if(sndx==NULL)
	{
	   LOG_ERROR("Secondary .ndx file doesn't exist\n");
	   return UNLOAD_FAIL;
	}

	if(cdsInfo.state == CDS_CLOSED)
		{
			LOG_ERROR("CDS already CLOSED\n");
			return CDS_ALREADYCLOSED ;
		}
	//Persisting stack and bst
	if(stackPersist(pndx,cdsInfo.freelist)==STACK_FAIL)
	{
	   LOG_ERROR("Did NOT persist freelist\n");
	   return UNLOAD_FAIL;
	}
	LOG_INFO("Persisted freelist\n");	
	
	if(bstPersistNodes(cdsInfo.primaryNdx,pndx)==BST_FAIL)
	{
	   LOG_ERROR("Didn't persist BST\n");
	   return UNLOAD_FAIL;
	}
	LOG_INFO("Persisted BST\n");
	//Persisting hash table
	if(hashPersist(sndx,cdsInfo.secondaryNdx)==HASH_FAIL)
	{
	   LOG_ERROR("Didn't persist Hash Table\n");
	   return UNLOAD_FAIL;
	}
	LOG_INFO("Persisted Hash Table\n");
	//closing primary and secondary index files
	fclose(pndx);	
	fclose(sndx);
	int i;
	for(i=0;i<cdsInfo.numCols;i++)
		fclose(cdsInfo.fileregister[i].fptr);
		
	// de-allocating all in memory structures(hash and bst)
	freeTree(cdsInfo.primaryNdx);
	freeHash(cdsInfo.secondaryNdx);
	
	// de-allocating all pointer variables 
	free(cdsInfo.database);
	cdsInfo.state = CDS_CLOSED;
	LOG_INFO("Successfully unloaded the CDS, closed all file pointers and populated the cdsInfo variable?\n");
	return UNLOAD_SUCCESS;

}

