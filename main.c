/*******************************************
* Name        :  Bhavith M Gowda
* Title       :  Address Book
* Date        :  15-08-2025
* Description :  To create, search, delete, edit, list the contact 
                 and save it to the file permanently
*********************************************/

#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;   // Initialize contact count to 0

    loadContactsFromFile(&addressBook);   // Load existing contacts from file at program start
    printf("--------------------------\n");

    do
    {
        // Display menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();   // Clear newline character from buffer
        
        // Perform action based on user choice
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);   // Add a new contact
                break;
            case 2:
                searchContact(&addressBook);   // Search for a contact by name/phone/email
                break;
            case 3:
                editContact(&addressBook);     // Edit existing contact details
                break;
            case 4:
                deleteContact(&addressBook);   // Delete a contact
                break;
            case 5:  
                {
                    int sortCriteria;
                    // Ask sorting preference before listing contacts
                    printf("Sort contacts by: \n");
                    printf("1)Name\n");
                    printf("2)Phone\n");
                    printf("3)Email\n");
                    scanf("%d",&sortCriteria);        
                    listContacts(&addressBook, sortCriteria); // Display contacts in chosen order
                }
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);   // Save all contacts permanently to file
                break;
            default:
                // Ignore invalid input (no message to keep UI clean)
                break;
        }
    } 
    while (choice != 6);   // Repeat menu until user chooses to save and exit
    
    return 0;
}
