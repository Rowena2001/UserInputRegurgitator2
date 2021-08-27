/* CS2211a 2020 */
/* Rowena Shi */
/* November 30, 2020 */ 

// this file contains all the functions needed for the program
// main.c calls these functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"
#include "linkedlist.h"

#ifndef functions
#define functions

LIST* input() {
    LIST* l = createControlStructure();
    int sentence_count = 0;
    int word_count;
    char str[1000]; // character array for user input
    char *wstr; // pointer to a word string in the user input
    word *current_word = (word *)malloc(sizeof(word)); // dynamically allocates memory for a word
    sentence *current_sentence = (sentence *)malloc(sizeof(sentence)); // dynamically allocates memory for a sentence;

    printf("\nPlease enter a string: ");
    gets(str);

    while(strcmp(str, "") != 0) { // continues prompting until user enters an empty string
        wstr = strtok(str, " ");
        word_count = 0;
        while(wstr != NULL) { // iterates through word strings inside user input
            (*current_word).ptr = (char *)malloc((strlen(wstr)+1)*sizeof(char)); // dynamically allocates memory based on length of wstr
            strcpy((*current_word).ptr, wstr); // copies wstr into the character pointer of current word
            word_count++;
            (*current_word).pos_in_sentence = word_count; // sets word position
            (*current_word).num_char = (strlen(wstr)); // sets number of characters in word
            if(word_count == 1) { // first word of sentence
                (*current_sentence).word_ptr = current_word; // sets current_sentence pointer to first word
            }
            word *new_word = (word *)malloc(sizeof(word)); // dynamically allocates memory for a new word
            (*current_word).next_word = new_word; // points current word to new word
            current_word = (*current_word).next_word; // sets current word to the new word
            wstr = strtok(NULL, " ");
        }
        sentence_count++;
        (*current_sentence).num_words = word_count; // sets number of words in sentence
        (*current_sentence).pos_in_collection = sentence_count; // sets sentence position
        if(sentence_count == 1) { // points sentence list to first sentence
            (*l).first = current_sentence;
        }
        sentence *new_sentence = (sentence *)malloc(sizeof(sentence)); // dynamically allocates memory for a new sentence
        (*current_sentence).next_sentence = new_sentence; // points current sentence to new sentence
        current_sentence = (*current_sentence).next_sentence; // sets current sentence to new sentence
        printf("\nPlease enter a string: ");
        gets(str);
    }
    (*l).count = sentence_count;
    return l;
}

void print_sentences(LIST* l) {
    printf("\nThese are all the sentences entered: \n");
    int i = 1; // sentence iterator
    int j = 1; // word iterator
    sentence *s = (*l).first;
    while(i <= (*l).count) { // iterates though sentences
        word *w = (*s).word_ptr;
        while(j <= (*s).num_words) { // iterates though words
            printf("%s ", (*w).ptr); // prints word
            w = (*w).next_word; // moves to next word
            j++;
        }
        printf("\n");
        s = (*s).next_sentence; // moves to next sentence
        j = 1; // resets the word count to 1 since it's a new sentence
        i++;
    }
}

void search_word(LIST* l) {
    char str[1000] = "\0";
    printf("\nPlease enter a word to search for: ");
    gets(str);

    while(strcmp(str, "") != 0) { // continues prompting until user enters an empty string
        bool found = false;
        sentence *s = (*l).first; // sets sentence pointer to the first sentence
        word *w = (*s).word_ptr; // sets word pointer to the first word in the sentence
        int i = 1; // sentence iterator
        int j = 1; // word iterator
        while(i <= (*l).count) { // iterates though sentences
            while(j <= (*s).num_words) { // iterates though words
                if(strcmp((*w).ptr, str) == 0) { // comapres word to user input
                    printf("'%s' found in line %d position %d.\n", str, (*s).pos_in_collection, ((*w).pos_in_sentence));
                    found = true;
                }
                w = (*w).next_word;
                j++;
            }
            s = (*s).next_sentence;
            j = 1; // resets word count to 1 since it's a new sentence
            i++;
        }
        if(found == false) {
            printf("'%s' was not found in the lines entered.\n", str);
        }
        printf("\nPlease enter a word to search for: ");
        gets(str);
    }
}

void delete_sentence(LIST *l) {
    sentence *s1 = (*l).first;
    sentence *s2 = (*l).first;
    sentence *s3 = (*l).first;
    sentence *prev;
    int num_sentences = (*l).count;
    int line_number;
    printf("\nPlease enter a line number to delete: ");
    scanf(" %d", &line_number);
    if(line_number > (*l).count) {
        printf("Request denied. Please enter a number less than %d: ", (*l).count+1);
        scanf(" %d", &line_number);
    }
    int i = 1;
    while(i < (line_number-1)) { // iterates through list until it reaches the sentence before the one being deleted
        i++;
        s1 = (*s1).next_sentence;
    }
    prev = s1; // stores previous sentence
    int j = 1;
    while(j < line_number) { // iterates though list up to line number
        s2 = (*s2).next_sentence;
        j++;
    }
    if(s2 != (*l).first) {
        (*prev).next_sentence = (*s2).next_sentence; // points previous sentence to next
    }
    else {
        (*l).first = (*s2).next_sentence;
    }
    word *w = (*s2).word_ptr;
    while(j <= (*s2).num_words) { // iterates though words to free memory of deleted sentence
        word *current = w;
        word *next = (*w).next_word;
        free((*current).ptr); // frees string
        free(current); // frees word
        w = next; // moves to next word
        j++;
    }
    free(s2);
    int h = 1;
    for(int k = 1; k <= (*l).count-1; k++) { // for loop that adjusts all sentence numbers
        if((*s3).pos_in_collection > line_number) {
            (*s3).pos_in_collection = (*s3).pos_in_collection - 1;
        }
        s3 = (*s3).next_sentence;
    }
    print_sentences(l);
}

void free_memory(LIST *l) {
    int i = 1; // sentence iterator
    int j = 1; // word iterator
    int k = 1;
    sentence *s = (*l).first;
    while(i <= (*l).count) { // iterates though sentences
        word *w = (*s).word_ptr;
        while(j <= (*s).num_words) { // iterates though words
            word *current = w;
            word *next = (*w).next_word;
            free((*current).ptr); // frees string
            free(current); // frees word
            w = next; // moves to next word
            j++;
        }
        sentence *current_sentence = s;
        sentence *next_sentence = (*s).next_sentence;
        free(current_sentence); // frees sentence
        s = next_sentence;
        j = 1; // resets the word count to 1 since it's a new sentence
        i++;
    }
    free(l);
}

#endif
