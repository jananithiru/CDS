/*Structures to be used in CDS*/
/*
In any function if the return type is int and
it is expected to return the status then,
on success return 0
on failure return 1

*/
#define SUCCESS 0
#define NULL_LIST 1
#define NULL_DATA 2

#define TYPE_INT 1
#define TYPE_STRING 2

#define LOG_INFO(msg)   fprintf(logfiledesc, "#INFO: %s : %d : %s", __FILE__, __LINE__, msg); //*__DATE__*/) ;
#define LOG_WARNING(msg)   fprintf(logfiledesc, "#WARNING:%s : %d : %s", __FILE__, __LINE__, msg);//*__DATE__*//) ;
#define LOG_ERROR(msg)   fprintf(logfiledesc, "#ERROR: %s : %d : %s", __FILE__, __LINE__, msg);/*__DATE__*/

struct node
{
   void *data;
   struct node *next;
};

typedef struct
{
    int count;
    struct node *head;
} LISTCOLLECTION;

struct primaryIndex
{
	char key[30]; // forms the unique key of your schema
	int offset; //offset of your unique key
	char flag; //set to 1, if deleted
};

struct secondaryIndex
{
	char key[30] ; // or int key;  //depeneds on the type of your secondary index
	int offset;
	char flag;
};


#define MAX_COL_NAME  2 //fill up the max length of column name
#define MAX_COL 10

#define CDS_CLOSED 0
#define CDS_OPEN_RW 1
#define CDS_OPEN_READONLY 2

struct colDataStore{
	int state;				//Stores the state of the datastore (CDS_CLOSED etc.)
	char *database;
	struct bstNode *primaryNdx;		//Stores the bst root node
	struct hashTable *secondaryNdx;		//Stores the hashtable for secondary indeing
	struct stack *freelist;			//Stores the stack for freelist
	int numCols;				//Number of columns in the datastore
	struct{
		FILE *fptr;			//file pointer to the corresponing column dat file
		int type;                       //Type of the field TYPE_INT or TYPE_STRING
		int length;                     //Length of the field. 4 in case of int or n depends on the record definition
		char *colname; 	//Name of the column
	} fileregister[MAX_COL];		//Array of the column structure storing the name and file pointer
};

/* Added by RC */

extern struct colDataStore cdsInfo;
struct dataRecord{
	int numCols;
	char *values[MAX_COL];
};

/* The implementation for the following function is present in globals.c */

#define PRINT_ERROR 1
#define STRING_WRITE_ERROR 2
#define STRING_READ_ERROR 3

int printRecord( struct dataRecord* record );
int printCollection( LISTCOLLECTION* recordset );
int printDatabase();
int writeString( FILE *fp, int position, char *str, int maxsize );
char *readString( FILE *fp, int position, int maxsize );
