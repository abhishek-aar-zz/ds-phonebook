#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum operations
{
    EXIT,
    ADD_CONTACT,
    DELETE_CONTACT,
    DISPLAY_CONTACT,
    EDIT_CONTACT,
    SEARCH_CONTACT
};
typedef enum operations MENU;

typedef struct contact
{
    int PhoneNO;
    char Name[30];
    char email[30];
    char address[30];
    char MobileNo[20];
} CONTACT;

typedef struct node
{
    struct node *prev;
    CONTACT info;
    struct node *next;
} NODE;

NODE *head = NULL;
NODE *deletehead = NULL;

void FreeList(void);
int CountNodes(NODE *trav);
int CountNodesForFreeList(NODE *trav);
void DeleteContact(void);
void AcceptData(CONTACT *contact);
void DisplayData(CONTACT contact);
NODE *CreateNode(void);
void AddtoContactlist(CONTACT contact);
void DisplayContacts(NODE *trav);
void DeleteContacts(void);
void SortContacts(void);
void SearchContact(void);
void AddContactsToFile(void);
void ReadContactsFromFile(void);

static int counter = 0;

MENU menu_function()
{
    int choice;
    printf(" 1. Add Contacts\n");
    printf(" 2. Delete Contacts\n");
    printf(" 3. Display Contacts\n");
    printf(" 4. Edit Contacts\n");
    printf(" 5. Search Contacts\n");
    printf(" 0. EXIT\n");
    printf(" Enter your choice::");
    scanf("%d", &choice);
    if (choice < 0 || choice > 5)
    {
        printf(" Error: Enter valid choice\n");
    }
    return choice;
}

void FreeList()
{
    while (CountNodesForFreeList(head))
    {
        DeleteContact();
    }
}

int CountNodes(NODE *trav)
{
    int count = 0;
    while (trav != NULL)
    {
        count++;
        trav = trav->next;
    }
    printf("\nTotal No of contacts is : %d \n", count);
    return count;
}

int CountNodesForFreeList(NODE *trav)
{
    int count = 0;
    while (trav != NULL)
    {
        count++;
        trav = trav->next;
    }
    return count;
}

void DeleteContact()
{
    NODE *temp = head;
    head = head->next;
    free(temp);
    temp = NULL;
}

void AcceptData(CONTACT *contact)
{
    counter = CountNodesForFreeList(head);
    contact->PhoneNO = ++counter;
    getchar();
    printf(" Enter Contact name::");
    scanf("%[^\n]s", &contact->Name);
    getchar();
    printf(" Enter MobileNo::");
    scanf("%[^\n]s", &contact->MobileNo);
    getchar();
    printf(" Enter Email::");
    scanf("%[^\n]s", &contact->email);
    getchar();
    printf(" Enter address::");
    scanf("%[^\n]s", &contact->address);
}

void DisplayData(CONTACT contact)
{
    printf(" %d\t\t", contact.PhoneNO);
    printf(" %s\t\t", contact.Name);
    printf(" %s\t\t", contact.email);
    printf(" %s\t\t", contact.address);
    printf(" %s\t\t", contact.MobileNo);
    printf("\n");
}

NODE *CreateNode()
{
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void AddtoContactlist(CONTACT contact)
{
    NODE *new_node;
    new_node = CreateNode();
    new_node->info = contact;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

void DisplayContacts(NODE *trav)
{
    if (trav == NULL)
    {
        printf(" Contact list is empty...\n");
    }
    else
    {
        printf(" Available Contacts\n");
        while (trav != NULL)
        {
            DisplayData(trav->info);
            trav = trav->next;
        }
        printf("\n");
    }
}

void DeleteContacts()
{

    int contact_Sr_No;
    printf(" Enter Contact SR_NO::");
    scanf("%d", &contact_Sr_No);
    if (contact_Sr_No <= CountNodes(head))
    {
        NODE *trav = head, *prevnode = NULL;
        NODE *right;
        while (contact_Sr_No != trav->info.PhoneNO)
        {
            prevnode = trav;
            trav = trav->next;
        }
        if (trav == head)
        {
            if (head->next == NULL)
            {
                NODE *temp = head;
                head = head->next;
                free(temp);
                temp = NULL;
            }
            else
            {
                head = head->next;
                head->prev = NULL;
                trav = NULL;
                free(trav);
                NODE *ptr = head;
                while (ptr != NULL)
                {
                    ptr->info.PhoneNO--;
                    ptr = ptr->next;
                }
                printf(" Contact Deleted successfully...\n");
            }
        }
        else if (trav->next == NULL)
        {
            prevnode->next = NULL;
            trav->prev = NULL;
            trav = NULL;
            free(trav);
            printf(" Contact Deleted successfully...\n");
        }
        else
        {
            right = trav->next;
            NODE *ptr = right;
            while (ptr != NULL)
            {
                ptr->info.PhoneNO--;
                ptr = ptr->next;
            }
            prevnode->next = right;
            right->prev = prevnode;
            trav->next = NULL;
            trav->prev = NULL;
            free(trav);
            printf(" Contact Deleted successfully...\n");
        }
    }

    else
    {
        printf("\n contact SR_NO not found,enter valid SR_NO next time \n\n");
    }
}

void EditContacts()
{

    int contact_Sr_No;
    printf(" Enter Contact SR_NO::");
    scanf("%d", &contact_Sr_No);
    if (contact_Sr_No <= CountNodes(head))
    {
        NODE *trav = head, *prevnode = NULL;
        while (contact_Sr_No != trav->info.PhoneNO)
        {
            prevnode = trav;
            trav = trav->next;
        }
        getchar();
        printf(" Enter Contact name::");
        scanf("%[^\n]s", trav->info.Name);
        getchar();
        printf(" Enter MobileNo::");
        scanf("%[^\n]s", trav->info.MobileNo);
        getchar();
        printf(" Enter Email::");
        scanf("%[^\n]s", trav->info.email);
        getchar();
        printf(" Enter address::");
        scanf("%[^\n]s", trav->info.address);
    }

    else
    {
        printf("\n contact SR_NO not found,enter valid SR_NO next time \n\n");
    }
}

void SortContacts()
{
    if (head == NULL)
    {
    }
    else
    {
        NODE *trav = head, *right = head->next;
        CONTACT temp;
        while (trav->next != NULL)
        {
            right = trav->next;
            while (right != NULL)
            {
                if (trav->info.PhoneNO > right->info.PhoneNO)
                {
                    temp = trav->info;
                    trav->info = right->info;
                    right->info = temp;
                }
                right = right->next;
            }
            trav = trav->next;
        }
    }
}

void SearchContact()
{
    char string[20];
    getchar();
    printf("\nEnter the Mobile_No of Contact to Search :");
    scanf("%s", string);
    NODE *trav = head;
    while ((trav != NULL) && (strcmp(string, trav->info.MobileNo) != 0))
    {
        trav = trav->next;
    }
    if (trav == NULL)
    {
        printf("\nContact Not Found\n\n");
    }
    else
    {
        DisplayData(trav->info);
        printf("\n");
    }
}

void AddContactsToFile()
{
    NODE *trav = head;
    FILE *fp;
    fp = fopen("Contactlist1.txt", "w");
    if (fp == NULL)
    {
        printf(".dat file failed to open....EXIT the program at END to save the deatails to .dat file\n");
    }
    else
    {
        while (trav != NULL)
        {
            fprintf(fp, "%d %s %s %s %s\n", trav->info.PhoneNO, trav->info.Name, trav->info.email, trav->info.address, trav->info.MobileNo);
            trav = trav->next;
        }
    }
    fclose(fp);
}

void ReadContactsFromFile()
{
    CONTACT contact;
    FILE *fp = fopen("Contactlist1.txt", "r");
    if (fp == NULL)
    {
        printf(".dat file failed to open....EXIT the program at END to save the deatails to .dat file\n");
    }
    else
    {
        while ((fscanf(fp, "%d %s %s %s %s", &contact.PhoneNO, &contact.Name, &contact.email, &contact.address, &contact.MobileNo)) != EOF)
        {
            AddtoContactlist(contact);
        }
    }
    fclose(fp);
}

int main()
{
    MENU choice;
    //int data;
    CONTACT contact;
    printf("EXIT the program at END to save the deatails to file\n\n");

    ReadContactsFromFile();

    while ((choice = menu_function()) != EXIT)
    {
        switch (choice)
        {
        case ADD_CONTACT:
            AcceptData(&contact);
            AddtoContactlist(contact);
            SortContacts();
            printf(" Contact added to lib successfully...\n");
            CountNodes(head);
            break;

        case DELETE_CONTACT:
            if (head == NULL)
            {
                printf(" No Contacts are available now...\n");
                break;
            }
            else
            {
                DeleteContacts();
            }
            break;

        case DISPLAY_CONTACT:
            SortContacts();
            DisplayContacts(head);
            printf("\n");
            break;

        case EDIT_CONTACT:
            if (head == NULL)
            {
                printf(" No Contacts are available now to EDIT...\n");
                break;
            }
            else
            {
                EditContacts();
            }
            break;

        case SEARCH_CONTACT:
            if (head == NULL)
            {
                printf(" No Contacts are available now to EDIT...\n");
                break;
            }
            else
            {
                SearchContact();
            }
            SortContacts();
            break;
        }
    }
    AddContactsToFile();
    FreeList();
    return 0;
}
