#include <stdio.h>
#include "file.h"

// Function to save all contacts from memory to a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
    // Open file in write mode (overwrite existing content)
    FILE *fptr = fopen("contacts.csv", "w");
    if (fptr == NULL) 
    {
        printf("❌ Error: Could not open file for saving.\n");
        return;
    }

    // Write each contact as: name,phone,email
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr); // close file after writing
    printf("✅ %d contacts saved successfully.\n", addressBook->contactCount);
}

// Function to load contacts from CSV file into memory
void loadContactsFromFile(AddressBook *addressBook)
{
    // Open file in read mode
    FILE *fptr = fopen("contacts.csv", "r");
    if (fptr == NULL) 
    {
        // If file doesn’t exist, start with empty address book
        printf("⚠ No contacts found. Starting fresh.\n");
        addressBook->contactCount = 0;
        return;
    }

    int i = 0;
    // Read until EOF or maximum contact limit reached
    while (i < MAX_CONTACTS &&
           fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[i].name,   // read name until ','
                  addressBook->contacts[i].phone,  // read phone until ','
                  addressBook->contacts[i].email)  // read email until '\n'
           == 3) 
    {
        i++;
    }
    addressBook->contactCount = i;

    fclose(fptr); // close file after reading
    printf("\n✅ %d contacts loaded from file.\n", i);
}
