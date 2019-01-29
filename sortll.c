// ----------------------------------------------
// sort.c  by Ph. Jounin 2018
//
// A implementation of the fusion sort algorithm
// applied to a linked list
//
// ----------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


struct LL 
{
   char *name ;
   int   len ;
   struct LL *next;
};



#define min(a,b)  ( (a) < (b) ? (a) : (b) )
// ----------------------------------------------------

static void *merge_ll ( struct LL *first, struct LL *second, 
                              int cmp(void const *a, void const *b) )
{
struct LL *prev ; // last item sorted
struct LL *cur ;  // item being sorted
struct LL dummy ; // init starting point for prev, thus prev->next is never NULL
                  // also keep track of beginning of list (dummy.next)

   // printf ("merging list %p (%s) and list2 %p (%s) items\n", first, first->name, second, second->name);

  for ( prev = & dummy ;       // dummy.next is the beginning of the list
        first != NULL  && second != NULL ; 
        prev = prev->next = cur )
  {
      if ( cmp (first, second) < 0 )
      {
         cur = first ;          // take elem from first queue
         first = first->next ;  // and advance this queue
      }
      else
      {
         cur  = second ;         // take elem from secodn queue
         second = second->next ; // and pop it from queue
      }
      //  printf ("inserted item %s in pointer %p/%p (%p, %p)\n", cur->name, cur, prev, first, second);
  } // interleave lists       

  // one list has been fully copied, complete with the rest of the other queue
  prev->next = (first==NULL) ? second : first;
//  printf ("inserted list beginning with %s in pointer %p (%p, %p)\n", prev->next->name, prev->next, first, second);
  
return dummy.next;
} // merge_ll


struct LL * sort_ll ( struct LL *liste, int cmp(void const *a, void const *b) )
{
int count, half, ark ; 
struct LL *cur, *split_ll;
   
    // count the items
    for (count=0, cur=liste ;   cur!=NULL ; cur = cur->next )  count ++;

    if (count>1)
    {
        half = (count+1) / 2;
        for (ark=0, split_ll=liste ;  ++ark<half ;  split_ll=split_ll->next);
        cur = split_ll;
        split_ll = split_ll->next ; 
        cur->next = NULL; 

        liste = sort_ll (liste, cmp);
        split_ll = sort_ll (split_ll, cmp);
        liste =  merge_ll ( liste, split_ll, cmp);

    }
return liste;
} // sort_ll
        


// ----------------------------------------------------

struct LL *Create (const char *file)
{
FILE *f;
char buf[128];
struct LL *head=NULL, *cur;
int len;

   f = fopen (file, "r");
   if (f==NULL)  { printf ("error: can not open file %s\n", file); return NULL; }
   while ( fgets(buf, sizeof buf, f) )
   {
      len = strlen (buf);
      if (buf[len-1] == '\n')    buf[--len] = 0;
      if (buf[len-1] == '\r')   buf[--len] = 0;
      if (head==NULL)    head = cur = malloc(sizeof *cur);
      else               cur = cur->next = malloc (sizeof *cur);
      cur->next = NULL;
    
      cur->name = strdup (buf);
      cur->len = len;
   }
  fclose (f);
return head;
} // Create
      

int LL_Print  (struct LL *head, char *sz)
{
int count;
   printf (sz);
   for ( count=0 ;  head!=NULL ; head=head->next, count++ )
      printf ("%s (%d)%s", head->name, head->len, head->next==NULL ? "" : ", " );
   printf (" %d items -----------------\n", count);
return count;
} // print_array


// ----------------------------------------------------

static nbcmp=0;

int cmp (const void *a, const void *b) 
{ 
struct LL *pa, *pb;
   pa = (struct LL *) a;
   pb = (struct LL *) b;

   // printf (" comparing %s and %s\n", pa->name, pb->name );
   nbcmp++;
   return ( pa->len == pb->len ) ?   strcmp (pa->name, pb->name) : pa->len - pb->len ;
}

int main (int argc, char *argv[])
{
clock_t begin;
struct LL *head1, *head2, *head;

   head1 = Create (argv[1]);
   LL_Print (head1, "brut: ");
   // head2 = Create (argv[2]);
   // LL_Print (head2);
   // head = merge_ll (head1, head2, cmp);

  head = sort_ll (head1, cmp);
   LL_Print (head, "sorted:" );

   
   begin = clock();
   printf ("done ins %d ms, with %d comparaisons\n", (clock()-begin) / (CLOCKS_PER_SEC/1000), nbcmp);
   

} // main

