/* CS2211a 2020 */
/* Rowena Shi */
/* November 30, 2020 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"

#ifndef list
#define list

LIST* createControlStructure(void) {
   LIST* linked_list;
   linked_list = (LIST*) malloc (sizeof (LIST));
	if (linked_list) {
        linked_list->first = NULL;
        linked_list->count = 0;
   	} // if
	return linked_list;
}	// createList

#endif
