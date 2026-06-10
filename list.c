#include <stdio.h>
#include <string.h>
#include "contact.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if (addressBook->contactCount == 0) {
        printf("Address book is empty.\n");
        return;
    }

    // Temporary copy of contacts
    Contact temp[100];  // assuming max contacts = 100
    for (int i = 0; i < addressBook->contactCount; i++) {
        temp[i] = addressBook->contacts[i];
    }

    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = i + 1; j < addressBook->contactCount; j++) {
            int cmp = 0;
            if (sortCriteria == 1)  // sort by name
                cmp = strcasecmp(temp[i].name, temp[j].name);
            else if (sortCriteria == 2)  // sort by phone
                cmp = strcmp(temp[i].phone, temp[j].phone);
            else if (sortCriteria == 3)  // sort by email
                cmp = strcasecmp(temp[i].email, temp[j].email);

            if (cmp > 0) {
                Contact swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }
    // Display after swapping
    printf("\nContact List (Sorted by %s):\n", (sortCriteria == 1 ? "Name" : (sortCriteria == 2 ? "Phone" : "Email")));
    printf("----------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-5d %-25s  %-20s  %-3s\n", i+1, temp[i].name, temp[i].phone, temp[i].email);
    }
    printf("----------------------------------\n");
}