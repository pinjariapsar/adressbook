#ifndef CONTACT_H//ifndef is usedq=to check if the header file is already defined
#define CONTACT_H//here we are defining the header file

#define MAX_CONTACTS 100//here we are defining the maximum number of contacts as 100

typedef struct {// here we are defining the structure of a contact because we are using it in other functions which contain the contact details of a person contains name, phone number and email
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {// here we are defining the structure o f an address book because we are using it in other functions which contains the contact details of a person contains name, phone number and email
    Contact contacts[MAX_CONTACTS];//here we are defining the array of contacts 
    int contactCount;//used to store the number of contacts
} AddressBook;
//below are the function prototypes
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
//hi

#endif
