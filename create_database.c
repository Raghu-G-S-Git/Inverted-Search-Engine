#include "inverted_search.h"

// Function to insert a file at the end of the file list
int insert_at_last(Flist **head, char *file_name)
{
    // Allocate new node
    Flist *new = malloc(sizeof(Flist));
    
    // Validate allocation
    if(new == NULL)
        return FAILURE;
        
    // Update node data
    strcpy(new->filename,file_name);
    new->link = NULL;
    
    // Handle empty list
    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        Flist *temp = *head;
        
        // Check for duplicate files
        while(temp->link != NULL)
        {
            if(strcmp(temp->filename,new->filename) == 0)
            {
                free(new);
                return FAILURE;
            }
            temp = temp->link;
        }
        temp->link = new;
        return SUCCESS;
    }
    return SUCCESS;
}

// Function to print the file list
void print_list(Flist **head)
{
    Flist *temp = *head;
    if (temp == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        printf("\nFILE LIST : HEAD -> ");
        // Traverse and print each file
        while (temp)		
        {
            printf("%s -> ", temp->filename);
            temp = temp -> link;
        }
        printf("NULL\n\n");
    }
}

// Function to initialize the hash table
void create_HT(Hash_t *HT)
{
    // Initialize each hash table entry
    for(int i=0; i<28; i++)
    {
        HT[i].key = i;
        HT[i].link = NULL;
    }
}

// Function to update database with file contents
void update_database(Hash_t key_table[], Flist **files)
{
    Flist *temp = *files;

    // Check if file list is empty
    if (temp == NULL)
    {
        printf("INFO : Files List is empty\n");
        return;
    }
    
    // Process each file
    while(temp != NULL)
    {
        FILE *fptr = fopen(temp->filename,"r");
        if(fptr == NULL)
        {
            printf("\nWARNING : Could Not Open %s File\n",temp->filename);
            exit(1);
        }

        rewind(fptr);
        char word_buf[25];
        // Read words from file
        while(fscanf(fptr,"%s",word_buf) == 1)
        {
            int key;
            
            // Calculate hash key based on first character
            if(isupper(word_buf[0]))    key = word_buf[0] - 64;
            else if(islower(word_buf[0]))   key = word_buf[0] - 96;
            else if(isdigit(word_buf[0]))   key = 0;
            else    key = 27;

            // Insert word into hash table
            insert_node(key_table, temp->filename, word_buf, key);
        }

        temp = temp->link;
        fclose(fptr);
    }
}

// Function to insert a word into the hash table
int insert_node(Hash_t key_table[], char *filename, char *word, int key)
{   
    // Handle empty hash table entry
    if(key_table[key].link == NULL)
    {
        Main_node *new_main = malloc(sizeof(Main_node));
        if(new_main == NULL)
            return FAILURE;
        
        new_main->file_count = 1;
        strcpy(new_main->word, word);
        new_main->main_link = NULL;
        
        Sub_node *new_sub = malloc(sizeof(Main_node));
        if(new_sub == NULL)
            return FAILURE;

        new_sub->word_count = 1;
        strcpy(new_sub->file_name, filename);
        new_sub->link = NULL;

        new_main->sub_link = new_sub;

        key_table[key].link = new_main;

        return SUCCESS;
    }
   
    Main_node *temp = key_table[key].link, *prev = key_table[key].link;
    
    // Search for existing word
    while(temp != NULL)
    {
        if(strcmp(temp->word, word) == 0)
        {
            Sub_node *temp_sub = temp->sub_link, *prev_sub = temp->sub_link;
            
            // Search for existing file
            while(temp_sub != NULL)
            {
                if(strcmp(temp_sub->file_name, filename) == 0)
                {
                    temp_sub->word_count++;
                    return SUCCESS;
                }

                prev_sub = temp_sub;
                temp_sub = temp_sub->link; 
            }

            // Add new file entry
            Sub_node *new_sub = malloc(sizeof(Sub_node));
            if(new_sub == NULL)
                return FAILURE;
            
            new_sub->word_count = 1;
            strcpy(new_sub->file_name, filename);
            new_sub->link = NULL;

            prev_sub->link = new_sub;
            
            temp->file_count++;

            return SUCCESS;
        }

        prev = temp;
        temp = temp->main_link;
    }
    
    // Add new word entry
    Main_node *new_main = malloc(sizeof(Main_node));
    if(new_main == NULL)
        return FAILURE;

    new_main->file_count = 1;
    strcpy(new_main->word, word);
    new_main->main_link = NULL;
    
    Sub_node *new_sub = malloc(sizeof(Main_node));
    if(new_sub == NULL)
        return FAILURE;

    new_sub->word_count = 1;
    strcpy(new_sub->file_name, filename);
    new_sub->link = NULL;
    
    new_main->sub_link = new_sub;
    
    prev->main_link = new_main;
    
    return SUCCESS;
}