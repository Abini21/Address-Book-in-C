#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 200

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

/* Validation Functions */
int validateName(char name[]);
int validatePhone(AddressBook *addressBook, char phone[]);
int validateEmail(AddressBook *addressBook, char email[]);

#endif
