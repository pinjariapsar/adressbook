#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
int matchedIndex[MAX_CONTACTS];
int matchCount = 0;

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    switch(sortCriteria) {
        case 1: printf("sorting by name\n");
        for(int i = 0; i < addressBook->contactCount-1; i++) {
            for(int j = 0; j < addressBook->contactCount-i-1; j++) {
                if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) >0) {// here we are comparing names
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }   
        }
        printf("Index no \tName\t\tPhone\t\tEmail\n");
        for(int i = 0; i < addressBook->contactCount; i++) {
            printf("%d\t\t%s\t\t%s\t\t%s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
       
        break;
        case 2: printf("sorting by phone\n");
         for(int i = 0; i < addressBook->contactCount-1; i++) {
            for(int j = 0; j < addressBook->contactCount-i-1; j++) {
                if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) >0) {//here we are comparing phone numbers
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                 
                }
            }
            
        }
        printf("Index no \tName\t\tPhone\t\tEmail\n");
        for(int i = 0; i < addressBook->contactCount; i++) {
            printf("%d\t\t%s\t\t%s\t\t%s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
         }
       
        break;
        case 3: printf("sorting by email\n");
         for(int i = 0; i < addressBook->contactCount-1; i++) {
            for(int j = 0; j < addressBook->contactCount-i-1; j++) {
                if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) >0) {//here we are comparing emails
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                 
                }
            }
            
        }
        printf("Index no \tName\t\tPhone\t\tEmail\n");
        for(int i = 0; i < addressBook->contactCount; i++) {
            printf("%d\t\t%s\t\t%s\t\t%s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
       
        break;
        default: printf("Invalid sorting criteria\n");
        
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;//here we are initializing contact count
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)

    loadContactsFromFile(addressBook);//calling function of file.h 
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file

    
    exit(EXIT_SUCCESS); // Exit the program

}
#include <ctype.h>

int validatename(char name[])
//in this we are validating name by checking whether it contains only alphabets and spaces
{
    int i = 0;

    if(name[0] == '\0')
        return 0;
    if(strlen(name)<=4){
        printf("Name should be more than 4 characters\n");
        return 0;

    }

    while(name[i] != '\0')
    {
        if(isalpha(name[i]) || name[i] == ' ')//checking whether it contains only alphabets and spaces
            i++;
        else
            return 0;
    }

    return 1;
}int validatephone(char phone[], AddressBook *addressBook)
//in this we are validating phone number by checking whether it contains 10 digits and is a valid phone number and no two phone numbers should be same
{
    // Check length
    if(strlen(phone) != 10)
        return 0;

    // First digit should be 6-9
    if(phone[0] < '6' || phone[0] > '9')
        return 0;

    // Check all are digits
    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
            return 0;
    }

    // Check duplicate phone numbers
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
            return 0;
    }
    return 1;
}
int validateemail(char email[])
{
    int i = 0, at = -1, dot = -1;//-1 bcz we are using it as a flag if we use 0 it will give error
    int len = strlen(email);

    // First character should be a lowercase letter

    // Find @ and .
    for(i = 0; i < len; i++)
    {
        if(email[i] == '@')
            at = i;

        if(email[i] == '.')
            dot = i;
    }

    
    // @ and . must exist
    if(at == -1 || dot == -1)
        return 0;

    // . must come after @
    if(dot < at)
        return 0;

    // Must end with ".com"
    if(strcmp(&email[dot], ".com") != 0)
        return 0;
    // Before @ : only lowercase letters
    for(i = 0; i < at; i++)
    {
        if(!islower(email[i]))
            return 0;
    }
    // Between @ and . : only lowercase letters
    for(i = at + 1; i < dot; i++)
    {
        if(!islower(email[i]))
            return 0;
    }

    return 1;
}

void createContact(AddressBook *addressBook)
{
    // Create a new contact and add it to the address book
   char name[50];
    char phone[20];
    char email[50];
    int attempts=3;
         while(attempts>0){
            printf("Enter the name:");;
            scanf(" %[^\n]", name);
            if(validatename(name)){
                break;
            }
            printf("Invalid name\n");
            attempts--;


         }
         if(attempts==0){
            printf("Contact creation failed\n");
            return;
         }
         attempts=3;
         while(attempts>0){
            printf("Enter the phone number: ");
            scanf("%s", phone);
            if(validatephone(phone, addressBook)){
                break;
            }
            printf("Invalid phone number\n");
            attempts--;
         }
         if(attempts==0){
            printf("Contact creation failed\n");
            return;
         }
         attempts=3;

         while(attempts>0){
            printf("Enter the email: ");
            scanf("%s", email);
            if(validateemail(email)){
                break;
            }
            printf("Invalid email\n");
            attempts--;
         }
         

        strcpy(addressBook->contacts[addressBook->contactCount].name, name);//here we are copying name phone and email into address book 
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);//here we are copying name phone and email into address book
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);//here we are copying name phone and email into address book
        addressBook->contactCount++;//here we are incrementing contact count becuase we have created a new contact
        // attempts--;
        printf("Contact created successfully\n");

	/* Define the logic to create a Contacts */
    
}


void searchContact(AddressBook *addressBook)
{
    int choice;
    printf("1.Search by name\n");
    printf("2.Search by phone\n");
    printf("3.Search by email\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    printf("Choice = %d\n", choice); 
    int found=0;
    matchCount=0;//calling global variable beacause we are using it in other functions
    switch(choice)
    {
        case 1:
            char name[50];
            printf("Enter the name: ");
            scanf(" %[^\n]", name);
            found=0;//calling global variable beacause we are using it in other functions using as a flag
            for(int i=0;i<addressBook->contactCount;i++){
                if(strstr(addressBook->contacts[i].name, name) != NULL)//here we are comparing names even if it is not case sensitive and also search for substring
                {
                    matchedIndex[matchCount]=i;//here  we are storing the index of matched contact becuase we are using it in other functions called by deleteContact
                    printf("Index: %d\n",matchCount+1);
                    printf("Name: %s\n",addressBook->contacts[i].name);
                    printf("Phone: %s\n",addressBook->contacts[i].phone);
                    printf("Email: %s\n",addressBook->contacts[i].email);
                    found=1;
                    matchCount++; //calling global variable beacause we are using it in other functions
                    // break;
                    // return i;
                }
            }
            if(found==0){
                printf("Contact not found\n");
            }
            break;

        case 2:
            char phone[20];
            printf("Enter the phone number: ");
            scanf("%s", phone);
            found=0;
            for(int i=0;i<addressBook->contactCount;i++){
                if(strstr(addressBook->contacts[i].phone, phone) != NULL){
                    printf("Name: %s\n",addressBook->contacts[i].name);
                    printf("Phone: %s\n",addressBook->contacts[i].phone);
                    printf("Email: %s\n",addressBook->contacts[i].email);
                    found=1;
                    // return i;
                }
            }
            if(found==0){
                printf("Contact not found\n");
            }

            
            break;

        case 3:
            char email[50];
            printf("Enter the email: ");
            scanf("%s", email);
            found=0;
            for(int i=0;i<addressBook->contactCount;i++){
                if(strstr(addressBook->contacts[i].email, email) != NULL){
                    printf("Name: %s\n",addressBook->contacts[i].name);
                    printf("Phone: %s\n",addressBook->contacts[i].phone);
                    printf("Email: %s\n",addressBook->contacts[i].email);
                    found=1;
                    // return i;
                }
            }
            if(found==0){
                printf("Contact not found\n");
            }
            break;

        default:
            printf("Invalid Choice\n");
    }
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int attempts=3;
    searchContact(addressBook);// we should call searchContact function before editContact because we are using matchCount and matchedIndex in editContact as well we should search first
    if(matchCount==0){
        printf("Contact not found\n");
        return;
    }
    int serial;//serail is used to choose which contact we want to edit
    printf("Choose what you want to edit\n");
    scanf("%d", &serial);

    int index=matchedIndex[serial-1];//here we are storing the index of matched contact becuase we are using it in other functions called by editContact 
    int choice;

    printf("1.Edit name\n");
    printf("2.Edit phone\n");
    printf("3.Edit email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
       switch(choice)
{
    case 1:
    {
        char name[50];
        attempts = 3;

        while(attempts > 0)
        {
            printf("Enter the name: ");
            scanf(" %[^\n]", name);

            if(validatename(name))
            {
                strcpy(addressBook->contacts[index].name, name);//here we are updating the name in the contact by using index which we got from searchContact by using matchedIndex
                printf("Name updated successfully.\n");
                break;
            }

            printf("Invalid name\n");
            attempts--;
        }

        if(attempts == 0)
        {
            printf("Contact updation failed\n");
            return;
        }

        break;
    }

    case 2:
    {
        char phone[20];
        attempts = 3;

        while(attempts > 0)
        {
            printf("Enter the phone number: ");
            scanf("%s", phone);

            if(validatephone(phone, addressBook))
            {
                strcpy(addressBook->contacts[index].phone, phone);//here we are updating the phone in the contact by using index which we got from searchContact by using matchedIndex
                printf("Phone updated successfully.\n");
                break;
            }

            printf("Invalid phone number\n");
            attempts--;
        }

        if(attempts == 0)
        {
            printf("Contact updation failed\n");
            return;
        }

        break;
    }

    case 3:
    {
        char email[50];
        attempts = 3;

        while(attempts > 0)
        {
            printf("Enter the email: ");
            scanf("%s", email);

            if(validateemail(email))
            {
                strcpy(addressBook->contacts[index].email, email);//here we are updating the email in the contact by using index which we got from searchContact by using matchedIndex
                printf("Email updated successfully.\n");
                break;
            }

            printf("Invalid email\n");
            attempts--;
        }

        if(attempts == 0)
        {
            printf("Contact updation failed\n");
            return;
        }

        break;
    }

    default:
        printf("Invalid Choice\n");
}
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    searchContact(addressBook);// we should call searchContact function before deleteContact because we are using matchCount and matchedIndex in deleteContact as well we should search first
    if(matchCount==0){
        printf("Contact not found\n");
        return;
    }
    int serial;//serail is used to choose which contact we want to delete
    printf("Choose what you want to delete\n");
    scanf("%d", &serial);

    int index=matchedIndex[serial-1];//-1 is used because we are using 1 based indexing
    for(int i=index;i<addressBook->contactCount-1;i++){
        addressBook->contacts[i]=addressBook->contacts[i+1];//here we are deleting the contact by using index which we got from searchContact by using matchedIndex
    }
    addressBook->contactCount--;//here we are decrementing the contact count because we are deleting the contact
    printf("Contact deleted successfully.\n");

   
}