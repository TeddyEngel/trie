/****************************************************************************
 * trie.h
 *
 * Teddy Engel
 *
 * Declares a trie's functionality.
 ***************************************************************************/

#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHARACTERS 27

/**
 * Trie structure
 */
typedef struct node
{
    int total_size; // stores slightly more per node but allows to retrieve the size super fast
    bool is_word;
    struct node* children[MAX_CHARACTERS];
}
node;

/**
 * Creates a new trie node
 */
node* create_trie_node();

/**
 * Returns the current trie size
 */
unsigned int get_trie_size(node* root);

/**
 * Adds a character to the trie node
 */
node* add_char_to_trie_node(char c, node* current_node);

/**
 * Adds a word to the trie
 */
void add_word_to_trie(char* word, node* root);

/**
 * Checks if the trie has the passed word
 */
bool has_word_in_trie(char* word, node* root);

/**
 * Frees a trie node recursively (also calling it on its child)
 */
void free_trie_node(node* current_node);

#endif // TRIE_H
