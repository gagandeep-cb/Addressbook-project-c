#include <stdio.h>
#include <unistd.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.csv", "w");

    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(fp, "#%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);

    for (int i = 0; i < 100; i++)
    {
        printf("[Saving.........................%d%%]\r", i);
        usleep(10000);
        fflush(stdout);
    }
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    fscanf(fp, "#%d\n", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, " %[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fp);
}
