#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook)
{
    AddressBook *add = addressBook;
    // Sort contacts based on the chosen criteria
    // buble sort
    for (int i = 0; i < add->contactCount - 1; i++)
    {
        for (int j = 0; j < add->contactCount - i - 1; j++)
        {
            if (strcmp(add->contacts[j].name, add->contacts[j + 1].name) > 0)
            {
                // swap contacts
                Contact temp = add->contacts[j];
                add->contacts[j] = add->contacts[j + 1];
                add->contacts[j + 1] = temp;
            }
        }
    }
    printf("-----------------------------------------------------------------------------\n");
    printf("|                               ADDRESS BOOK                                |\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("| %-3s | %-25s | %-10s | %-25s |\n", "S.No", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < add->contactCount; i++)
    {
        printf("|  %-3d | %-25s | %-10s | %-25s |\n",
               i + 1,
               add->contacts[i].name,
               add->contacts[i].phone,
               add->contacts[i].email);
    }
    printf("-----------------------------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    // sizeof(addressBook);
    char name[30], phone[11], email[30];
    int res;
    do
    {
        printf("Enter the name(lowercase) : ");
        scanf(" %[^\n]", name);

        res = validate_name(name);

    } while (res == 0);

    do
    {
        printf("Enter the phone : ");
        scanf("%s", phone);

        res = validate_phone(phone, addressBook);

    } while (res == 0);

    while (1)
    {
        printf("Enter the email : ");
        scanf("%s", email);
        res = validate_email(email, addressBook);
        if (res == 0)
        {
            printf("Invalid Email.\n");
        }
        else if (res == 1)
        {
            // printf("Valid Email.\n");
            break; // valid email..
        }
        else if (res == 2)
        {
            printf("Email already exists!\n");
        }
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */

    int choise;

    // print promt
    printf("\n-------- For Search Select one option ---------\n");
    printf("---------------------------------------\n");
    printf("|             SEARCH MODE             |\n");
    printf("---------------------------------------\n");
    printf("|   1   |   %-25s |\n", "SEARCH BY NAME ");
    printf("|   2   |   %-25s |\n", "SEARCH BY PHONE");
    printf("|   3   |   %-25s |\n", "SEARCH BY EMAIL");
    printf("---------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choise); //get the option from user

    switch (choise)
    {
    case 1:
        return search_by_name(addressBook);
        
    case 2:
        return search_by_phone(addressBook);
        
    case 3:
       return search_by_email(addressBook);
        
    default:
         printf("\n-------Plz Select Correct Option-------\n");
         return -1;
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    int choise;
    int index = searchContact(addressBook);
    if (index == -1)
    {
       printf("\nTry Again \n");
        return;
    }

    // print promt
        printf("\n--- Contact Found. Enter new details ---\n");

    printf("------------------------------------\n");
    printf("|              EDIT MODE           |\n");
    printf("------------------------------------\n");
    printf("|   1   |   %-22s |\n", "EDIT NAME ");
    printf("|   2   |   %-22s |\n", "EDIT PHONE");
    printf("|   3   |   %-22s |\n", "EDIT EMAIL");
    printf("|   4   |   %-22s |\n", "EDIT ALL");
    printf("------------------------------------\n");
    printf("Enter the choise: ");
    scanf("%d", &choise);

    switch (choise)
    {
    case 1:
        Edit_name(addressBook, index);
        break;
    case 2:
        Edit_phone(addressBook, index);
        break;
    case 3:
        Edit_email(addressBook, index);
        break;
    case 4:
        Edit_all(addressBook, index);
        break;
    default:
        printf("Invalid Input\n");
    }
    printf("\nContact edited successfully!\n");
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    char repeat;
    do
    {
        int index = searchContact(addressBook);

        if (index == -1)
        {
            // printf("\nContact not Found.\n");
            return;
        }

        char ch;

        printf("\nPress (Y) for Delete\nPress (N) Keep This Contact\n");
        printf("Enter your choice: ");
        scanf(" %c", &ch);

        if (ch == 'N' || ch == 'n')
        {
            printf("\nNo changes Made\n");
            return;
        }
        else
        {

            for (int i = index; i < addressBook->contactCount - 1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;

            printf("Contact deleted successfully.\n");
        }
        printf("\n----You Want to Detele Another Contact?----\n");
        printf("\nFor Yes press 'Y'\nFor No press 'N'\n");
        scanf(" %c", &repeat);
    } while (repeat == 'Y' || repeat == 'y');
}

int validate_name(char *name)
{
    // LOOP till name[i] != '\0'
    //     check name[i] is not in the range of A to Z, a to z, ' ', '.'
    //         return 0; // invalid
    // END LOOP

    for (int i = 0; name[i]; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ' || (name[i] >= 'a' && name[i] <= 'z') || name[i] == '.'))
        {
            printf("Invalid name\n");
            return 0; // invalid
        }
    }

    return 1; // valid
}
int validate_phone(char *phone, AddressBook *AddressBook)
{
    // pho length
    if (strlen(phone) != 10)
    {
        printf("Invalid Contact Length!\n");
        return 0;
    }
    // check digit

    // Loop till str[i] != '\0'
    //     check the str[i] is not in the rage '0' to '9'
    //         return 1; invalid
    for (int i = 0; phone[i]; i++)
    {
        if (!((phone[i] >= '0' && phone[i] <= '9')))
        {
            printf("Invalid Phone No!\n");
            return 0; // invalid
        }
    }
    // unique check
    for (int i = 0; i < AddressBook->contactCount; i++)
    {
        if (strcmp(phone, AddressBook->contacts[i].phone) == 0)
        {
            printf("Duplicate Phone No!\n");
            return 0;
        }
    }
    return 1; // valid
}
int validate_email(char *email, AddressBook *addressBook)
{
    int atCount = 0;
    int atPos = -1;
    int dotPos = -1;
    int len = strlen(email);

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
            atPos = i;
        }
        // if (email[atPos - 1] == '.')
        //     return 0;

        // if (email[atPos + 1] == '.')
        //     return 0;

        else if (email[i] == '.')
        {
            dotPos = i;

            /* Check for consecutive dots */
            if (i < len - 1)
            {
                if (email[i] == email[i + 1])
                {
                    return 0;
                }
            }
        }
        else if (!((email[i] >= 'a' && email[i] <= 'z') ||
                   (email[i] >= '0' && email[i] <= '9') ||
                   (email[i] == '@') ||
                   (email[i] == '.')))
        {
            return 0;
        }
    }

    if (atCount != 1)
        return 0;

    if (atPos == 0 || atPos == len - 1)
        return 0;
    if (email[atPos - 1] == '.')
        return 0;

    if (email[atPos + 1] == '.')
        return 0;

    if (dotPos <= atPos + 1 || dotPos == len - 1)
        return 0;

    /* Duplicate email check */
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 2;
        }
    }

    return 1;
}

int search_by_name(AddressBook *addressBook)
{
    char name[30];
    int count = 0;
    int index;
    int duplicate[MAX_CONTACTS];

    printf("Enter the name to Search(Lowercase): ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name) != NULL)
        {
            duplicate[count] = i;
            index = i;
            count++;
        }
    }

    if (count == 0)
    {
        printf("\nNo Matching Contact Found..!\n");
        return -1;
    }

    else if (count == 1)
    {
        printf("\nOne matching contact found.\n");

        printf("-----------------------------------------------------------------------------\n");
        printf("| %-3s | %-25s | %-10s | %-25s |\n",
               "S.No", "Name", "Phone", "Email");
        printf("-----------------------------------------------------------------------------\n");

        printf("| %-3d | %-25s | %-10s | %-25s |\n",
               index + 1,
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);

        printf("-----------------------------------------------------------------------------\n");

        return index;
    }

    else
    {
        printf("\nMultiple Contacts Found..!\n");

        printf("-----------------------------------------------------------------------------\n");
        printf("| %-3s | %-25s | %-10s | %-25s |\n",
               "S.No", "Name", "Phone", "Email");
        printf("-----------------------------------------------------------------------------\n");

        for (int i = 0; i < count; i++)
        {
            index = duplicate[i];

            printf("| %-4d | %-25s | %-10s | %-25s |\n",
                   i + 1,
                   addressBook->contacts[index].name,
                   addressBook->contacts[index].phone,
                   addressBook->contacts[index].email);

            printf("-----------------------------------------------------------------------------\n");
        }

        while (1)
        {
            int choice;

            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            if (choice >= 1 && choice <= count)
            {
                int selectedIndex = duplicate[choice - 1];

                printf("\nSelected Contact:\n");

                printf("-----------------------------------------------------------------------------\n");
                printf("| %-3s | %-25s | %-10s | %-25s |\n",
                       "S.No", "Name", "Phone", "Email");
                printf("-----------------------------------------------------------------------------\n");

                printf("| %-4d | %-25s | %-10s | %-25s |\n",
                       selectedIndex + 1,
                       addressBook->contacts[selectedIndex].name,
                       addressBook->contacts[selectedIndex].phone,
                       addressBook->contacts[selectedIndex].email);

                printf("-----------------------------------------------------------------------------\n");

                return selectedIndex;
            }

            printf("Invalid Input..!\n");
        }
    }
}

int search_by_phone(AddressBook *addressBook)
{
    char str[11];

    // Get the phone number
    printf("Enter the phoneNO to search: ");
    scanf("%s", str);

    // Loop from 0 to cc - 1
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, str) == 0)
        {
            // print the contact
            printf("-----------------------------------------------------------------------------\n");
            printf("|                               ADDRESS BOOK                                |\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-4d | %-25s | %-10s | %-25s |\n", i + 1, addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            printf("-----------------------------------------------------------------------------\n");
            // printf("\n%d\t%s\t%s\t%s\n", i + 1,
            //        addressBook->contacts[i].name,
            //        addressBook->contacts[i].phone,
            //        addressBook->contacts[i].email);
            return i;
        }
    }
    printf("\n No Contacts Found!\n\n");
    return -1;
}

int search_by_email(AddressBook *addressBook)
{
    char str[30];
    printf("Enter Email to search: ");
    scanf(" %[^\n]", str);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, str) == 0)
        {
            printf("-----------------------------------------------------------------------------\n");
            printf("|                               ADDRESS BOOK                                |\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-3d | %-25s | %-10s | %-25s |\n", i + 1, addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            printf("-----------------------------------------------------------------------------\n");

            return i;
        }
    }
    printf("\n No Contacts Found!\n\n");
    return -1;
}

void Edit_name(AddressBook *addressBook, int index)
{

    while (1)
    {
        printf("contact found.\n");
        char newName[30];
        printf("Enter new name: ");
        scanf(" %[^\n]", newName);

        if (validate_name(newName))
        {
            strcpy(addressBook->contacts[index].name, newName);
            printf("---------------------------------------\n");
            printf("|           CONTACT DETAILS           |\n");
            printf("---------------------------------------\n");
            printf("| S.No    | %-25d |\n", index + 1);
            printf("| NAME    | %-25s |\n", addressBook->contacts[index].name);
            printf("| PHONE   | %-25s |\n", addressBook->contacts[index].phone);
            printf("| EMAIL   | %-25s |\n", addressBook->contacts[index].email);
            printf("---------------------------------------\n");
            break;
        }
        else
        {
              printf("Try again.\n"); //Invalid Name. 
        }
    }
}

void Edit_phone(AddressBook *addressBook, int index)
{

    while (1)
    {
        printf("contact found.\n");
        char newphone[11];
        printf("Enter new phone: ");
        scanf("%s", newphone);

        if (validate_phone(newphone, addressBook))
        {
            strcpy(addressBook->contacts[index].phone, newphone);
            printf("---------------------------------------\n");
            printf("|           CONTACT DETAILS           |\n");
            printf("---------------------------------------\n");
            printf("| S.No    | %-25d |\n", index + 1);
            printf("| NAME    | %-25s |\n", addressBook->contacts[index].name);
            printf("| PHONE   | %-25s |\n", addressBook->contacts[index].phone);
            printf("| EMAIL   | %-25s |\n", addressBook->contacts[index].email);
            break;
        }
        else
        {
              printf("Invalid Phone No.Try again.\n");  //Invalid Phone No.
        }
    }
}

void Edit_email(AddressBook *addressBook, int index)
{

    while (1)
    {

        char newemail[30];
        printf("Enter new email: ");
        scanf("%s", newemail);

        if (validate_email(newemail, addressBook))
        {
            strcpy(addressBook->contacts[index].email, newemail);
            printf("---------------------------------------\n");
            printf("|           CONTACT DETAILS           |\n");
            printf("---------------------------------------\n");
            printf("| S.No    | %-25d |\n", index + 1);
            printf("| NAME    | %-25s |\n", addressBook->contacts[index].name);
            printf("| PHONE   | %-25s |\n", addressBook->contacts[index].phone);
            printf("| EMAIL   | %-25s |\n", addressBook->contacts[index].email);
            printf("---------------------------------------\n");
            break;
        }
        else
        {
             printf("Invalid Email address.Try again.\n");//Invalid Email address.
        }
    }
}

void Edit_all(AddressBook *addressBook, int index)
{
    char newName[30], newphone[11], newemail[30];

    while (1)
    {

        printf("Enter new name: ");
        scanf(" %[^\n]", newName);

        if (validate_name(newName))
        {
            break;
        }
        else
        {
             printf("Try again.\n");
        }
    }

    while (1)
    {

        printf("Enter new phone: ");
        scanf("%s", newphone);

        if (validate_phone(newphone, addressBook))
        {
            break;
        }
        else
        {
            printf("Invalid Phone No.Try again.\n");
        }
    }

    while (1)
    {

        printf("Enter new email: ");
        scanf("%s", newemail);

        if (validate_email(newemail, addressBook))
        {
            break;
        }
        else
        {
            printf("Invalid Email address.Try again.\n");
        }
    }
    strcpy(addressBook->contacts[index].name, newName);
    strcpy(addressBook->contacts[index].phone, newphone);
    strcpy(addressBook->contacts[index].email, newemail);

    printf("---------------------------------------\n");
    printf("|           CONTACT DETAILS           |\n");
    printf("---------------------------------------\n");
    printf("| S.No    | %-25d |\n", index + 1);
    printf("| NAME    | %-25s |\n", addressBook->contacts[index].name);
    printf("| PHONE   | %-25s |\n", addressBook->contacts[index].phone);
    printf("| EMAIL   | %-25s |\n", addressBook->contacts[index].email);
    printf("---------------------------------------\n");
}
