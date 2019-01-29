// --------------------------------------------------------
// wildcard.c by Ph. Jounin 2018
//
// a poor man regexp: match a string against a pattern using wildcards * and ?
// 
// ----------------------------------------------------------

#include <stdbool.h>
#include <string.h>

#define MULTICHAR '*'
#define ONECHAR   '?'
#define BEGIN_CAPTURE '('
#define END_CAPTURE   ')'



bool wildcard(const char *subject, const char *pattern, char *capture, int len) 
{
const char *s;

    for (; *pattern; pattern++) 
    {
        switch (*pattern) 
        {
          case BEGIN_CAPTURE :
               len=0;
               break;

          case END_CAPTURE :
printf ("end of capture, len is %d\n", len);
               capture[len]=0;
               len=-1;
               break;

          case MULTICHAR:
            if (*(pattern + 1) == '\0') {
                /* This wildcard appears at the end of the pattern.
                   If we made it this far already, the match succeeds
                   regardless of what the rest of the subject looks like. */
                return true;
            }
            for (s = subject; *s; s++) {
                if (len!=-1) capture[len] = *s;
                if (wildcard(s, pattern + 1, capture, len)) {
                    return true;
                }
                len++;
            }
            return false;

          case ONECHAR:
            if (len!=-1)  capture[len++] = *subject;
            if (*(subject++) == '\0') {
                return false;
            }
            break;

          default:
            if (len!=-1)  capture[len++] = *subject;
            if (*subject == '\0' || *pattern != *(subject++)) 
            {
                return false;
            }
        } // switch *pattern
    } // parse all pattern

    /* End of pattern reached.  If this also the end of the subject, then
       match succeeds. */
    return *subject == '\0';
}

// ----------------------------------------
#include <string.h>
#include <stdio.h>

struct S_Test
{
   char *pattern;
   char *string;
   int  expected;
}
sTests[] = 
{
   { "a(*y)", "azerty", 1 },
   // { NULL, NULL, 0 },

   { "GET * HTTP/*.*", "GET http://10.1.1.2/index.html HTTP/1.1", 1 },
   { "", "", 1 },
   { "", "?", 0 },
   { "?", "", 0 },
   { "a(ze)rty", "azerty", 1 },
   { "a(?e)rty", "azerty", 1 },
   { "(a*r)ty", "azerty", 1 },
   { "a(*)", "azerty", 1 },
   { "a(*)zerty", "azerty", 1 },
   { "a*aerty", "azerty", 0 },
   { "a(*)e*rty", "azerty", 1 },
   { "a*e(*)y", "azerty", 1 },
   { "a*e*z", "azerty", 0 },
   { "a(*e*)", "azerty", 1 },

   { NULL, NULL, 0 },
};

int main ()
{
int ark;
char capture[32];
   for (ark=0 ;    sTests[ark].string!=NULL  ; ark++)
   {
      strcpy (capture, "123456789012345678901234567890");
      int rc = wildcard (sTests[ark].string, sTests[ark].pattern, capture, -1) ;

      printf ("args: %s, %s, expected %d, get %d, capture is <%s>\n",
                       sTests[ark].string,
                       sTests[ark].pattern,
                       sTests[ark].expected,
                       rc,
                       capture
             );
   }

}


