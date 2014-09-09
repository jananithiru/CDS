#include "headers.h"
extern FILE *logfiledesc;
/*struct bstNode
{
struct primaryIndex *data; //This would hold the "unique" key to be indexed
struct bstNode *rightChild;
struct bstNode *leftChild;
};*/
//=====================================================================================================
struct bstNode* bstLoadFromFile(FILE *fp)
{
     if(fp==NULL)
		{
			LOG_ERROR("  No file exists. Cannot load from file.\n");
    			return NULL;
		}

     struct bstNode *root=NULL ;//*temp=root,*new,*parent=NULL;
     struct primaryIndex *tempdata=(struct primaryIndex *)malloc(sizeof(struct primaryIndex));
//     int i;
     while(fread(tempdata,sizeof(struct primaryIndex),1,fp)!=0)
		bstInsertNode(&root,tempdata);
     LOG_INFO("Populated the BST structure\n");
     return root;
}

//=====================================================================================================
//Insert a node in BST. The primary index will be used for insertion.Updations to root will be made if required.Return 0 for success and -1 for failure.
int bstInsertNode(struct bstNode **rootNode,struct primaryIndex *data)
{
      struct bstNode *temp = *rootNode,*new,*parent=NULL;
      while(temp!=NULL)
      {
              parent=temp;
              if( strcmp(data->key,temp->data->key)>0) 
                   temp=temp->rightChild;
              else if( strcmp(data->key , temp->data->key)<0 )
                   temp=temp->leftChild;
              else if(strcmp(data->key,temp->data->key)==0 && temp->data->flag=='1')
              {
                   *temp->data=*data; 
                   return BST_SUCCESS;
              }
              else
			{
		   LOG_INFO("The node already exists in the BST\n");
                   return BST_DUPLICATE;
		}
       }


       new=(struct bstNode*)malloc(sizeof(struct bstNode));
       new->data=(struct primaryIndex*)malloc(sizeof(struct primaryIndex));
       *new->data=*data;
       new->rightChild=new->leftChild=NULL;

       if(*rootNode==NULL)
         *rootNode=new;
       else
       {
         if( strcmp(data->key , parent->data->key)>0 )
            parent->rightChild=new;
         else
            parent->leftChild=new;
       }
       displayNodes(cdsInfo.primaryNdx);
       LOG_INFO("Successfully inserted a node in the BST\n");
       return BST_SUCCESS;
}
//=====================================================================================================
//Search the BST for the primary Index of the given key.
struct primaryIndex *bstSearchNode(struct bstNode *rootNode,char *key)
{
      struct bstNode *temp=rootNode;
      while(temp!=NULL)
      {
          if( strcmp(key , temp->data->key)>0) 
                   temp=temp->rightChild;
          else if( strcmp(key , temp->data->key)<0 )
                   temp=temp->leftChild;

          else if(strcmp(temp->data->key,key)==0 && temp->data->flag=='0')
                return temp->data;
          else
		{
		LOG_INFO(" The node was marked for deletion.\n");
                return NULL;
		}
      }
	LOG_INFO("Reached the end of the BST. Node not found\n");
      return NULL;

}
//=====================================================================================================
//Write the upddted BST to the file for making it persistent.Return 0 for success and -1 for failure.
int bstPersistNodes(struct bstNode *root,FILE *fp)
{
    if(fp==NULL)
	{
		LOG_ERROR("No such file exists. Could not persist\n");
		return BST_FAIL;
	}
    if(root==NULL)
	{
		LOG_INFO("Persisted the BST\n"); // What about an empty BST?
	        return BST_SUCCESS;
	}
    if(root->data->flag=='0')
      fwrite(root->data,sizeof(struct primaryIndex),1,fp);
    bstPersistNodes(root->leftChild,fp);
    bstPersistNodes(root->rightChild,fp);

}          
//=====================================================================================================
int displayNodes(struct bstNode *root)
{
    if(root==NULL)
        return 0;
    displayNodes(root->leftChild);
    printf("%s ",root->data->key);
    printf("%d ",root->data->offset);
    printf("%c\n",root->data->flag);
   
    displayNodes(root->rightChild);
    return 1;
}          
//=====================================================================================================
int bstMarkDeleted(struct bstNode *rootNode,char *key)
{
    struct bstNode *temp=rootNode;
    while(temp!=NULL)
    {
         if( strcmp(key , temp->data->key)>0) 
                temp=temp->rightChild;
         else if( strcmp(key , temp->data->key)<0 )
                temp=temp->leftChild;
         else if(strcmp(temp->data->key,key)==0 && temp->data->flag == '0')
         {
             temp->data->flag='1';
		LOG_INFO("Marked the node for deletion\n");
             return BST_SUCCESS;
         }
         else if(strcmp(temp->data->key,key)==0 && temp->data->flag == '1')
         {
			 LOG_INFO("Already Marked the node for deletion\n");
             return BST_ALREADYMARKED;
         }
         else
		{
		LOG_INFO("Didn't find the node. Couldn't mark for deletion\n");
	             return BST_FAIL;
		}
    }
    return BST_FAIL;
}
         
//=====================================================================================================
void freeTree(struct bstNode *root)
{
	if(root==NULL)
		return;
	freeTree(root->leftChild);
	freeTree(root->rightChild);
	free(root);
}          

