/* CS2211a 2020 */
/* Rowena Shi */
/* November 30, 2020 */ 

// this file includes all the prototypes of the functions in functions.h

#include "structures.h"
#include "linkedlist.h"

#ifndef dH
#define dH
    LIST* input();
    void print_sentences(LIST* l);
    void search_word(LIST* l);
    void delete_sentence(LIST *l);
    void free_memory(LIST *l);
#endif
