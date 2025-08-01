#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH

// Define success and failure status codes
#define SUCCESS 0
#define FAILURE -1

// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure for sub-node containing file-specific word count and filename
typedef struct s_node
{
    int word_count;        // Number of occurrences of the word in the file
    char file_name[25];    // Name of the file
    struct s_node *link;   // Pointer to the next sub-node
}Sub_node;

// Structure for main node containing word and file count
typedef struct m_node
{
    int file_count;         // Number of files containing the word
    char word[25];          // The word itself
    struct m_node *main_link; // Pointer to the next main node
    struct s_node *sub_link;  // Pointer to the linked list of sub-nodes
}Main_node;

// Structure for hash table entry
typedef struct table
{
    int key;                // Hash key
    struct m_node *link;    // Pointer to the linked list of main nodes
}Hash_t;

// Structure for file list node
typedef struct f_node
{
    char filename[25];      // Name of the file
    struct f_node *link;    // Pointer to the next file node
}Flist;

// Function prototypes
int insert_at_last(Flist **head, char *file_name); // Insert file at the end of file list
void print_list(Flist **head);                     // Print the file list
void create_HT(Hash_t *HT);                        // Initialize hash table
void update_database(Hash_t key_table[], Flist **files); // Update database with file contents
int insert_node(Hash_t key_table[], char *filename, char *word, int key); // Insert word into hash table
void display_data(Hash_t key_table[]);             // Display the database contents
int search_word(Main_node *link, char *word, int key); // Search for a word in the database
void save_db(FILE *db_fptr, Hash_t key_table[], Flist *files, Flist *deleted_files); // Save database to file
void update_old(Hash_t key_table[], FILE *db_fptr, Flist **file_head, Flist **deleted_file); // Update database from file
void delete_element(Flist **head, char *data);     // Delete a file from the file list

#endif