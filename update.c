#include "inverted_search.h"

// Function to update database from a file
void update_old(Hash_t key_table[], FILE *db_fptr, Flist **file_head, Flist **deleted_file)
{
    char ch, file_name[100];

    // Read first line containing file names
    if ((ch = fgetc(db_fptr)) == '#') 
    {
        while (1)
        {
            // Read file name until delimiter
            if (fscanf(db_fptr, "%[^;#]", file_name) != 1)
                break;

            // Update file lists
            insert_at_last(deleted_file, file_name);
            delete_element(file_head, file_name);
            ch = fgetc(db_fptr);  // Read the delimiter ; or #

            if (ch == '#') break;
        }
    }
    // Read remaining database entries
    while ((ch = fgetc(db_fptr)) != EOF) 
    {
        if (ch != '#') continue;

        int key, file_count, word_count;
        char word[100], sub_file[100];

        // Read main node data
        if (fscanf(db_fptr, "%d;%[^;];%d;", &key, word, &file_count) != 3)
            continue;

        // Allocate and initialize new main node
        Main_node *new_main = malloc(sizeof(Main_node));
        if(new_main == NULL)
        {
            printf("INFO: Couldn't Create Main Node\n");
            exit(1);
        }

        // Insert main node into hash table
        if(key_table[key].link == NULL)
        {
            key_table[key].link = new_main;
        }
        else
        {
            Main_node *temp = key_table[key].link;
            while(temp->main_link != NULL)
                temp = temp->main_link;
            temp->main_link = new_main;
        }
        
        new_main->file_count = file_count;
        strcpy(new_main->word, word);
        new_main->main_link = NULL;
        new_main->sub_link = NULL;
        
        // Read and insert sub-nodes
        for (int i = 0; i < file_count; i++) 
        {
            fscanf(db_fptr, "%[^;];%d;", sub_file, &word_count);

            // Allocate and initialize new sub-node
            Sub_node *new_sub = malloc(sizeof(Sub_node));
            if(new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                Sub_node *temp = new_main->sub_link;
                while(temp->link != NULL)
                    temp = temp->link;
                temp->link = new_sub;
            }
                
            new_sub->word_count = word_count;
            strcpy(new_sub->file_name, sub_file);
            new_sub->link = NULL;
        }
        
        // Skip until ending delimiter
        while ((ch = fgetc(db_fptr)) != '#' && ch != EOF);
    }
}

// Function to delete a file from the file list
void delete_element(Flist **head, char *data)
{
    // Check if list is empty
    if(*head == NULL)
    {
        return ;
    }
    
    // Handle deletion of the head node
    Flist *temp = *head,*last;
    
    if(strcmp((*head)->filename, data) == 0)
    {
        *head = (*head)->link;
        free(temp);
        return ;
    }
    
    // Handle deletion of other nodes
    while(temp != NULL)
    {
        if(strcmp((*head)->filename, data) == 0)
        {
            last->link = temp->link;
            free(temp);
            return;
        }
        last = temp;
        temp = temp->link;
    }
}