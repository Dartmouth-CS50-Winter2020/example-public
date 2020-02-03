// This is a simple program for use to practice GDB
// 
// CS50 2020
// Date: 01/28/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function Prototype
void mystr_cpy(char *dest,char *src);

int main(){
    char *text1="Welcome";
    char *text2="CS50"; //Fix 1
   
    printf("\ntext1 is %s\n",text1);
    printf("\ntext2 is %s\n",text2);
    
    // Allocate memory on the heap
   // text2=malloc(strlen(text1)+1); //Fix 1

    printf("\n\nCopying text1 into text2...\n\n" );
    mystr_cpy(text2,text1);

    printf("New text2 is %s\n\n",text2);
    
    // free memory allocation
    //free(text2); //Fix 2
    return 0;
}
// Function to handle string copy with pointers
void  mystr_cpy(char *dest,char *src){
	while(*src!='\0'){
		*dest++=*src++;
	}
	*dest='\0';
}

