// ----------------------------------------------
// getfilesize.c by Ph. Jounin 2018
//
// a simple test to retrieve the length of huge files (>4Gb)
// ----------------------------------------------

#include <stdio.h>

long GetFileSize(const char *filename)
{
FILE *hdle;
long size=-1;
   hdle = fopen(filename, "r");
   if (hdle!=NULL)
   {
       fseek (hdle, 0, SEEK_END);
       size = ftell (hdle);
       fclose (hdle);
   }
return size;
}

int main (int argc, char *argv[])
{
int ark;
   printf ("sizeof an integer is %ld, a long is %ld bytes\n", sizeof (int), sizeof (long) );
   for (ark=1 ;  ark<argc ; ark++)
      printf ( "file size of %s: %ld\n", argv[ark], GetFileSize (argv[ark]) );
}

