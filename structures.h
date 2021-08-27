/* CS2211a 2020 */
/* Rowena Shi */
/* November 30, 2020 */ 

// this file defines the structures word and sentences

#ifndef structures
#define structures

typedef struct word {
    char *ptr;
    int num_char;
    int pos_in_sentence;
    struct word *next_word;
} word;

typedef struct sentence {
    word *word_ptr;
    int num_words;
    int pos_in_collection;
    struct sentence *next_sentence;
} sentence;

typedef struct {
    struct sentence *first;
    int count;
} LIST;

#endif
