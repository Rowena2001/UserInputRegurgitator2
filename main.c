/* CS2211a 2020 */
/* Rowena Shi */
/* November 30, 2020 */ 

// this is the main file
// it executes the functions in functions.h

#include "headers.h"

int main() {
    printf("\nWelcome to another difficult assignment. I would like to thank you for embarking on this journey with me.\n");
    LIST *l = input();
    print_sentences(l);
    search_word(l);
    delete_sentence(l);
    free_memory(l);
    printf("Have a nice day!\n");
    return 0;
}
