/* Header file for implementing Linked List. Linked list will be used in the hash Table*/
//#include "cds.h"
struct llNode
{
struct secondaryIndex *data;
struct llNode *next;
};

/*Insert the data in the linked list in "sorted order" and update the head if required. The reason why it should be sorted order is because of the fact that it reduces the search complexity. For example : if 'abed' and 'abcd' are a part of a hash bucket, then, while searching for a string 'abdd' - the search function can return a "Not Found" if the list is sorted and if 'abed' is found and 'abdd' is not found. Only in the worst case you are supposed to search the entire bucket*/
int llInsertSortedOrder(struct llNode **head,struct secondaryIndex *data);

/*Return the node of the linked list containing the key.*/
struct llNode * llGetNode(struct llNode *head, char *key /* or int key; depending upon the secondary index type*/);

/*
Mark the node as deleted.
Return 1 on success and 0 on failure
*/
int llMarkDeleted(struct llNode *head,struct secondaryIndex * detail);

/*
Delete the nodes from the linked list which are marked to be removed.
Return 1 on success and 0 on failure
*/
int llDeleteNode(struct llNode **head,struct secondaryIndex * detail);

/*
Write the linked list to the file for making it persistent.
Return 1 on success and 0 on failure
*/
int llPersist(struct llNode *head,FILE *fp);

struct llNode* return_node(struct secondaryIndex *data);


int lldisplay(struct llNode *test);




