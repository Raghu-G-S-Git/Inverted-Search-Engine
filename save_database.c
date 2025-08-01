#include "inverted_search.h"

// Function to save the database to a file
void save_db(FILE *db_fptr, Hash_t key_table[], Flist *files, Flist *deleted_files)
{
    Flist *temp_file = deleted_files;
    // Write deleted files list
    fprintf(db_fptr,"#");
    while(temp_file != NULL)
    {
        fprintf(db_fptr,"%s;", temp_file->filename);
        temp_file = temp_file->link;
    }
    // Write active files list
    temp_file = files;
    while(temp_file != NULL)
    {
        fprintf(db_fptr,"%s;", temp_file->filename);
        temp_file = temp_file->link;
    }
    // Remove trailing semicolon and add section delimiter
    fseek(db_fptr,-1,SEEK_CUR);
    fprintf(db_fptr,"#");
    
    // Iterate through each key in the hash table
    for (int key = 0; key < 28; key++)
    {
        Main_node *temp_main = key_table[key].link;

        // Traverse the main node linked list
        while (temp_main != NULL)
        {
            Sub_node *temp_sub = temp_main->sub_link;

            int first_entry = 1; // Flag to track first sub-node entry

            fprintf(db_fptr,"\n");
            // Traverse the sub-node linked list
            while (temp_sub != NULL)
            {
                // Write main node details only for the first sub-node
                if (first_entry) 
                {
                    fprintf(db_fptr,"#%d;%s;%d", key, temp_main->word, temp_main->file_count);
                    first_entry = 0;
                }

                // Write sub-node details
                fprintf(db_fptr,";%s;%d", temp_sub->file_name, temp_sub->word_count);

                temp_sub = temp_sub->link;
            }
            // Add section delimiter
            fprintf(db_fptr,"#");

            temp_main = temp_main->main_link;
        }
    }
}