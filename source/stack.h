/*header files for implementing hash*/

/*
In any function if the return type is int and
it is expected to return the status then,
on failure return 0
on success return 1

*/


struct stack
{
int top;
int stackArray[100];
};

/*
Initialize the stack..
set all the array elements of stack to -1 and top to -1
Return 1 on success and 0 on failure
*/
int stackInit(struct stack *s);

/*
pop the data from the stack and store its address 'data'
If empty return 0. else 1
*/
int stackPop(struct stack *s,int *data);

/*
push the data to the stack.
if full return 0. else 1.
*/
int stackPush(struct stack *s, int data);

/*
Write the stack to the file for making it persistent.
The file pointer passed should be opened in write mode and not
append mode. Return 1 on success and 0 on failure
*/
int stackPersist(FILE *fp, struct stack* s);

/*
Populate the stack from the file.
The file pointer fp is opened in read mode.
Return 1 on success and 0 on failure
*/
int stackLoadFromFile(FILE *fp, struct stack* s);

//void stackDisplay(struct stack* s);
