#include "headers.h"
extern FILE *logfiledesc;
int cds_deleteByKey(char *key)
{

	if (cdsInfo.state != CDS_OPEN_RW)
		return DELETE_KEY_FAIL;

	struct dataRecord *record=(struct dataRecord *)malloc(sizeof(struct dataRecord));

	createEmptyRecord(record);
	
	struct secondaryIndex *hashData=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));

	if(selectByKey(key,record)==RECORD_NOTFOUND)
	{
		LOG_INFO("No Record found\n");
		return RECORD_NOTFOUND;
	}

	struct primaryIndex *bstData=bstSearchNode(cdsInfo.primaryNdx,key);
	int offset=bstData->offset;//copy offset to later push to stack
	
	if(stackPush(cdsInfo.freelist,offset)==STACK_FAIL)
	{
		LOG_INFO("Didn't push free offset onto stack\n");
		return DELETE_KEY_FAIL;
	}
	LOG_INFO("Pushed free offset onto stack\n");

	//Populating hash data  to mark for deletion
	strcpy(hashData->key,record->values[1]);
	hashData->offset=offset;
	hashData->flag='0';
	int temp;
	int retValue=bstMarkDeleted(cdsInfo.primaryNdx,key);
	if(retValue==BST_FAIL)
	{
		LOG_INFO("Did NOT mark the node for deletion in the BST\n");
		stackPop(cdsInfo.freelist,&temp);
		return DELETE_KEY_FAIL;
	}
	if(retValue==BST_ALREADYMARKED)
	{
		LOG_INFO("Did NOT mark the node for deletion as its already marked\n");
		stackPop(cdsInfo.freelist,&temp);
		return DELETE_KEY_FAIL;		
	}
	LOG_INFO("Marked the selected node for deletion in the BST\n");
	if(hashMarkDeleted(cdsInfo.secondaryNdx,hashData)==HASH_FAIL)
	{
		bstData->flag='0';
		//Reverting changes..since hashMark failed
		bstInsertNode(&cdsInfo.primaryNdx,bstData);
		stackPop(cdsInfo.freelist,&temp);
		LOG_INFO("Didn't mark the node for deletion in the linked list\n");
		LOG_INFO("Reverted Changes:Bst unmarked");
		return DELETE_KEY_FAIL;
	}
	LOG_INFO("Marked the selected node for deletion in the linked list\n");

	
	return DELETE_KEY_SUCCESS;
	
}
