#include "inverted_search.h"

// Function to display the database contents in a formatted table
void display_data(Hash_t key_table[])
{
    // Print table header with wide spacing
    printf("\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s%-31s%-24s%-30s%-15s\n", "KEY", "WORD", "FILE COUNT", "FILE NAME", "WORD COUNT");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    // Iterate through each key in the hash table
    for (int key = 0; key < 28; key++)
    {
        Main_node *temp_main = key_table[key].link;

        // Traverse the main node linked list
        while (temp_main != NULL)
        {
            Sub_node *temp_sub = temp_main->sub_link;

            int first_entry = 1; // Flag to track first sub-node entry

            // Traverse the sub-node linked list
            while (temp_sub != NULL)
            {
                // Print main node details only for the first sub-node
                if (first_entry) {
                    printf("%-20d%-35s%-20d", key, temp_main->word, temp_main->file_count);
                    first_entry = 0;
                } else {
                    printf("%-20s%-35s%-20s", "", "", "");
                }

                // Print sub-node details
                printf("%-35s%-20d\n", temp_sub->file_name, temp_sub->word_count);

                temp_sub = temp_sub->link;
            }

            temp_main = temp_main->main_link;
        }
    }
    // Print table footer
    printf("-------------------------------------------------------------------------------------------------------------------\n");
}