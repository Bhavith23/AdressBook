#ifndef FILE_H
#define FILE_H

#include "contact.h"

// Save all contacts from memory (addressBook) to a file permanently
void saveContactsToFile(AddressBook *addressBook);

// Load all contacts from file into memory (addressBook) at program startup
void loadContactsFromFile(AddressBook *addressBook);

#endif
