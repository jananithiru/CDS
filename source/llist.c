
#include "headers.h"
extern FILE *logfiledesc;
/*#define LIST_SUCCESS 0
#define LIST_FAIL -1 */
/*Insert the data in the linked list in "sorted order" and update the head if required. The reason why it should be sorted order is because of the fact that it reduces the search complexity. For example : if 'abed' and 'abcd' are a part of a hash bucket, then, while searching for a string 'abdd' - the search function can return a "Not Found" if the list is sorted and if 'abed' is found and 'abdd' is not found. Only in the worst case you are suspposed to search the entire bucket*/
//===============================================================================================
struct llNode* return_node(struct secondaryIndex *data)
{
    struct llNode *new;
    
    new=(struct llNode*)malloc(sizeof(struct llNode));
    new->data=(struct secondaryIndex*)malloc(sizeof(struct secondaryIndex));
    *new->data=*data;
    new->next=NULL;
 
    return new;
}
//===============================================================================================
int llInsertSortedOrder(struct llNode **head,struct secondaryIndex *data)
{
    struct llNode *temp=*head;
    struct llNode *new;
    new=return_node(data);
    
    if(temp==NULL)
    {
        *head=new;
         return LIST_SUCCESS;
    }
    
    while(temp->next!=NULL && strcmp(temp->next->data->key,data->key)<0)
        temp=temp->next;
    
    if(strcmp(data->key,temp->data->key)<0)
    {
          new->next=*head;
          *head=new;
           return LIST_SUCCESS;
    }    
    new->next=temp->next;
    temp->next=new;  
    return LIST_SUCCESS;
        
}
//===============================================================================================
/*Return the node of the linked list containing the key.*/
struct llNode * llGetNode(struct llNode *head, char *key /* or int key; depending upon the secondary index type*/)
{
    struct llNode *return_list=NULL;
    struct llNode *temp=head,*temp1,*new;

    while(temp!=NULL && strcmp(temp->data->key,key)<=0)
    {
          if(strcmp(temp->data->key,key)==0)
          {
              if(return_list==NULL)
              {
                  return_list=return_node(temp->data);
                  temp1=return_list; 
              }
              else
              {
                  new=return_node(temp->data);
                  temp1->next=new;
                  temp1=temp1->next;
              }
          }
          temp=temp->next;
    }
    LOG_INFO("Returned the node containing the key.");
    return return_list;
}
//===============================================================================================
/*
Mark the node as deleted.
Return 1 on success and 0 on failure
*/
int llMarkDeleted(struct llNode *head,struct secondaryIndex * detail)
{
    struct llNode *temp=head;
    while(temp!=NULL)
    {
       if(strcmp(temp->data->key,detail->key)==0 && temp->data->offset==detail->offset && temp->data->flag=='0')
       {
          temp->data->flag='1';
		  LOG_INFO("Marked a node for deletion\n");
          return LIST_SUCCESS;
       }
       else if(strcmp(temp->data->key,detail->key)==0 && temp->data->offset==detail->offset && temp->data->flag=='1')
			return LIST_ALREADYMARKED;
       temp=temp->next;
    }
    return LIST_FAIL;
}

/*
Delete the nodes from the linked list which are marked to be removed.
Return 1 on success and 0 on failure
*/
//===============================================================================================
int llDeleteNode(struct llNode **head,struct secondaryIndex * detail)
{
     struct llNode *temp,*ref,*prev=*head;
     int flag=0;

     if((*head)->data->flag=='1')
     {
        ref=*head;
        free(ref);
        *head=(*head)->next;          
        flag=1;
     }
     temp=*head;
     while(temp!=NULL)
     {
         if(temp->data->flag=='1')
         {
              temp=temp->next;
              free(prev->next);             
              prev->next=temp;
              flag=1;
         }
         else
         {
             prev=temp;
             temp=temp->next;
         }
    }
    if(flag==1)
	{	
		LOG_INFO("Successfully deleted a node\n");
		return LIST_SUCCESS;
	}
    
}
//===============================================================================================
/*
Write the linked list to the file for making it persistent.
Return 1 on success and 0 on failure
*/
int llPersist(struct llNode *head,FILE *fp)
{
    struct llNode *temp=head;
    int flag=0;
    while(temp!=NULL)
    {
        if(temp->data->flag=='0')
        {
           fwrite(temp->data,sizeof(struct secondaryIndex),1,fp);
           flag=1;
        } 
        temp=temp->next;
    }
    if(flag==1)
	LOG_INFO("Successfully persisted one row  ( linked list) \n");
    return LIST_SUCCESS;
}
//===============================================================================================
int lldisplay(struct llNode *test)
{
     while(test)
     {
          printf("%s %d %c\n",test->data->key,test->data->offset,test->data->flag);
          test=test->next;
     }
}
//===============================================================================================
void freeList(struct llNode *head)
{
	struct llNode *current=head,*temp;
	
	while(current!=NULL)
	{
		temp=current;
		current=current->next;
		free(temp);
	}
}
