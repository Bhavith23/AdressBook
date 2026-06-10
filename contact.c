#include <stdio.h>
#include <string.h>
#include "contact.h"

void createContact(AddressBook *addressBook)
{
    char name[50], phone[15], email[50];
    int valid;

    // ---------------- NAME ----------------
    while (1)
    {
        valid = 1;
        printf("Enter name: ");
        scanf(" %[^\n]", name);
        getchar();

        // ✅ Validate name (only alphabets, space, and '.')
        for (int i = 0; name[i] != '\0'; i++)
        {
            if ((name[i] >= 'A' && name[i] <= 'Z') ||
                (name[i] >= 'a' && name[i] <= 'z') ||
                 name[i] == ' ' || name[i] == '.')
                continue;
            else
            {
                valid = 0; // invalid character found
                break;
            }
        }

        if (valid)
        {
            printf("Name is valid\n");
            break;
        }
        else
        {
            printf("❌ Name is not valid, try again.\n");
        }
    }

    // ---------------- PHONE ----------------
    while (1)
    {
        valid = 1;
        printf("Enter phone number (10 digits): ");
        scanf(" %[^\n]", phone);
        getchar();

        int len = strlen(phone);
        if (len != 10) 
        valid = 0; // must be exactly 10 digits

        // ✅ Ensure all digits
        for (int i = 0; i < len; i++)
        {
            if (!(phone[i] >= '0' && phone[i] <= '9'))
            {
                valid = 0;
                break;
            }
        }

        if (valid)
        {
            printf("Phone is valid\n");
            break;
        }
        else
        {
            printf("❌ Phone is not valid, try again.\n");
        }
    }

    // ---------------- EMAIL ----------------
    while (1) 
    {
        valid = 1;
        printf("Enter new email: ");
        scanf(" %[^\n]", email);
        getchar();
    
        // ✅ Email cannot start with a digit
        if(email[0] >= '0' && email[0] <= '9')
        {
            printf("Invalid input, try again\n");
            continue;
        }

        // ✅ Validate email: allowed [a-z][0-9] @ . and must end with ".com"
        for (int j=0; email[j] != '\0'; j++)
        {
            if ((email[j] >= 'a' && email[j] <= 'z') || 
                (email[j] >= '0' && email[j] <= '9') || 
                email[j] == '@' || email[j] == '.')
            {
                if (email[j] == '@')
                {
                    j++;
                    while (email[j] >= 'a' && email[j] <= 'z')
                    {
                        j++;
                    }
                    // ✅ Must end with ".com"
                    if (email[j] == '.' && email[j+1] == 'c' && email[j+2] == 'o' && email[j+3] == 'm' && email[j+4] == '\0')
                    {
                        break;
                    }
                    else
                    {
                        valid = 0;
                        break;
                    }
                }
                continue;
            }
            else
            {
                valid = 0; // invalid character in email
                break;
            }
        }

        if (valid)
        {
            printf("Email is valid\n");
            break;
        }
        else
        {
            printf("Email is not valid, try again.\n");
        }
    }

    // ✅ Save validated contact
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;

    printf("\nContact created successfully!\n");
}


void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to search.\n");
        return;
    }

    int choice, i, found = 0;
    char searchValue[50];

    while (1)
    {
        // ✅ Search menu
        printf("\nSearch contact by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice! Please try again.\n");
            continue; // re-ask
        }

        printf("Enter value to search: ");
        scanf(" %[^\n]", searchValue);
        getchar();

        // ✅ Extra email validation in search
        if (choice == 3)
        {
            char *atPos = strchr(searchValue, '@');
            if (atPos != NULL && atPos == searchValue)
            {
                printf("❌ Invalid email: must contain at least one character before '@'. Try again.\n");
                continue;
            }
            if (atPos != NULL)
            {
                char *dotPos = strchr(atPos + 1, '.');
                if (dotPos == NULL || dotPos == atPos + 1)
                {
                    printf("❌ Invalid email: must contain at least one character between '@' and domain. Try again.\n");
                    continue;
                }
            }
        }

        // ✅ Find all matching contacts (store indexes)
        int matchedIndexes[MAX_CONTACTS];
        int matchedCount = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((choice == 1 && strcasestr(addressBook->contacts[i].name, searchValue) != NULL) ||
                (choice == 2 && strcasestr(addressBook->contacts[i].phone, searchValue) != NULL) ||
                (choice == 3 && strcasestr(addressBook->contacts[i].email, searchValue) != NULL))
            {
                matchedIndexes[matchedCount++] = i;
                found = 1;
            }
        }

        if (!found)
        {
            printf("❌ No contact found with the given value. Try again.\n");
            continue; // re-search
        }

        // ✅ Show one or multiple matches
        if (matchedCount == 1)
        {
            int idx = matchedIndexes[0];
            printf("\nName : %s\n", addressBook->contacts[idx].name);
            printf("Phone: %s\n", addressBook->contacts[idx].phone);
            printf("Email: %s\n", addressBook->contacts[idx].email);
        }
        else
        {
            // Multiple results → ask user to choose
            printf("\nMultiple contacts found:\n");
            for (int j = 0; j < matchedCount; j++)
            {
                int idx = matchedIndexes[j];
                printf("%d) %s | %s | %s\n", j + 1,
                       addressBook->contacts[idx].name,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            int selection;
            while (1)
            {
                printf("Enter the number of the contact you want to view: ");
                scanf("%d", &selection);
                getchar();

                if (selection >= 1 && selection <= matchedCount)
                {
                    int idx = matchedIndexes[selection - 1];
                    printf("\nName : %s\n", addressBook->contacts[idx].name);
                    printf("Phone: %s\n", addressBook->contacts[idx].phone);
                    printf("Email: %s\n", addressBook->contacts[idx].email);
                    break;
                }
                else
                {
                    printf("Invalid selection. Try again.\n");
                }
            }
        }

        break; // exit after successful search
    }
}
