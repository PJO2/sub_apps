// -------------------------------------------------------
// Google challenge : shuffle a card deck
// by Ph. Jounin 2018
// 
// shuffle.c: 
// limitation: because RAND_MAX lower that the number of hands
//             this is a bad generator
// --------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y) { typeof(x) swap=x; x=y ; y= swap; }

#define DECK_SIZE 52
#define COLORS     4
#define PLAYERS    4

int shuffle (int deck[], int len)
{
int ark, pos;
   for (ark=len-1;  ark>0 ; ark--)
   {
      pos = rand() % ark;
      SWAP (deck[ark], deck[pos]);

   }
} // shuffle


int comp_int (const void *pa, const void *pb)
{
   return * (const int *) pa - * (const int *) pb;
}

// affiche un jeu de bridge
int dump (int deck[], int len)
{
int ark;
static const char Colors[] = { 'S', 'H', 'D', 'C' };
static const char Cards[] = { 'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2' };
char last_color_idx=-1, color_idx;

   // sort each hand
   for (ark=0 ; ark<PLAYERS ; ark++)
       qsort ( & deck[len/PLAYERS * ark], len/PLAYERS, sizeof(deck[0]), comp_int);

   // dump only North hand
   for (ark=0 ; ark<len/PLAYERS ; ark++)
   {
      color_idx = deck[ark] / (DECK_SIZE / COLORS);
      while (color_idx > last_color_idx )
           printf ("\n%c ", Colors[++last_color_idx]);
      printf (" %c", Cards[deck[ark] % (DECK_SIZE / COLORS)] );
   }
  printf ("\n");
       
return 0;
}


int main ()
{
int deck[DECK_SIZE];
int ark;

   srand (time(NULL));
   for ( ark=0 ; ark<DECK_SIZE ; ark++) deck[ark]=ark;

   shuffle (deck, DECK_SIZE);
   
   dump (deck, DECK_SIZE);
}
