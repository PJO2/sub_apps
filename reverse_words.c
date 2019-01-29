// ---------------------------------------------------------
// Google challenge : reverse words: C version
// by Ph. Jounin 2018
//
// one pass algorithm to reverse words
// ---------------------------------------------------------

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char STR[] =  "find you will pain only go you recordings security the into if";

struct S_Words 
{
  char *word;
  struct S_Words *prev;
}
first = {  "", NULL };

char *reverse_words (const char *s)
{
struct S_Words *p, *prev;
const char *word, *next_word;
int len;
static char sz[521]="";

  for ( prev=&first, word=s ; word!=NULL+1 ; word=next_word+1, prev=p )
  { 
    p = malloc (sizeof *p);
    p->prev= prev;
    next_word = strchr (word, ' ');
    len = (next_word==NULL ? strlen(word) : next_word - word );
    p->word = strndup (word, len);
    printf ("+ %s\n", p->word);
  }

  for ( ; p->prev!=NULL ; p=p->prev )
  {
    printf ("- %s\n", p->word);
    strcat (sz, p->word);
    strcat (sz, " ");
  }

   return sz; 
}


int main ()
{
   printf ("<%s>\n", reverse_words (STR) );
}
