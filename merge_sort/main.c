// ------------------------------------------
// A merge sort for linked list
// Ph. Jounin
// ------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 #include "merge_sort.h"

#define STR_LEN 12

struct S_strnode 
{
    struct S_strnode *next;
    char          *sz;
};

struct S_strnode dummy = { NULL, ""};

struct S_strnode *fill (struct S_strnode *first, int n)
{
char buf[STR_LEN + 1];
struct S_strnode *node=first, *new_node;
  for (int ark=0 ; ark<n ; ark++)
  {
     int i;
     int len = rand() % (sizeof buf/3) +
               rand() % (sizeof buf/3) +
               rand() % (sizeof buf/3);
     for (i=0 ; i<len ; i++)
       buf[i] = rand() % (('z'+1)-'a') + 'a';
     buf[i] = 0;
     new_node = malloc (sizeof *new_node);
     // attach new_node to last node (which exists)
     node->next = new_node;
    
     node = new_node; // swap
     node->next = NULL;
     node->sz = strdup (buf);
  }
  return first;
} // fill


void dump (const char *prefix, const struct S_strnode *first)
{
  if (prefix!=NULL)
    printf ("%s\n", prefix);
  for (int ark=0 ; ark<strlen (prefix) ; ark++) 
      putchar ('-');
  printf ("\n");
  for (const struct S_strnode *node=first ; node!=NULL ; node=node->next)
    printf ("string is %-*.*s, pos %p, next %p\n", STR_LEN, STR_LEN, node->sz, node->next);
} // dump


int cmp (const struct S_node *a, const struct S_node *b)
{
  return strcmp ( ((struct S_strnode *) a)->sz, ((struct S_strnode *) b)->sz);
}


int main(void) {
  srand (time(NULL));
  fill (&dummy, 30);
  dump ("unsorted list", &dummy);
  dummy.next = merge_sort (dummy.next, cmp);
  dump ("sorted list", &dummy);
}
