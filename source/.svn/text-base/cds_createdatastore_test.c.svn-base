//Testing cds_createdatastore
#include "cds_createdatastore.c"
void test_valid_database_name();
void test_invalid_database_name();
void test_empty_sch_file();
void test_improper_format();

void test_valid_database_name()
{
	if(cds_createDataStore("FlightInfo")==0)
		printf("creating all files was successful\n");
	else
		printf("creating all files was not successful\n");
}

void test_invalid_database_name()
{
	if(cds_createDataStore("invalid")==0)
		printf("creating all files was successful\n");
	else
		printf("creating all files was not successful\n");
}

void test_empty_sch_file()
{
	if(cds_createDataStore("Empty")==0)
		printf("creating all files was successful\n");
	else
		printf("creating all files was not successful\n");
}

void test_improper_format()
{
	if(cds_createDataStore("improper")==0)
		printf("creating all files was successful\n");
	else
		printf("creating all files was not successful\n");
}

void main()
{
	test_valid_database_name();
	test_invalid_database_name();
	test_empty_sch_file();
	test_improper_format();
}


