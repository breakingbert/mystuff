// Linked list implementation skeleton
//
// This is a linked list implementation, although the user does not require
// any knowledge of the internal structure and implementation of the list.
//
// Items in the linked list are passed through as void pointers and cannot
// be NULL (this is used as a special result in many functions)

// The linked list handle
typedef struct LINKED_LIST_S * LINKED_LIST_T;

// User destruction function
typedef void (*DestroyFunction)(void *ptr);

// User compare function
// Returns -ve ptr1 <  ptr2
//          0  ptr1 == ptr2
//         +ve ptr1 >  ptr2
typedef int (*CompareFunction)(void *ptr1, void *ptr2, void *usr_data);

// Function to create a linked list and return an opaque handle to it
LINKED_LIST_T linkedListCreate();

// Function to destroy a linked list
// If fn is not NULL then it will call fn for each item in the list
void linkedListDestroy(LINKED_LIST_T list, DestroyFunction fn);

// Function to check if a list is empty
// returns  0  - False, there are items in the list
//          !0 - True
int linkedListIsEmpty(LINKED_LIST_T list);

// Append an item to the list.  This will add the item to the end of the list
// Item must be non-null
//
// Returns:  0 - Success
//          !0 - Failed
int linkedListAppend(LINKED_LIST_T list, void *item);

// Insert an item into the list.  This will insert the item in front of the
// Current item in the list.  Item must be non-null
// Returns:  0 - Success
//          !0 - Failed
int linkedListInsert(LINKED_LIST_T list, void *item);

// Remove the current item from the list
// Returns: 
//          NULL - the list is empty
//          item - The removed item
void * linkedListRemove(LINKED_LIST_T list);

// Get the current item in the list
// Returns:
//          NULL - The list is empty
//          item - The current item
void * linkedListCurrent(LINKED_LIST_T list);

// Get the first/last item from the list and set as current
//
void * linkedListGetFirst(LINKED_LIST_T list);
void * linkedListGetLast(LINKED_LIST_T list);

// Get the next / previous item from the list and set as
// current
void * linkedListGetNext(LINKED_LIST_T list);
void * linkedListGetPrev(LINKED_LIST_T list);

// Sort the linked list
// fn is a function used to compare two list items
// usr_info is a value passed to every call of fn
int linkedListSort(LINKED_LIST_T list, CompareFunction fn, void *usr_info);
