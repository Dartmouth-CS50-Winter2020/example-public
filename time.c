/*
 * time.c: a dummy code that displays current time three times, 
 *         sleeps for 1 sec between adjacent displays
 *
 * Note: the code is only for illustration of parameter passing, 
 *       there are much simpler ways to do the same. 
 * 
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void getTime(char *t)
{
	time_t now = time(0);
	t = calloc(strlen(ctime(&now))+1, sizeof(char));
	strcpy(t, ctime(&now));
}

int main()
{
	char *dst = NULL; 

	for (int i = 0; i < 3; i++) {
		getTime(dst);
		sleep(1);
		printf("current time: %s\n", dst);
	}
	
	return 0;
}
