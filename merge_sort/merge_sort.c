// ------------------------------------------
// A merge sort for linked list
// Ph. Jounin
// ------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

const int bVerbose=0;

// return the middle of a list
static struct S_node *split_list (struct S_node *first)
{
struct S_node *p1, *p2, *middle;
  // use two pointers p1 and p2, let p2 advance twice faster
  // p1 will be at the middle 
  for ( p1=first, p2=first->next; 
        p2!= NULL && p2->next !=NULL ; 
        p1=p1->next, p2=p2->next->next);
  middle = p1->next;
  p1->next = NULL; // split the list
return middle;
} // split_list

// merge two lists 
static struct S_node *merge_list (struct S_node *list1, 
                                  struct S_node *list2,
                                  int (* cmp) (const struct S_node *, const struct S_node *))
{
struct S_node head = { NULL };  // a dummy member
struct S_node *list, **low;

  for ( list=&head ; list1!=NULL && list2!=NULL ; list=list->next )
  {
    low = cmp (list1, list2)<0 ? &list1 : &list2; // points on the list with the lower item
    list->next = *low;                            // add the item to the merged list
    *low = (*low)->next;                          // and advance in the list
  }
  // one list is empty, attach the other one to the new list
  if (list1==NULL) list->next = list2;
  else             list->next = list1;

return head.next;
} // merge_list


// recursively split the list into single items, then regoup itemps using the cmp function
// and merge lists
struct S_node *merge_sort (struct S_node *first, int (* cmp) (const struct S_node *, const struct S_node *))
{
struct S_node *front, *middle;
  if (bVerbose) 
      printf ("entering merge_sort for ptr %p (%s)\n", first, "");
  if (first==NULL)  return NULL;
  if ((first)->next==NULL)  return first;

  middle = split_list (first);    // get middle list
  front = merge_sort (first, cmp);     // sort first part
  middle = merge_sort (middle, cmp);

  first = merge_list (front, middle, cmp);
  return first;
} // comb_sort




