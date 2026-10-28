#ifndef FILE_H//ifndef is used to check if the header file is already defined
#define FILE_H//here we are defining the header file

#include "contact.h"//include our own header file because we are using it in other functions which contains the contact details of a person contains name, phone number and email and also we are using it in other functions which contains the contact details of a person contains name, phone number and email 
// also the are many like createContact,searchContact,editContact,deleteContact,listContacts,initialize,saveContactsToFile,loadContactsFromFile
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
