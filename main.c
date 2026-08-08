#include <stdio.h>
#include<unistd.h>
#include "contact.h"
#include "file.h"

int main()
{
    for (int i = 0; i <= 100; i++)
    {
        printf("[Loading.........................%d%%]\r",i);
        usleep(10000);
        fflush(stdout);
        
    }
    int choice;
    AddressBook addressBook;

    initialize(&addressBook); // Initialize the address book

    do
    {
        printf("\n\n------------------------------------\n");
        printf("|           ADDRESSBOOK MENU       |\n");
        printf("------------------------------------\n");
        printf("|   1   |   %-22s |\n", "CREATE CONTACT");
        printf("|   2   |   %-22s |\n", "SEARCH CONTACT");
        printf("|   3   |   %-22s |\n", "EDIT CONTACT");
        printf("|   4   |   %-22s |\n", "DELETE CONTACT");
        printf("|   5   |   %-22s |\n", "LIST ALL CONTACTS");
        printf("|   6   |   %-22s |\n", "SAVE AND EXIT");
        printf("|   7   |   %-22s |\n", "EXIT");
        printf("------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printf("Saving and Exiting...\n");
            saveContactsToFile(&addressBook);
            break;
        case 7:
            printf("Exit\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
