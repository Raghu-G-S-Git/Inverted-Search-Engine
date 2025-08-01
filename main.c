#include "inverted_search.h"

// Main program entry point
int main(int argc, char *argv[])
{
    FILE *fptr;
    // Validate command-line arguments
    if(argc < 2)
    {
        printf("\n\t\t-INVALID INPUT METHOD-\n\nPass Argument like: ./a.out <file1.txt> <file2.txt> ....\n\n");
        exit(1);
    }

    Flist *files = NULL;
    Flist *deleted_files = NULL;

    // Process input files
    for(int i=1; i<argc; i++)
    {
        // Check file extension
        if(strstr(argv[i],".txt") == NULL)
        {
            printf("\nWARNING : Invalid File Extension Type Of %s File\n",argv[i]);
            continue;
        }
        // Check if file can be opened
        if((fptr = fopen(argv[i],"r")) == NULL)
        {
            printf("\nWARNING : Could Not Find %s File\n",argv[i]);
            continue;
        }
        // Check if file is empty
        fseek(fptr,0,SEEK_END);
        if(ftell(fptr) == 0)
        {
            printf("\nWARNING : %s Is Empty File\n",argv[i]);
            continue;
        }

        // Insert file into list
        if(insert_at_last(&files,argv[i]) == FAILURE)
        {
            printf("\nWARNING : %s File Already Exists\n",argv[i]);
            continue;
        }
        printf("\nINFO : %s Successfully insterted in list\n",argv[i]);
    }

    Hash_t key_table[28];
    int option,flag = 1, create_flag = 1;
    
    // Main menu loop
    do
    {
        // Display menu options
        printf("-------------------------------------------------------------------------------------------------------------------\n");
        printf("\n1. Create Database\n2. Display Database\n3. Update Database\n4. Search Word\n5. Save Database\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&option);
       
        // Create database option
        if(option == 1)
        {
            if(!create_flag)
            {
                printf("\nINFO: Creating Operation Is Not Possible. Database Already Exists.\n\n");
                continue;
            }
            if(flag)
                create_HT(key_table);
        
            update_database(key_table, &files);
            flag = 0;
            create_flag = 0;
            printf("\nINFO: Successfully Created Database\n");
        }

        // Display database option
        else if(option == 2)
        {
            if(flag)
            {
                printf("\nINFO: Database Is Not Created\n\n");
            }
            else
            {
                display_data(key_table);
            }
        }

        // Update database option
        else if(option == 3)
        {
            if(!flag)
            {
                printf("\nINFO: Updating Operation Is Not Possible. Database Already Exists.\n\n");
                continue;
            }

            char name[25];
            printf("\nEnter The Database File Name: ");
            scanf("%s",name);

            // Validate file extension
            if(strstr(name, ".txt") == NULL)
            {
                printf("\nINFO: Invalide File Type.\n");
                exit(1);
            }

            // Open database file
            FILE *db_fptr ;
            db_fptr = fopen(name,"r");
            if(db_fptr == NULL)
            {
                printf("\nINFO: Couldn't Open The File. Exiting...\n\n");
                exit(1);
            }

            // Validate database file format
            char first,last;
            first = fgetc(db_fptr);
            fseek(db_fptr,-1,SEEK_END);
            last = fgetc(db_fptr);

            if(first != '#' || last != '#')
            {
                printf("\nINFO: Invalide Database File.\n");
                exit(1);
            }
            rewind(db_fptr);

            create_HT(key_table);

            // Update database structure
            update_old(key_table, db_fptr, &files, &deleted_files);
            flag = 0;

            fclose(db_fptr);
            print_list(&files);
            printf("\nINFO: Updated Database File \"%s\" In Structure ...\n\n",name);
        }

        // Search word option
        else if(option == 4)
        {
            char word[25];
            printf("\nEnter the word: ");
            scanf("%s",word);

            // Calculate hash key
            int key;
            if(isupper(word[0]))    key = word[0] - 64;
            else if(islower(word[0]))   key = word[0] - 96;
            else if(isdigit(word[0]))   key = 0;
            else    key = 27;

            // Perform search
            search_word(key_table[key].link, word, key);
        }

        // Save database option
        else if(option == 5)
        {
            char name[25];
            printf("\nEnter The <File_Name.txt> To Store Database: ");
            scanf("%s",name);

            // Validate file extension
            if(strstr(name, ".txt") == NULL)
            {
                printf("\nINFO: Invalide File Type.\n");
                exit(1);
            }

            // Open file for writing
            FILE *db_fptr ;
            db_fptr = fopen(name,"w");
            if(db_fptr == NULL)
            {
                printf("\nINFO: Couldn't Open The File. Exiting...\n\n");
                exit(1);
            }

            // Save database
            save_db(db_fptr, key_table, files, deleted_files);
            fclose(db_fptr);
            printf("\nINFO: Saved Database In \"%s\" File...\n\n",name);
        }

        // Exit option
        else if(option == 0)
        {
            printf("\nINFO: Exiting....\n\n");
            exit(1);
        }
        
        // Invalid option
        else
        {
            printf("INFO: Invalid Option. Try Again...\n");
        }
            
        getchar();
        
    } while (1);
}