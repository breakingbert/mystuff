// Linked list implementation skeleton
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


/* Node */
struct LINKED_LIST_NODES{
	void *value;
	struct LINKED_LIST_NODES *next;
	struct LINKED_LIST_NODES *prev;
};

//create useful node handle
typedef struct LINKED_LIST_NODES *LINKED_LIST_NODE_T;

/* Double linked list */
struct LINKED_LIST_S{
	LINKED_LIST_NODE_T firstNode;
	LINKED_LIST_NODE_T currentNode;
	LINKED_LIST_NODE_T lastNode;
};

// Function to create a linked list and return an opaque handle to it
LINKED_LIST_T linkedListCreate()
{
	struct LINKED_LIST_S *list = (struct LINKED_LIST_S *)malloc(sizeof(struct LINKED_LIST_S));

    list->firstNode = NULL;
    list->lastNode = NULL;
    list->currentNode = NULL;

	return list;
}

// Function to destroy a linked list
// If fn is not NULL then it will call fn for each item in the list
void linkedListDestroy(LINKED_LIST_T list, DestroyFunction fn)
{
	list->currentNode = list->lastNode;

    while(list->currentNode->prev != NULL)
    {
    	list->currentNode = list->lastNode->prev;
    	if(fn != NULL)
    		fn(list->currentNode->next);
    	else {
    	    free(list->currentNode->next);
    	}
    	list->lastNode = list->currentNode;
    }
    //last one!
    (fn != NULL)? fn(list->currentNode->next): free(list->currentNode);
}

// Function to check if a list is empty
// returns  0  - False, there are items in the list
//          !0 - True
int linkedListIsEmpty(LINKED_LIST_T list)
{
	if (list->firstNode == NULL) return -1;
	return 0;
}

// Append an item to the list.  This will add the item to the end of the list
// Item must be non-null
//
// Returns:  0 - Success
//          !0 - Failed
int linkedListAppend(LINKED_LIST_T list, void *item)
{
	if (list == NULL) return -1;
	if (item == NULL) return -1;

	LINKED_LIST_NODE_T node = malloc(sizeof(struct LINKED_LIST_NODES));

	node->value = item;
	node->next = NULL;

	if (list->firstNode == NULL) {
		node->prev = NULL;
		list->firstNode = node;
		list->lastNode = node;
		list->currentNode = node;
	}
	else {
		node->prev = list->lastNode;
		list->lastNode->next = node;
		list->lastNode = node;
	}

	return 0;
}

// Insert an item into the list.  This will insert the item in front of the
// Current item in the list.  Item must be non-null
// Returns:  0 - Success
//          !0 - Failed
int linkedListInsert(LINKED_LIST_T list, void *item)
{
	if (list == NULL) return -1;
	if (item == NULL) return -1;
	//create new node
	LINKED_LIST_NODE_T node = malloc(sizeof(struct LINKED_LIST_NODES));
	node->value = item;

	node->next = list->currentNode;
	node->prev = list->currentNode->prev;
	//check that if we are in the first Node
	if (node->prev != NULL)
	    node->prev->next = node;
    node->next->prev = node;
    list->currentNode = node;

    if (list->currentNode->prev == NULL)
        list->firstNode = list->currentNode;
    return 0;

}

// Remove the current item from the list
// Returns: 
//          NULL - the list is empty
//          item - The removed item
void * linkedListRemove(LINKED_LIST_T list)
{
	void *val;

	LINKED_LIST_NODE_T current = list->currentNode;

	//oops, current is null!!, list is empty
	if (current == NULL) return NULL;

	val = current->value;

	//list with 1 element
	if (list->firstNode == current && list->lastNode == current) {
		list->firstNode = list->lastNode = NULL;
	}
	//>1 elements and current not pointing to first and last
	else if (list->firstNode != current && list->lastNode != current) {

		current->prev->next = current->next;
		current->next->prev = current->prev;
		//move forward currentNode
		list->currentNode = current->next;
	}
	//current pointing to the first element
	else if (list->firstNode == current) {
		list->firstNode = current->next;
		current->next->prev = NULL;
		list->currentNode =  list->firstNode;
	}
	//current pointing to the last element
	else if (list->lastNode == current) {
		list->lastNode = current->prev;
		current->prev->next = NULL;
		list->currentNode = list->lastNode;
	}
	free(current);
	return val;
}

// Get the current item in the list
// Returns:
//          NULL - The list is empty
//          item - The current item
void * linkedListCurrent(LINKED_LIST_T list)
{
	return list->currentNode->value;
}

// Get the first/last item from the list and set as current
//
void * linkedListGetFirst(LINKED_LIST_T list)
{
	list->currentNode = list->firstNode;
	return list->currentNode->value;
}

void * linkedListGetLast(LINKED_LIST_T list)
{
	list->currentNode = list->lastNode;
	return list->currentNode->value;
}

// Get the next / previous item from the list and set as
// current
void * linkedListGetNext(LINKED_LIST_T list)
{
	LINKED_LIST_NODE_T temp = list->currentNode->next;
	if (NULL != temp) {
		list->currentNode = temp;
		return list->currentNode->value;
	}
	else return NULL;

}

void * linkedListGetPrev(LINKED_LIST_T list)
{
	LINKED_LIST_NODE_T temp = list->currentNode->prev;
	if (NULL != temp) {
		list->currentNode = temp;
		return list->currentNode->value;
	}
	else return NULL;
}

// Sort the linked list
// fn is a function used to compare two list items
// usr_info is a value passed to every call of fn
int linkedListSort(LINKED_LIST_T list, CompareFunction fn, void *usr_info)
{
	//let's do a simple bubble sort, we could do fancy things such qsort or merge sort but
	//we are running out of time.
	LINKED_LIST_NODE_T q,q1;
	void *a1,*a2;

    q = list->firstNode;
    while(q!=NULL)
    {
        q1 = q->next;
        while(q1!=NULL)
        {
            a1 = q->value;
            a2=  q1->value;
            if(fn(a1,a2,usr_info))
            {
            	//with only one value that will do
            	//but ideally we should do a node swap.
                q1->value=a1;
                q->value=a2;
            }
            q1=q1->next;
          }
          q=q->next;
      }

}

