#ifndef __BAG_H
#define __BAG_H

/*****global data types****/
typedef struct bag bag_t; // hide the bag structure from the user

/***** functions ****/

/* Create a new (empty) bag; return NULL if error. */
bag_t *bag_new(void);

/* Add new item to the bag; a NULL bag is ignored; a NULL item is ignored. */
void bag_insert(bag_t *bag, void *item);

/* Return any data item from the bag; return NULL if bag is NULL or empty. */
void *bag_extract(bag_t *bag); 

/* Print the whole bag; provide the output file and func to print each item.
 * If fp==NULL; do nothing. If bag==NULL, print (null).
 * If itemprint==NULL, print nothing for each item.
 */
void bag_print(bag_t *bag, FILE *fp,
               void (*itemprint)(FILE *fp, void *item));

/* Delete the whole bag; ignore NULL bag.
 * Provide a function that will delete each item (may be NULL).
 */
void bag_delete(bag_t *bag, void (*itemdelete)(void *item));

#endif // __BAG_H