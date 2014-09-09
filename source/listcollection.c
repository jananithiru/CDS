#include "headers.h"

/*#define SUCCESS 0
#define NULL_LIST 1
#define NULL_DATA 2*/
//------------------------------
void print_list(LISTCOLLECTION *lc);

int LC_init(LISTCOLLECTION *lc)
{
     if(lc==NULL)
       return NULL_LIST;
     lc->count=0;
     lc->head=NULL;
     return SUCCESS;
}

int LC_insertHead(LISTCOLLECTION *lc,void *data)
{
    struct node *newNode;
    if(data==NULL)
       return NULL_DATA;
    if(lc==NULL)
       return NULL_LIST;
    newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data=data;
    newNode->next=lc->head;
    lc->count++;
    lc->head=newNode;
    return SUCCESS;
}

/*void print_list(LISTCOLLECTION *lc)
{
	struct node *s=lc->head;
	int i=0;
	//printf("FlightNo\tFlightName\tFlightType\tPilotName\tCoPilotName\n");
	while(i++<lc->count)
	{
	struct FlightData *fd=(struct FlightData*)s->data;
	printf("%d\t%s\t%d\t%s\t%s\n",fd->FlightNo,fd->FlightName,fd->FlightType,fd->PilotName,fd->CoPilotName);
		s=s->next;
	}
	
}*/

/*delete functionality is not required */
