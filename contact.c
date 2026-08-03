#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria

    // Bubble sort

   
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char str[30], str1[11], str2[30];
    int res;
    do{
        printf("Enter the name : ");
        scanf("%s", str);

         res = validate_name(str);

    }while(res == 0);
   
    

    printf("Enter the phone : ");
    scanf("%s", str1);

    printf("Enter the email : ");
    scanf("%s", str2);


    


    addressBook->contactCount++;



    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    int choise;

    // print promt

    scanf("%d", &choise);

    switch(choise)
    {
        case 1:
           // search_by_name(addressBook);
            break;
        case 2:
           // search_by_phone(addressBook);
            break;
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}




int validate_name(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        if(!((str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' '))
        {
            printf("Invalid name\n");
            return 0; // invalid
        }
    }

    return 1; // valid


}

int search_by_name(AddressBook *addressBook)
{
    char str[30];

    //Get the name

//    // Loop from 0 to cc-1
//         if (str == addressBook->contacts[i].name)
//         {
//            // print the contact
//             count++;
//             // return i;
//         }

//     count ==> 0 ==> return -1;
//     count ==> more then 1 ==> return search_by_phone(addressBook);
   // count ==> 1 ==> return matching index
}


int search_by_phone(AddressBook * addressBook)
{
    char str[11];

    //Get the phone number 

    // Loop from 0 to cc-1
    //     if (str == addressBook->contacts[i].phone)
    //     {
    //         print the contact
    //         return i;
    //     }

    return -1;
}