/*------------------ DOCUMENTATION ------------------

Project Name : Address Book Management System

Description:
This project is used to manage contacts. It allows the user
to create, search, edit, delete, list, save, and load contacts.

Files Used:
1. contact.h - Contains Contact structure and function prototypes.
2. file.h - Contains file handling function prototypes.

Contact Details:
- Name
- Phone Number
- Email Address

Functions:
- createContact()
- searchContact()
- editContact()
- deleteContact()
- listContacts()
- saveContactsToFile()
- loadContactsFromFile()

Working:
1. Contacts are loaded from a file when the program starts.
2. User selects an option from the menu.
3. Contacts can be added, searched, edited, deleted, or listed.
4. Phone numbers and emails are validated before storing.
5. Contacts are saved to a file before exiting.

Search:
Uses strstr() to find contacts using full or partial matches.

Edit/Delete:
Searches contacts, displays matching records, and allows
the user to select a contact using a serial number.

List:
Displays all contacts stored in the address book.

Save/Load:
Used to store contacts permanently in a file and retrieve
them when the program starts.

----------------------------------------------------*/

#include <stdio.h>
#include "contact.h"//include our own header file where we are using it in other functions which contains the contact details of a person contains name, phone number and email

int main() {
    int choice;
    AddressBook addressBook;//here we are defining the structure of an address book AdddressBook is name of structure and addressBook is name of variable
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
