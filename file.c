#include <stdio.h> 
#include "file.h"//include our own header file called file.h which contains the function prototypes
void saveContactsToFile(AddressBook *addressBook) {//here we are saving the contacts to file 
    FILE *file = fopen("contacts.csv", "w");//opening the file in write mode which is called contacts.csv where csv stands for comma separated values

    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "Total contacts: #%d\n", addressBook->contactCount);//we are writing the contact count to the file like Total contacts: #3

    for (int i = 0; i < addressBook->contactCount; i++) {
        // fprintf(file,%s addressBook->contacts[i].name);
        fprintf(file,"%s,%s,%s,\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);//here we are writing the contacts to the file int the format name,phone number,email because we are using comma separated values
    }
    
    fclose(file);
  
}
// as the saveContactsToFile function is called in the saveAndExit function to reflect the changes in the file we are calling it in the saveAndExit function  by using loadContactsFromFile

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "r");//opening the file in read mode

    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    fscanf(file, "Total contacts: #%d\n", &addressBook->contactCount);//here we are reading the contact count from the file ex: Total contacts: #3
    
    for (int i = 0; i < addressBook->contactCount; i++) {
        fscanf(file, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);//here we are reading the contacts from the file int the format name,phone number,email because we are using comma separated values
    }
    fclose(file);
    
}
