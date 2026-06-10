#include <stdio.h>
#include <string.h>
#include "contact.h"

void editContact(AddressBook *addressBook)
{
    // ✅ If no contacts are available, nothing to edit
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to edit.\n");
        return;
    }

    int choice, i, j, found = 0, valid, select, matchCount = 0;
    char searchValue[50], newValue[50];

    while (1)
    {
        // ✅ Ask user how they want to search a contact for editing
        printf("\nEdit contact by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        // Validate menu choice
        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice! Please try again.\n");
            continue;
        }

        // ✅ Get search keyword (name, phone, or email)
        printf("Enter value to search: ");
        scanf(" %[^\n]", searchValue);
        getchar();

        int matches[100];   // store indices of matching contacts
        matchCount = 0;
        found = 0;

        // ✅ Search for matching contacts based on user’s choice
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((choice == 1 && strcasestr(addressBook->contacts[i].name, searchValue) != NULL) ||
                (choice == 2 && strcasestr(addressBook->contacts[i].phone, searchValue) != NULL) ||
                (choice == 3 && strcasestr(addressBook->contacts[i].email, searchValue) != NULL))
            {
                matches[matchCount++] = i; // store match index
                found = 1;
            }
        }

        // ✅ If no match found → try again
        if (!found)
        {
            printf("❌ No contact found with the given value. Try again.\n");
            continue;
        }

        // ✅ If multiple matches found → ask user to choose one
        if (matchCount > 1)
        {
            printf("\nMultiple contacts found:\n");
            for (int k = 0; k < matchCount; k++)
            {
                printf("%d) Name: %s | Phone: %s | Email: %s\n",k + 1,addressBook->contacts[matches[k]].name,addressBook->contacts[matches[k]].phone,addressBook->contacts[matches[k]].email);
            }

            printf("Enter the number of the contact you want to edit: ");
            scanf("%d", &select);
            getchar();

            // Validate selection
            if (select < 1 || select > matchCount)
            {
                printf("Invalid selection.\n");
                return;
            }

            i = matches[select - 1]; // pick selected contact
        }
        else
        {
            i = matches[0]; // only one contact found
        }

        // ---------------- EDIT NAME ----------------
        if (choice == 1)
        {
            while (1)
            {
                valid = 1;
                printf("Enter new name: ");
                scanf(" %[^\n]", newValue);
                getchar();

                // ✅ Check that name contains only letters, spaces, and dots
                for (j = 0; newValue[j] != '\0'; j++)
                {
                    if ((newValue[j] >= 'A' && newValue[j] <= 'Z') ||
                        (newValue[j] >= 'a' && newValue[j] <= 'z') ||
                        newValue[j] == ' ' || newValue[j] == '.')
                    {
                        continue;
                    }
                    else
                    {
                        valid = 0;
                        break;
                    }
                }

                if (valid)
                {
                    strcpy(addressBook->contacts[i].name, newValue);
                    break;
                }
                else
                {
                    printf("Name is not valid, try again.\n");
                }
            }
        }
        // ---------------- EDIT PHONE ----------------
        else if (choice == 2)
        {
            while (1)
            {
                valid = 1;
                printf("Enter new phone (10 digits): ");
                scanf(" %[^\n]", newValue);
                getchar();

                // ✅ Validate phone → only digits, must be exactly 10
                for (j = 0; newValue[j] != '\0'; j++)
                {
                    if (newValue[j] < '0' || newValue[j] > '9')
                    {
                        valid = 0;
                        break;
                    }
                }

                if (j != 10) // must be exactly 10 digits
                {
                    valid = 0;
                }

                if (valid)
                {
                    strcpy(addressBook->contacts[i].phone, newValue);
                    break;
                }
                else
                {
                    printf("Phone number is not valid, try again.\n");
                }
            }
        }
        // ---------------- EDIT EMAIL ----------------
        else if (choice == 3)
        {
            while (1)
            {
                valid = 1;
                printf("Enter new email: ");
                scanf(" %[^\n]", newValue);
                getchar();

                // ✅ Email validation
                char *atPos = strchr(newValue, '@');
                if (atPos == NULL || atPos == newValue) // must contain at least 1 char before '@'
                {
                    valid = 0;
                }
                else
                {
                    char *dotPos = strstr(atPos, ".com");
                    if (dotPos == NULL || dotPos == atPos + 1) // must have at least 1 char between '@' and '.'
                    {
                        valid = 0;
                    }
                    else if (*(dotPos + 4) != '\0') // must end with ".com"
                    {
                        valid = 0;
                    }
                }

                if (valid)
                {
                    strcpy(addressBook->contacts[i].email, newValue);
                    break;
                }
                else
                {
                    printf("Email is not valid, try again.\n");
                }
            }
        }

        // ✅ Show updated contact details
        printf("\nContact updated successfully!\n");
        printf("Name : %s\n", addressBook->contacts[i].name);
        printf("Phone: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
        return; // Exit after successful update
    }
}
