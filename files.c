#include <assert.h>
#include <stdio.h>
#include <string.h>

#define   MAXSTRING   100

int main(void)
{
   char   input[MAXSTRING];
   char   string[15];
   char   *val;
   char   c;
   int    cnt;
   int    i;
   int    n;
   FILE   *ifp;

   ifp = fopen("input", "r");
   assert(ifp != NULL);
   // fgets reads in a string until it gets the newline (\n),  EOF character or reads MAXSTRING-1
   // characters. If it reads a newline it appends to the end of the array. This is the case
   // for the names file. The contents of the file have a string then a \n. 
   val = fgets(input, MAXSTRING, ifp);
   assert(val != NULL);
   fclose(ifp);

   /*
   // Delete the newline at the end of the input string.
   */
   n = strlen(input);

   // Note below we print out the /n with the %s when looking at the output.

   printf("string is \"%s\" and value at the end of string is the \\n character %d\n", input, *(input + n - 1));

   // So that the string will operate correctly we have to replace the \n with the NULL (\0) character

   *(input + n - 1) = '\0';

   printf("string is \"%s\" and value at the end of string is the \\0 character %d\n", input, *(input + n - 1));

   // sscanf parses the input string.  %*s means "match a string and then throw it away", and specific
   // characters must be matched by the format string it the sscanf terminates.
   cnt = sscanf(input, "%d , %*s %% %c %5s %s", &i, &c, string, &string[5]);

   // Note that when C encounters two successive string literals with onll whitespace between them, 
   // C will combine them into a single string for you.  Nice!  We use that here.

   printf("%s%s%s%c%s%d%s%s%s%s%s%d%s\n",
      "---\n"
      "Control string: \"%d , %*s %% %c %5s %s\"\n" 
      "\n"
      "  Input string: \"", input, "\"\n"
      "\n"
      "Here are the values obtained from the input string:\n"
      "\n"
      "            c = ", c, "\n"
      "            i = ", i, "\n"
      "       string = ", string, "\n"
      "   string + 5 = ", string + 5, "\n"
      "\n"
      "   number of successful conversions = ", cnt, "\n");
   return 0;
}
