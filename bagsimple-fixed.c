/*
 * bagsimple.c - a simple use case of bag module
 * 
 * insert student_t struct into a bag, and print out bag items
 * 
 * CS50 January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "bag.h"
#include "readlinep.h"

typedef struct student {
	char *name; 
	int age; 
	float gpa; 
} student_t; 

void student_print(FILE *fp, void *item);
void student_delete(void *item);

int main()
{
	// create a bag
	bag_t *bag = bag_new(); // the bag

	// insert into the bag
	student_t *stu; // fix 1: switch to struct pointer
	int start_age = 16;
	float start_gpa = 3.5;
	while (!feof(stdin)) {
		char *name = readlinep();  // readlinep() used malloc()
		if (name != NULL) {
			// fix 2: request heap memory and initiate it accordingly
			stu = malloc(sizeof(student_t));
			stu->name = name; 							 
			stu->age = start_age++;
			stu->gpa = start_gpa + 0.1;
			bag_insert(bag, stu); 
		}
	}

	// print out bag items
	bag_print(bag, stdout, student_print); 

	// delete the bag
	bag_delete(bag, student_delete);

	return 0;
}

// print a student struct
void student_print(FILE *fp, void *item)
{
	student_t *s = item; 
	if (s == NULL) {
		fprintf(fp, "(null)");
	}
	else {
		fprintf(fp, "%s, age: %d, GPA: %.1f\n", s->name, s->age, s->gpa);
	}
}

// delete a student struct 
void student_delete(void *item)
{
	student_t *s = item; 
	if (s != NULL)
	{
		if (s->name != NULL) { // fix 3: free heap memory related to name
			free(s->name);  // name points to a heap memory block because of readlinep() function
		}
		free(s); 
	}
}

