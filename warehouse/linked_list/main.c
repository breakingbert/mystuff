// Linked list test skeleton
//
// This code is for interview

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

#define N_ITEMS 100

typedef enum list_order_t_
{
   ORDER_ASCENDING,
   ORDER_DESCENDING
   
} list_order_t;

// Comparison function for sorting the list
//
// Returns >  0 if ptr2 > ptr1
//         == 0 if ptr2 == ptr1
//         <  0 if ptr2 < ptr1
int sort_fn(void *ptr1, void *ptr2, void *usr)
{
   int a = (int) ptr1;
   int b = (int) ptr2;
   int direction = (list_order_t) usr;
   
   switch(direction)
   {
      case ORDER_ASCENDING:
         return b - a;

      case ORDER_DESCENDING:
         return a - b;
         
      default:
         printf("Invalid direction required in sort_fn\n");
         exit(-1);
   }
}

// Function to initialise the test items to known values
void initialiseTest(void *item[N_ITEMS])
{
   int i;
   
   for(i = 0; i < N_ITEMS; i++)
   {
      item[i] = (void *) (i+1);
   }
}

// Check that the list is in the order specified.
// Note: This will move the current position in the list
int checkList(LINKED_LIST_T list, list_order_t order)
{
   void *item;
   int i;

   i = (int) linkedListGetFirst(list);
   
   for(item = linkedListGetFirst(list);
       item;
       item = linkedListGetNext(list))
   {
      if((int) item != i)
         break;
      
      if(order == ORDER_ASCENDING)
         i++;
      else
         i--;
   }
   
   return item != NULL;
}

// Main function
// 
// Does not use any command line arguments
// Returns: 0 on success
//         -1 on failure
int main( int argc, char * argv[])
{
   LINKED_LIST_T list;
   void * item[N_ITEMS];
   void * item_tmp;
   int i;
   
   printf("Initialising test\n");
   initialiseTest(item);
   
   printf("Testing create\n");
   list = linkedListCreate();
   if(list == NULL)
   {
      printf("Failed to create list\n");
      return -1;
   }
   
   printf("Testing Append\n");
   linkedListAppend(list, item[0]);
   
   if(linkedListIsEmpty(list))
   {
      printf("Failed to add item to list\n");
      return -1;
   }
   
   printf("Testing remove\n");
   // Remove the current item from the list
   item_tmp = linkedListRemove(list);
   if(item_tmp != item[0])
   {
      printf("Failed to remove item from list\n");
      return -1;
   }
   
   if(!linkedListIsEmpty(list))
   {
      printf("Failed to remove the final item from the list\n");
      return -1;
   }
   
   printf("Setting up full list\n");
   for(i = 0; i < N_ITEMS; i++)
   {
      linkedListAppend(list, item[i]);
   }

   printf("Testing get first\n");
   i = 0;
   item_tmp = linkedListGetFirst(list);
   if(item_tmp != item[i])
   {
      printf("Failed to get first item from the list\n");
      exit(-1);
   }
   i++;
   
   printf("Testing get next\n");
   while((item_tmp = linkedListGetNext(list)) != NULL)
   {
      if(item_tmp != item[i])
      {
         printf("Failed to iterate the linked list forwards\n");
         exit(-1);
      }
      
      i++;
   }
   
   if(i != N_ITEMS)
   {
      printf("Failed to output all the items in the linked list\n");
      exit(-1);
   }
   
   printf("Testing get last\n");
   i = 0;
   item_tmp = linkedListGetLast(list);
   if(item_tmp != item[(N_ITEMS - 1) - i])
   {
      printf("Failed to get first item from the list\n");
      exit(-1);
   }
   i++;
   
   printf("Testing get prev\n");
   while((item_tmp = linkedListGetPrev(list)) != NULL)
   {
      if(item_tmp != item[(N_ITEMS - 1) - i])
      {
         printf("Failed to iterate the linked list backwards\n");
         exit(-1);
      }
      
      i++;
   }
   
   if(i != N_ITEMS)
   {
      printf("Failed to output all the items in the linked list (iterating backwards)\n");
      exit(-1);
   }
   
   printf("Check random movement\n");
   // This will return item 0
   linkedListGetFirst(list);
   linkedListGetNext(list); // item 1
   linkedListGetNext(list); // item 2
   linkedListGetNext(list); // item 3
   linkedListGetPrev(list); // item 2
   linkedListGetNext(list); // item 3
   linkedListGetPrev(list); // item 2
   
   // This should remove item 2
   item_tmp = linkedListRemove(list);
   if(item_tmp != item[2])
   {
      printf("Remove did not remove the current item\n");
      exit(-1);
   }
   
   // Removal of an item should make the current item the one after the removed item
   // This way insert will insert the item back into the list at the same position
   item_tmp = linkedListCurrent(list);
   if(item_tmp != item[3])
   {
      printf("Remove should make the current pointer move backward\n");
      exit(-1);
   }
   
   // Insert the item back again and check the list
   linkedListInsert(list, item[2]);
   if(checkList(list, ORDER_ASCENDING) != 0)
   {
      printf("Failed to insert item correctly into list\n");
      exit(-1);
   }
   
   // The list starts out being sorted in an ascending order
   printf("Testing sorting\n");
   linkedListSort(list, sort_fn, (void *) ORDER_DESCENDING);
   if(checkList(list, ORDER_DESCENDING) != 0)
   {
      printf("Failed to order the list in decending order\n");
      exit(-1);
   }
   
   // Repeat the sort back to ascending
   linkedListSort(list, sort_fn, (void *) ORDER_ASCENDING);
   if(checkList(list, ORDER_ASCENDING) != 0)
   {
      printf("Failed to order the list in ascending order\n");
      exit(-1);
   }
   
   printf("Testing inserting removing from beginning / end of list\n");
   
   // Test inserting / removing from beginning / end
   linkedListGetFirst(list);
   item_tmp = linkedListRemove(list);
   linkedListAppend(list, item_tmp);
   if(linkedListGetLast(list) != item_tmp)
   {
      printf("Failed to append item to end of list\n");
      exit(-1);
   }
   
   // Remove from end
   item_tmp = linkedListRemove(list);
   linkedListGetFirst(list);
   linkedListInsert(list, item_tmp);
   
   if(checkList(list, ORDER_ASCENDING) != 0)
   {
      printf("Failed to insert item at beginning of list\n");
      exit(-1);
   }
   
   //test destroy
   linkedListDestroy(list,NULL);

   printf("All tests passed\n");   
   return 0;
}
