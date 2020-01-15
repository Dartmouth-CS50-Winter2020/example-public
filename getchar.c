#include<string.h>
#include<stdio.h>
#include<ctype.h>

int main()
{
     char c;

// Note if you type a char and <cr> i.e., newline 
// you will get two chars: the character you type and
// the newline. See example code below
     scanf("%c", &c);
     printf("the character is %d\n", c);
     scanf("%c", &c);
     printf("the character is %d\n", c);

// Note, I print the ASCII values of the characters so
// you can see the white space character \n "new line" value 10

// A more conventional way to do this is use getchar 
// and remove any white space characters like newline
// Other white space characters are space, tab, carriage-return.
// The code below drops any white characters and only
// prints chars.
     for (;;) {
          printf("\nEnter p, r, s, g, h, e:");     
          while (isspace( c = getchar()))
               ;
          printf("the character is %d", c);
          if ('q' == c)
               break;
     }

     return 0;
}



