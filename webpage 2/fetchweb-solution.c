/*
 * fetchweb.c - an example of calling the webpage module to fetch a 
 *              webpage of a given URL and save it to a file.
 * 
 * usage: ./fetchweb URL FileName
 * 
 * see libcs50/webpage.md for APIs of the webpage module 
 *
 * Xia Zhou, January 2019
 * Updated by Temi Prioleau, January 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "libcs50/webpage.h"
#include "libcs50/memory.h"

/**************** local function prototypes ****************/
void save_page(webpage_t* page, const char* fname);

/**************** main ****************/
int main(const int argc, char *argv[])
{
	char* program = argv[0];  // program name

	// check input arguments: # of arguments
	if (argc != 3) {
		fprintf(stderr, "usage: %s URL FileName\n", program);
		return 1; 
	}
	// check input arguments: URL validity
	char* url = argv[1];
	if (!NormalizeURL(url)) {
		fprintf(stderr, "%s cannot be normalized\n", url);
		return 2;
	}

	// fetch the page
	webpage_t *web = webpage_new(url, 0, NULL); 
	if (webpage_fetch(web)) { 
		save_page(web, argv[2]);
	}
	else { // failed to fetch the page
		fprintf(stderr, "failed to fetch %s\n", url);
		webpage_delete(web);
		return 3;
	}
	webpage_delete(web);

	return 0;
}

/**************** save_page ****************/
void save_page(webpage_t* page, const char* fname)
{
	FILE *fp = fopen(fname, "w"); 
	assertp(fp, "cannot open file for writing\n");

	fprintf(fp, "%s\n%s", webpage_getURL(page), webpage_getHTML(page));

	fclose(fp);	
}