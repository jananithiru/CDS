#include "headers.h"
extern FILE *logfiledesc;
/*struct stack
{
int top;
int stackArray[STACK_SIZE];
};*/

//=================================================================================================
int stackInit(struct stack *s)
{
	
	int i;	
	if(s == NULL)
		{
		LOG_WARNING("Freelist is NULL \n");
		LOG_ERROR("  Freelist is NULL \n");
		return STACK_FAIL;
		}
	s->top=-1;
	for(i=0;i<STACK_SIZE;i++)
	{
		s->stackArray[i] =-1;
		//printf("%d",s->stackArray[i]);
	}
	LOG_INFO("Freelist successfully initialised with 100 elements set to -1 \n");
	return STACK_SUCCESS;
	
}
//=================================================================================================
int stackPop(struct stack *s,int *data)
{
	
	if (s->top == -1)
		{
		LOG_INFO(" No offsets to pop \n");
		return STACK_FAIL;
		}
	*data = s->stackArray[s->top--];
	LOG_INFO(" Offset popped\n");
	return STACK_SUCCESS;
	
}
//=================================================================================================
int stackPush(struct stack *s, int data)
{
	
	
		if (s->top==STACK_SIZE)
		{
			LOG_ERROR("  Cannot insert! Freelist (stack) is full\n");
			return STACK_FAIL;
		}
	
		s->stackArray[++s->top] = data;
		LOG_INFO("Element inserted successfully into freelist\n");
		//printf("\n%d",s->stackArray[s->top]);
		return STACK_SUCCESS;
	
	
	LOG_ERROR(" ERROR : Character elements cannot be inserted into freelist\n");
	return STACK_FAIL;
}
//=================================================================================================
int stackPersist(FILE *fp, struct stack *s)
{
  	if(fp==NULL)
		{
			LOG_ERROR("  No file exists. Cannot persist the freelist.\n");
    			return STACK_FAIL;
		}
  	int arr[STACK_SIZE],i;
  	int data;
	
  	
	for(i=0;stackPop(s,&data)!=1;i++)
       			arr[i]=data;

  	while(i<STACK_SIZE)
	     	arr[i++]=-1;

	fwrite(arr,sizeof(int),STACK_SIZE,fp);
	LOG_INFO("Successfully persisted the freelist to file.\n");

    	return STACK_SUCCESS;
}
//=================================================================================================
int stackLoadFromFile(FILE* fp, struct stack* s)
{
	
	int buf[STACK_SIZE],i;	

  	if(fp==NULL)
		{
			LOG_ERROR("  No file exists. Cannot load from file.\n");
    			return STACK_FAIL;
		}

	fread(buf,sizeof(int),STACK_SIZE,fp); // Open the file and read the first 400 bytes
	
	for(i=0;i<STACK_SIZE;i++)
		{
			if(buf[i] == -1) // break when you encounter a -1
				break;

			stackPush(s,buf[i]);
							
		}
	LOG_INFO("Successfully populated the freelist. \n");
	return STACK_SUCCESS;
}


//=================================================================================================
// Change Display to print for test cases.
// CHECK how call is made in other files.
void stackDisplay(struct stack *s)
{
	int i=0;

	for(i=0;i<=/*s->top*/cdsInfo.freelist->top;i++)
		printf("%d ",cdsInfo.freelist->stackArray[i]);// s->stackArray[i]);
}





