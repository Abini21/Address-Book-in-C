#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"


void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("1. sort by name\n2. sort by phone\n3. sort by email\n");
    int sortchoice;
    printf("Enter your choice for sorting: ");
    scanf("%d", &sortchoice);
    switch(sortchoice)
{
    case 1:
    {
        for (int i = 0; i < addressBook->contactCount - 1; i++)
        {
            for (int j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if (strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
        break;
    }
    default:
        printf("Invalid choice!\n");
        return;
}
for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Contact %d: Name: %s, Phone: %s, Email: %s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 10;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validateName(char name[])
{
    int i = 0;

    while(name[i] != '\0')
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' '))
        {
            return 0;
        }

        i++;
    }

    return 1;
}

int validatePhone(AddressBook *addressBook, char phone[])
{
    int i;

    // Check length
    if(strlen(phone) != 10)
    {
        return 0;
    }

    // Check every character is a digit
    for(i = 0; phone[i] != '\0'; i++)
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            return 0;
        }
    }

    // Check for duplicate phone number
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 0;
        }
    }

    return 1;
}

int validateEmail(AddressBook *addressBook, char email[])
{
    int i;
    int atCount = 0;

    for(i = 0; email[i] != '\0'; i++)
    {
        // No spaces
        if(email[i] == ' ')
        {
            return 0;
        }

        // No uppercase letters
        if(email[i] >= 'A' && email[i] <= 'Z')
        {
            return 0;
        }

        // Count '@'
        if(email[i] == '@')
        {
            atCount++;
        }
    }

    // Exactly one '@'
    if(atCount != 1)
    {
        return 0;
    }

    // Check domain
    if(strstr(email, ".com") == NULL &&
       strstr(email, ".net") == NULL &&
       strstr(email, ".org") == NULL &&
       strstr(email, ".in") == NULL)
    {
        return 0;
    }

    // Check duplicate email
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            return 0;
        }
    }

    return 1;
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("Enter the name : ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);

    if(validateName(addressBook->contacts[addressBook->contactCount].name))
    {
        printf("Valid Name\n");
    }
    else
    {
        printf("Invalid Name\n");
    }

    printf("Enter the phone no : ");
    scanf(" %s", addressBook->contacts[addressBook->contactCount].phone);

    if(validatePhone(addressBook,addressBook->contacts[addressBook->contactCount].phone))
    {
        printf("Valid phone\n");
    }
    else
    {
        printf("Invalid phone\n");
    }

    printf("Enter the email id : ");
    scanf(" %s", addressBook->contacts[addressBook->contactCount].email);

    if(validateEmail(addressBook,addressBook->contacts[addressBook->contactCount].email))
    {
        printf("Valid email\n");
    }
    else
    {
        printf("Invalid email\n");
    }

    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice = 0;
    printf("1.Search by name. \n2. Search by phone no. \n3. Search by email. \nEnter the choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            char name[50];
            printf("Enter the name : ");
            getchar();
            scanf("%[^\n]", name);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(name, addressBook->contacts[i].name) == 0)
                {
                    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    return i;
                }
            }
            break;
            
        case 2:
            char phone[20];
            printf("Enter the phone no : ");
            scanf("%s", phone);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(phone, addressBook->contacts[i].phone) == 0)
                {
                    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    return i;
                }
            }
            break;

        case 3:
            char email[50];
            printf("Enter the phone no : "); // Note: The image shows this label for email search as well
            scanf("%[^\n]", email);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(email, addressBook->contacts[i].email) == 0)
                {
                    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    return i;
                }
            }
            break;
    }
    printf("Contact not found!\n");
    return -1;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int ret = searchContact(addressBook);
    if(ret == -1)
    {
        return;
    }
    printf("1. Edit name\n2. Edit phone.\n3. Edit mail id.\nEnter the choice : ");
    int choice = 0;
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
        {
            char name[50];
            printf("Enter the name : ");
            scanf(" %[^\n]", name);
            
            //validate the name -> 1 -> valid name
            //                  -> 0 -> not a valid name
            if(validateName(name))
            {
                strcpy(addressBook->contacts[ret].name, name);
                break;
            }
            else
            {
                printf("Invalid Name!\n");
            }
            break;
        }
        case 2:
        {
            char phone[20];

            printf("Enter new phone : ");
            scanf("%s", phone);

            if(validatePhone(addressBook, phone))
            {
                strcpy(addressBook->contacts[ret].phone, phone);
                printf("Phone updated successfully.\n");
            }
            else
            {
                printf("Invalid or Duplicate Phone Number!\n");
            }
            break;
        }

        case 3:
        {
            char email[50];

            printf("Enter new email : ");
            scanf("%s", email);

            if(validateEmail(addressBook, email))
            {
                strcpy(addressBook->contacts[ret].email, email);
                printf("Email updated successfully.\n");
            }
            else
            {
                printf("Invalid or Duplicate Email!\n");
            }
            break;
        }
    }
    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[ret].name, addressBook->contacts[ret].phone, addressBook->contacts[ret].email);
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int ret = searchContact(addressBook);
    if(ret == -1)
    {
        return;
    }
    for(int i = ret; i < addressBook->contactCount; i++)
    {
      
        addressBook->contacts[i] = addressBook -> contacts[i + 1];

    }
    addressBook->contactCount--;
}
