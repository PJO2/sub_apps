// ----------------------------------------------
// sort.c  by Ph. Jounin 2018
//
// A implementation of the merge sort algorithm
//
// ----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define min(a,b)  ( (a) < (b) ? (a) : (b) )
// ----------------------------------------------------

// merge two sorted lists of list_size items, 
// first list is overriden (and second too if lists are consecutive)
static int merge_list_of_integers (int *first, int *second, int block_size, int *merged_list)
{
int idx1=0, idx2=0;
  // copy with interleaving until one list is consumed
  while ( idx1<block_size &&  idx2<block_size )
       *merged_list ++ = (first[idx1] < second[idx2]) ? first[idx1++] : second[idx2++];
  // one list has been copied, complete with the rest of the other queue
  if (idx1==block_size)
       while (idx2<block_size)  *merged_list++ = second[idx2++];
  else
       while (idx1<block_size)  *merged_list++ = first[idx1++];
}


static void *merge_lists (void *first, void *second, 
                         int first_list_size, int second_list_size,
                         int item_size, void *merged_list, int cmp(void const *a, void const *b))
{
void *first_edge, *second_edge;   // pointers on the location just after each list
                                  // (for us first_edge==second)

  // printf ("merging list 1 %d items and list2 %d items\n", first_list_size, second_list_size);
  if (second_list_size<=0)  return first;

  // iteration : items may be intervealed, procede item by item
  for (  first_edge = first + (first_list_size * item_size), second_edge = second + (second_list_size * item_size)  ;
         first<first_edge &&  second<second_edge ;
         merged_list += item_size  )
  {
     if ( cmp (first, second) < 0 )
     {
          memcpy (merged_list, first, item_size);
          first += item_size;
     }
     else
     {
          memcpy (merged_list, second, item_size);
          second += item_size;
     }
  } 

  // one list has been copied, complete with the rest of the other queue
  //  printf ("completing with %d char from list 1 and %d from list2\n", first_edge - first, second_edge - second);
  memcpy (merged_list, first, first_edge - first);
  memcpy (merged_list, second,  second_edge - second);
return merged_list;
}


void *mergesort (void *tArr, int items_nb, int item_size, int cmp(const void *a, const void *b))
{
int block_nb, list2_nb;  // number of items in first list and second list
int ark;
void *merged_list;  // memoty allocated for partial results

   // allocate some space for merged lists
   merged_list = malloc ( items_nb * item_size );

   // iterate on the blocs_nb using power of two until all items are split in only 2 lists
   for ( block_nb=1 ;  block_nb < items_nb ;  block_nb <<= 1 )
   {
      // merge two blocks
      for ( ark=0 ; ark<items_nb-block_nb ; ark += block_nb*2 )
      {
          // for last iteration size of second list may be shorter that block_nb
          list2_nb =  (ark+2*block_nb>items_nb) ? items_nb - block_nb - ark : block_nb ;

          merge_lists ( tArr + ark*item_size,               // beginning of the first list
                        tArr + (block_nb+ark)*item_size,    // beginning of the second list
                        block_nb,                           // number of items in first list
                        list2_nb,                           // number of items in second list
                        item_size,                          // size of an item 
                        merged_list,                        // list to contain first+second
                        cmp );                              // comparaison function
          // reinject merged list into initial array (only block_nb items)
          memcpy ( tArr + ark*item_size, merged_list, (block_nb+list2_nb) * item_size );
      }
   }
   free (merged_list);
return tArr;
} // mergesort
     
      



// ----------------------------------------------------
int init_array (int *tArr, int size)
{
int ark;
   srand (time(NULL));
   for (ark=0 ; ark<size ; ark++)
     tArr[ark] = rand() ;
return ark;
} // init_array

int print_array  (int *tArr, int size)
{
int ark;
   printf ("[ ");
   for (ark=0 ; ark<size ; ark++)
     printf ("%3d%s", tArr[ark], ark==size-1 ? "" : ", ");
   printf (" ] \n");
return ark;
} // print_array


// ----------------------------------------------------

static nbcmp=0;

int cmp (const void *a, const void *b) 
{ 
   //printf (" comparing %d and %d\n", * ((const int *) a), * ((const int *) b) );
   nbcmp++;
   return * ((const int *) a) - * ((const int *) b); 
}

int main (int argc, char *argv[])
{
int *tArray;
int size = 0;
clock_t begin;
   if (argc==2)  size=atoi(argv[1]);
   if (size==0)  size = 21;

   tArray = malloc (sizeof tArray[0] * size);

   init_array (tArray, size);
   // print_array (tArray, size);
   begin = clock();
   mergesort (tArray, size, sizeof tArray[0], cmp);
   // print_array (tArray, size);
   printf ("done ins %d ms, with %d comparaisons\n", (clock()-begin) / (CLOCKS_PER_SEC/1000), nbcmp);
   
  nbcmp=0;
   init_array (tArray, size);
   begin = clock();
   qsort (tArray, size, sizeof tArray[0], cmp);
   printf ("done ins %d ms, with %d comparaisons\n", (clock()-begin) / (CLOCKS_PER_SEC/1000), nbcmp);





   free (tArray);

} // main

