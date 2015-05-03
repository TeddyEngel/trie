/****************************************************************************
 * trie.c
 *
 * Teddy Engel
 *
 * Implements a trie's functionality.
 ***************************************************************************/

#include "trie.h"

/**
 * Creates a new trie node
 */
node* create_trie_node()
{
    // allocate the node
    node* new_node = malloc(sizeof(node));
    // initialize all members
    new_node->total_size = 0;
    new_node->is_word = false;
    for (int i = 0; i < MAX_CHARACTERS; i++)
        new_node->children[i] = 0;
    return new_node;
}

/**
 * Returns the current trie size
 */
unsigned int get_trie_size(node* root)
{
    return root->total_size;
}

/**
 * Translates a character to a trie index
 */
int get_char_index(char c)
{
    if (c == '\'')
    {
        return 26;
    }
    return (int)tolower(c) - 'a';
}


/**
 * Adds a character to the trie node
 */
node* add_char_to_trie_node(char c, node* current_node)
{
    if (!current_node)
    {
        return 0;
    }
    // if the current node doesn't have a children yet for that character, we create it
    int index = get_char_index(c);

    if (current_node->children[index] == 0)
    {
        current_node->children[index] = create_trie_node();
    }
    return current_node->children[index];
}

/**
 * Adds a word to the trie
 */
void add_word_to_trie(char* word, node* root)
{
    if (!word || !root)
    {
        return;
    }
    node* current_node = root;

    // loop through all the word's characters
    for (int i = 0, n = strlen(word); i < n && current_node && (isalpha(word[i]) || word[i] == '\''); i++)
    {
        current_node = add_char_to_trie_node(word[i], current_node);
    }
    if (!current_node->is_word)
    {
        current_node->is_word = true;
        // only increase the number of words if the flag was set to off
        root->total_size++;
    }
}

/**
 * Checks if the trie has the passed word
 */
bool has_word_in_trie(char* word, node* root)
{
    if (!word || !root)
    {
        return false;
    }

    node* current_node = root;
    for (int i = 0, n = strlen(word), index = 0; i < n && current_node; i++)
    {
        // find the index of current character
        index = get_char_index(word[i]);

        // if there is a children to current node for that character
        if (current_node->children[index] != 0)
        {
            // change node to child
            current_node = current_node->children[index];
        }
        else
        // otherwise, means the word isn't found in the dictionary
            return false;
    }
    return current_node->is_word;
}

/**
 * Frees a trie node recursively (also calling it on its child)
 */
void free_trie_node(node* current_node)
{
    if (!current_node)
        return;
    // recursively call free on sub-nodes to free children
    for (int i = 0; i < MAX_CHARACTERS; i++)
    {
        free_trie_node(current_node->children[i]);
        current_node->children[i] = 0;
    }
    // free the node
    free(current_node);
}
