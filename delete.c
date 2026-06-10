#include <stdio.h>
#include <string.h>
#include "contact.h"

void deleteContact(AddressBook *addressBook)
{
    // ✅ Check if address book is empty
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete.\n");
        return;
    }

    int choice, i, j, found = 0, select, matchCount = 0;
    char searchValue[50], confirm;

    // ✅ Ask user how they want to search for contact
    printf("\nDelete Contact by:\n");
    printf("1) Name\n");
    printf("2) Phone Number\n");
    printf("3) Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline

    // ✅ Take search input
    printf("Enter value to search: ");
    scanf(" %[^\n]", searchValue);

    // ✅ Array to store all matching contacts' indices
    int matches[100];

    // ✅ Search for matching contacts
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strcasestr(addressBook->contacts[i].name, searchValue) != NULL) ||
            (choice == 2 && strcasestr(addressBook->contacts[i].phone, searchValue) != NULL) ||
            (choice == 3 && strcasestr(addressBook->contacts[i].email, searchValue) != NULL))
        {
            matches[matchCount++] = i; // store matching index
            found = 1;
        }
    }

    // ❌ If no match is found
    if (!found)
    {
        printf("\n❌ No contact found with the given value.\n");
        return;
    }

    // ✅ If multiple matches are found, let user select one
    if (matchCount > 1)
    {
        printf("\nMultiple contacts found:\n");
        for (i = 0; i < matchCount; i++)
        {
            printf("%d) Name : %s\n", i + 1, addressBook->contacts[matches[i]].name);
            printf("   Phone: %s\n", addressBook->contacts[matches[i]].phone);
            printf("   Email: %s\n\n", addressBook->contacts[matches[i]].email);
        }

        // ✅ Ask user to pick which contact to delete
        printf("Enter the number of the contact you want to delete: ");
        scanf("%d", &select);

        if (select < 1 || select > matchCount)
        {
            printf("Invalid selection.\n");
            return;
        }

        i = matches[select - 1]; // chosen index
    }
    else
    {
        i = matches[0]; // ✅ If only one match, pick it directly
    }

    // ✅ Show chosen contact before deletion
    printf("\nContact Found:\n");
    printf("Name : %s\n", addressBook->contacts[i].name);
    printf("Phone: %s\n", addressBook->contacts[i].phone);
    printf("Email: %s\n", addressBook->contacts[i].email);

    // ✅ Ask confirmation before deleting
    printf("\nAre you sure you want to delete this contact? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y')
    {
        // ✅ Shift contacts left to overwrite deleted contact
        for (j = i; j < addressBook->contactCount - 1; j++)
        {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }
        addressBook->contactCount--; // reduce count
        printf("\n✅ Contact deleted successfully!\n");
    }
    else
    {
        printf("\n❌ Deletion cancelled.\n");
    }
}
