/*
 * fileIO - read a list of file names as command-line arguments, 
 *          and print the first line of each file. 
 *          return status is the # of files that it fails to read
 * 
 * usage: ./fileIO [filename]....
 * 
 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // only need it if option 2 is used

int main(const int argc, const char *argv[])
{
  int status = 0;
  FILE *fp; 

  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
  		fprintf(stderr, "failed to open %s\n", argv[i]);
  		status++; 
  		continue; // move on to the next argument/file
  	}
  	// read a line
  	printf("%s: ", argv[i]); 
  	// option 1: read by characters
  	char c; 
  	while ((c = fgetc(fp)) != EOF) 
  	{
  		putchar(c);
  		if (c == '\n') {
  			break; 
  		}
  	}

/* the following two options are less optimal as 
   they assume a maximal line length */

  	// option 2: read by lines
  	/*
  	char line[100];   // buffer to store a line
  	if (fgets(line, 100, fp) != NULL) {
  		int len = strlen(line);
  		if (line[len-1] == '\n') {
  			line[len-1] = '\0';
  		}
  		printf("%s\n", line);
  	}
  	*/

  	// option 3: read by format
  	/*
  	char line[100];   // buffer to store a line
  	if (fscanf(fp, "%[^\n]", line) == 1) {
  		printf("%s\n", line);
  	}
  	*/
  	
  	// close file 
  	fclose(fp);
  }

  return status;
}