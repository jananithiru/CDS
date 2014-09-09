/*
*This is the header file for implementing BST
* BST is basically used for primary/unique key indexing
*/

/*
In any function if the return type is int and
it is expected to return the status then,
on failure return 0
on success return 1

*/
//#include "cds.h"

struct bstNode
{
struct primaryIndex *data; //This would hold the "unique" key to be indexed
struct bstNode *rightChild;
struct bstNode *leftChild;
};

/*
*The basic functionality of this function is to Load the BST from a file
This gets the file pointer in read mode. If it doesnot find anything(ie, eof at the file pointer) then it
returns NULL.
*/
struct bstNode *bstLoadFromFile(FILE *fp);

/*
*This is used to insert a primary index into a BST.
* We are passing **rootNode so that, if during insertion the rootNode changes -
then we can we can reassign the rootNode (usually when the bst is empty)
If you are trying to insert a node whose key is same as another node's (unless
its marked for deletion), the function should return 0. But if u are trying to
a node whose key is same a node's key which was marked for deletion then free the node's data
and assign the given primaryIndex data.
*/
int bstInsertNode(struct bstNode **rootNode,struct primaryIndex *data);

/*
Delete a node from BST depending upon the key.
in other words remove the node from the tree.
This can result in the change of root node itself. thats the reason
for **rootNode
*/
int bstDeleteNode(struct bstNode **rootNode,char* key);


/*
This function is used to only set the flag of the primary index to denoted that its
deleted - Since there is no possiblity of a change in rootNode - only a single pointer is passed
*/
int bstMarkDeleted(struct bstNode *rootNode,char* key);

/*
Search the BST for the primary Index of the given key.
If a node is deleted for delete and it should return NULL
*/
struct primaryIndex *bstSearchNode(struct bstNode *rootNode,char* key);

/*
Write the updated BST to the file for making it persistent.
The file pointer fp is opend in write mode. Start writeing the
data from the current pointer. This will be called after persistStack function
*/
int bstPersistNodes(struct bstNode *rootNode,FILE *fp);

