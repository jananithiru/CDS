#include "headers.h"

void createRecord(struct dataRecord *fd,int ,char* fname,int ftype,char *pilotname,char *copilotname)
{
	fd->FlightNo=fno;
	strcpy(fd->FlightName,fname);
	fd->FlightType=ftype;
	strcpy(fd->PilotName,pilotname);
	strcpy(fd->CoPilotName,copilotname);
}

void main()
{

	
	//logfiledesc = fopen("logfile.txt","a");
	//cds_createDataStore("Rama");
	cds_openDataStore("Rama");

		
	struct FlightData f1,f2,f3,f4,f5,f6,f7;
	createRecord(&f7,7,"F1",1,"P1","C7");
	createRecord(&f1,1,"F1",1,"P1","C1");
	createRecord(&f2,2,"F2",0,"P2","C2");
	createRecord(&f3,3,"F3",1,"P3","C3");
	createRecord(&f4,4,"F4",0,"P4","C4");
	createRecord(&f5,5,"F5",0,"P5","C5");
	createRecord(&f6,6,"F6",1,"P6","C6");

	cds_addUniqueRecord(f1);
	cds_addUniqueRecord(f2);
	cds_addUniqueRecord(f3);
	cds_addUniqueRecord(f4);
	cds_addUniqueRecord(f5);
	cds_addUniqueRecord(f7);

	if(updateRecord(2,&f6)==UPDATE_SUCCESS)
	{
		selectByKey(f6.FlightNo,&f7);
		print_record(f7);
	}
	printf("After updating....\n");
	printf("The Complete Table...\n");
	int i=0;
	for(i=1;i<7;i++)
	{
		if(selectByKey(i,&f1)==RECORD_FOUND)
		print_record(f1);
		else
			printf("%d not found\n",i);
	}

	LISTCOLLECTION *lcfno=(LISTCOLLECTION *)malloc(sizeof(LISTCOLLECTION));
	selectByColumnName("FlightNo","1",lcfno);
	printf("Selecting by ColumnName:FlightNo\n");
	print_list(lcfno);

	LISTCOLLECTION *lcfname=(LISTCOLLECTION *)malloc(sizeof(LISTCOLLECTION));
	selectByColumnName("FlightName","F3",lcfname);
	printf("Selecting by ColumnName:FlightName\n");
	print_list(lcfname);


	LISTCOLLECTION *lctype=(LISTCOLLECTION *)malloc(sizeof(LISTCOLLECTION));
	selectByColumnName("FlightType","1",lctype);
	printf("Selceting by column name:FlightType\n");
	print_list(lctype);
	
	LISTCOLLECTION *lcpname=(LISTCOLLECTION *)malloc(sizeof(LISTCOLLECTION));
	selectByColumnName("PilotName","P3",lcpname);
	printf("Selecting by ColumnName:PilotName\n");
	print_list(lcpname);

	LISTCOLLECTION *lccpname=(LISTCOLLECTION *)malloc(sizeof(LISTCOLLECTION));
	selectByColumnName("CoPilotName","C4",lccpname);
	printf("Selecting by ColumnName:CoPilotName\n");
	print_list(lccpname);

	printf("Selecting by secondary key....\n");
	

	LISTCOLLECTION *lc1=(LISTCOLLECTION *)malloc(sizeof(LISTCOLLECTION));
	selectBySecondaryKey("F1",lc1);
	print_list(lc1);

	cds_unloadDataStore();
	
}
















