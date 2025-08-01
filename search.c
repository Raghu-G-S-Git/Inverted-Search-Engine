#include "inverted_search.h"

// Function to search for a word in the database
int search_word(Main_node *link, char *word, int key)
{
    Main_node *temp_main = link;

    // Traverse main node linked list
    while (temp_main != NULL)
    {
        // Check if word matches
        if(strcmp(temp_main->word, word) == 0)
        {
            printf("\nINFO: Found The Word \"%s\" In Database\n",word);
            Sub_node *temp_sub = temp_main->sub_link;

            int first_entry = 1; // Flag to track first sub-node entry

            // Print search results in formatted table
            printf("\n-------------------------------------------------------------------------------------------------------------------\n");
            printf("%-20s%-31s%-24s%-30s%-15s\n", "KEY", "WORD", "FILE COUNT", "FILE NAME", "WORD COUNT");
            printf("-------------------------------------------------------------------------------------------------------------------\n");
            while (temp_sub != NULL)
            {
                // Print main node details only for first sub-node
                if (first_entry) 
                {
                    printf("%-20d%-35s%-20d", key, temp_main->word, temp_main->file_count);
                    first_entry = 0;
                } 
                else 
                {
                    printf("%-20s%-35s%-20s", "", "", "");
                }

                // Print sub-node details
                printf("%-35s%-20d\n", temp_sub->file_name, temp_sub->word_count);

                temp_sub = temp_sub->link;
            }
            printf("-------------------------------------------------------------------------------------------------------------------\n");
                
            return SUCCESS;
        }    

        temp_main = temp_main->main_link;
    }

    // Word not found
    printf("INFO: Not Found The Word \"%s\" In Database\n\n",word);
    return FAILURE;
}