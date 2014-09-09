#include "headers.h"
extern FILE *logfiledesc;
char* convert_to_filename(char *database,char *temp,char *format)
{
	char *fieldname=(char*)malloc(sizeof(char)*(strlen(database)+1+strlen(temp)+strlen(format)+1));
	strcpy(fieldname,database);
	strcat(fieldname,"_");
	strcat(fieldname,temp);
	strcat(fieldname,format);
	return fieldname;
}
//==============================================================================================================
void remove_files(int i)
{
	int k;
	for(k=0;k<i;k++)
	 remove(cdsInfo.fileregister[i].colname);
         	cdsInfo.numCols=0;
}
//==============================================================================================================
int isCreated=NO;
int cds_createDataStore(char *database)
{
	if(isCreated==YES)
		return CREATE_FAIL;
	
	char *temp=(char*)malloc(sizeof(char)*(strlen(database)+5));
	strcpy(temp,database);
	strcat(temp,".sch");


	FILE *fp1=fopen(temp,"r");
	FILE *pndx,*sndx;
	if(fp1==NULL)
		{
			LOG_INFO("No such file! Cannot open the CDS\n");
	  		return CREATE_FAIL;
		}

	char line[120];
	int i=0;
	LOG_INFO("Opened .sch file.\n");

	

	//============================================================================================
	while( fgets(line,sizeof(line),fp1)!=NULL && i<MAX_COL)
	{
		char *temp=strTok(line,":");
		char *size=strTok(NULL,":");
		char *datatype=strTok(NULL,":");
		char *last=strTok(NULL,":");
		char *tempname=(char*)malloc(sizeof(char)*MAX_COL_NAME);

		if(temp!=NULL && size!=NULL && datatype!=NULL && last==NULL)
		{
		//=================================================================================
			
			char *fieldname=convert_to_filename(database,temp,".dat");
			cdsInfo.fileregister[i].fptr=fopen(fieldname,"wb");
			LOG_INFO("Created .dat files\n");
		//=================================================================================
			if(cdsInfo.fileregister[i].fptr==NULL)
			{
				remove_files(i);
				LOG_ERROR("File creation failed! Deleting all other .dat files\n");
	  			return CREATE_FAIL;			
			}
		//=================================================================================
			if(i<2)
			{
				if(i==0)
				{
					char *indexfilename = convert_to_filename(database,temp,".ndx");
					pndx=fopen(indexfilename,"wb");
					cdsInfo.freelist=(struct stack *)malloc(sizeof(struct stack));
					
						
			     		if(stackInit(cdsInfo.freelist)==STACK_SUCCESS)
					{
			     			stackPersist(pndx,cdsInfo.freelist);
						LOG_INFO("Opened .ndx file. Persisted Stack\n");
					}
	
					fclose(pndx);
				}
				if(i==1)
				{
					char *indexfilename=convert_to_filename(database,temp,".ndx");
					sndx=fopen(indexfilename,"wb");
					LOG_INFO("Created secondary .ndx file.\n");
					fclose(sndx);
				}
			}
			i++;
		}
		//=================================================================================
		else
			{
		   	remove_files(i); //remove all files created so far
			LOG_ERROR("File creation failed! Deleting all other .dat files\n");
		   	return CREATE_FAIL;
			}
			free(tempname);
	}// while

	cdsInfo.numCols=i;
	free(temp);
	isCreated=YES;
	return CREATE_SUCCESS;
}

