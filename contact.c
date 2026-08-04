#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

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
    printf("*****************************************************************************\n");
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
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    // loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    char name[30], phone[11], email[30];
    int res;
    do
    {
        printf("Enter the name : ");
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
    printf("1.Search_by_name\n");
    printf("2.Search_by_phone\n");
    printf("3.search_by_email\n");
    printf("Enter the choise: ");
    scanf("%d", &choise);

    switch (choise)
    {
    case 1:
        search_by_name(addressBook);
        break;
    case 2:
        search_by_phone(addressBook);
        break;
    case 3:
        search_by_email(addressBook);
        break;
    default:
        printf("Invalid input\n");
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    int choise;
    int index = searchContact(addressBook);
    if (index == -1)
    {
       // printf("Not Found contact.\n");
        return;
    }

    // print promt
    printf("1.Edit Name.\n");
    printf("2.Edit Phone number.\n");
    printf("3.Edit mail.\n");
    printf("4.Edit all.\n");
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
        printf("Invalid input\n");
    }
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
            //printf("\nContact not Found.\n");
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
    for (char i = 0; name[i]; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ' || name[i] >= 'a' && name[i] <= 'z' || name[i] == '.'))
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
        if (email[atPos - 1] == '.')
            return 0;

        if (email[atPos + 1] == '.')
            return 0;

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
    char str[30];
    int count = 0;
    int index = -1;

    // Get the name
    printf("Enter the Search name: ");
    scanf(" %[^\n]", str);

    // Loop from 0 to cc - 1
    for (int i = 0; i < addressBook->contactCount; i++)
    {

        if (strcmp(addressBook->contacts[i].name, str) == 0)
        {

            // print the contact
            printf("\n%d\t%s\t%s\t%s\n", i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            count++;
            index = i;
        }
    }
    // count == > 0 == > return -1;
    if (count == 0)
    {
        printf("\nContacts not found\n");
        return -1;
    }

    // count == > more then 1 == > return search_by_phone(addressBook);
    if (count > 1)
        printf("Same More name. Try to search by phone NO..\n");
        return search_by_phone(addressBook);

    // count == > 1 == > return matching index
    return index;
}

int search_by_phone(AddressBook *addressBook)
{
    char str[11];

    // Get the phone number
    printf("Enter phone number: ");
    scanf("%s", str);

    // Loop from 0 to cc - 1
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, str) == 0)
        {
            // print the contact
            printf("\n%d\t%s\t%s\t%s\n", i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return i;
        }
    }
    return -1;
}

int search_by_email(AddressBook *addressBook)
{
    char str[30];
    printf("Enter Gmail: ");
    scanf(" %[^\n]", str);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, str) == 0)
        {
            printf("\n%d\t%s\t%s\t%s\n", i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return i;
        }
    }
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
            printf("Name  : %s\n", addressBook->contacts[index].name);
            printf("Phone : %s\n", addressBook->contacts[index].phone);
            printf("Email : %s\n", addressBook->contacts[index].email);
            break;
        }
        else
        {
            printf(" Try again.\n");
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
            printf("Name  : %s\n", addressBook->contacts[index].name);
            printf("Phone : %s\n", addressBook->contacts[index].phone);
            printf("Email : %s\n", addressBook->contacts[index].email);
            break;
        }
        else
        {
            printf(" Try again.\n");
        }
    }
}

void Edit_email(AddressBook *addressBook, int index)
{

    while (1)
    {
        printf("contact found.\n");
        char newemail[30];
        printf("Enter new email: ");
        scanf("%s", newemail);

        if (validate_email(newemail, addressBook))
        {
            strcpy(addressBook->contacts[index].email, newemail);
            printf("Name  : %s\n", addressBook->contacts[index].name);
            printf("Phone : %s\n", addressBook->contacts[index].phone);
            printf("Email : %s\n", addressBook->contacts[index].email);

            break;
        }
        else
        {
            printf(" Try again.\n");
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
            printf(" Try again.\n");
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
            printf(" Try again.\n");
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
            printf(" Try again.\n");
        }
    }
    strcpy(addressBook->contacts[index].name, newName);
    strcpy(addressBook->contacts[index].phone, newphone);
    strcpy(addressBook->contacts[index].email, newemail);

    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);
}
