#include <stdio.h>
#include <string.h>

#define MAX 100

struct contact
{
    char name[50];
    char ph[15];
};

struct contact p[MAX];
int n = 0;

void load();
void save();
void add();
void search();
void update();
void deleteContact();
void sort();
void display();


// LOAD CONTACTS FROM FILE
void load()
{
    FILE *fp;

    fp = fopen("contact.txt", "r");

    if(fp == NULL)
        return;

    n = 0;

    while(n < MAX &&
          fscanf(fp, "\n%49[^|]|%14s",
                 p[n].name, p[n].ph) == 2)
    {
        n++;
    }

    fclose(fp);
}


// SAVE CONTACTS TO FILE
void save()
{
    FILE *fp;
    int i;

    fp = fopen("contact.txt", "w");

    if(fp == NULL)
    {
        printf("Error in opening the file!\n");
        return;
    }

    for(i = 0; i < n; i++)
    {
        fprintf(fp, "%s|%s\n",
                p[i].name, p[i].ph);
    }

    fclose(fp);

    printf("Contacts saved successfully!\n");
}


// ADD CONTACT
void add()
{
    int count, i, j, valid;
    char mobile[100];

    printf("How many contacts do you want to add?\n");
    scanf("%d", &count);

    if(count <= 0)
    {
        printf("Invalid number of contacts!\n");
        return;
    }

    for(i = 0; i < count && n < MAX; i++)
    {
        printf("Enter the name: ");
        scanf(" %49[^\n]", p[n].name);

        do
        {
            valid = 1;

            printf("Enter the mobile number: ");
            scanf(" %99s", mobile);

            if(strlen(mobile) != 10)
                valid = 0;

            for(j = 0; mobile[j] != '\0'; j++)
            {
                if(mobile[j] < '0' || mobile[j] > '9')
                {
                    valid = 0;
                    break;
                }
            }

            if(valid == 0)
            {
                printf("Invalid number! Enter exactly 10 digits.\n");
            }

        } while(valid == 0);

        strcpy(p[n].ph, mobile);

        n++;
    }

    if(i < count)
    {
        printf("Contact storage is full!\n");
    }

    save();
}


// SEARCH CONTACT
void search()
{
    char searchName[50];
    int i, flag = 0;

    printf("Enter the name to search:\n");
    scanf(" %49[^\n]", searchName);

    for(i = 0; i < n; i++)
    {
        if(strcmp(p[i].name, searchName) == 0)
        {
            printf("\nName: %s", p[i].name);
            printf("\nPhone Number: %s\n", p[i].ph);

            flag = 1;
        }
    }

    if(flag == 0)
    {
        printf("Contact not found!\n");
    }
}


// UPDATE CONTACT
void update()
{
    char updateName[50];
    char mobile[100];

    int i, j, flag = 0, valid;

    printf("Enter the name to be updated:\n");
    scanf(" %49[^\n]", updateName);

    for(i = 0; i < n; i++)
    {
        if(strcmp(p[i].name, updateName) == 0)
        {
            printf("Enter new name: ");
            scanf(" %49[^\n]", p[i].name);

            do
            {
                valid = 1;

                printf("Enter new phone number: ");
                scanf(" %99s", mobile);

                if(strlen(mobile) != 10)
                    valid = 0;

                for(j = 0; mobile[j] != '\0'; j++)
                {
                    if(mobile[j] < '0' || mobile[j] > '9')
                    {
                        valid = 0;
                        break;
                    }
                }

                if(valid == 0)
                {
                    printf("Invalid number! Enter exactly 10 digits.\n");
                }

            } while(valid == 0);

            strcpy(p[i].ph, mobile);

            flag = 1;
            break;
        }
    }

    if(flag == 1)
    {
        printf("Contact updated successfully!\n");
        save();
    }
    else
    {
        printf("Contact not found!\n");
    }
}


// DELETE CONTACT
void deleteContact()
{
    char deleteName[50];
    int i, j, flag = 0;

    printf("Enter the name to delete:\n");
    scanf(" %49[^\n]", deleteName);

    for(i = 0; i < n; i++)
    {
        if(strcmp(p[i].name, deleteName) == 0)
        {
            for(j = i; j < n - 1; j++)
            {
                p[j] = p[j + 1];
            }

            n--;
            flag = 1;
            break;
        }
    }

    if(flag == 1)
    {
        save();
        printf("Contact deleted successfully!\n");
    }
    else
    {
        printf("Contact not found!\n");
    }
}


// SORT CONTACTS ALPHABETICALLY
void sort()
{
    int i, j;
    struct contact temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(strcmp(p[i].name, p[j].name) > 0)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    save();

    printf("Contacts sorted successfully!\n");
}


// DISPLAY CONTACTS
void display()
{
    int i;

    if(n == 0)
    {
        printf("No contacts available!\n");
        return;
    }

    printf("\n-------- CONTACT LIST --------\n");

    for(i = 0; i < n; i++)
    {
        printf("\nNAME: %s", p[i].name);
        printf("\nPHONE: %s\n", p[i].ph);
    }
}


// MAIN FUNCTION
int main()
{
    int choice;

    load();

    do
    {
        printf("\n\n====== CONTACT MANAGEMENT SYSTEM ======\n");
        printf("1. Add contacts\n");
        printf("2. Search contacts\n");
        printf("3. Update contacts\n");
        printf("4. Delete contacts\n");
        printf("5. Sort contacts\n");
        printf("6. Display contacts\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                add();
                break;

            case 2:
                search();
                break;

            case 3:
                update();
                break;

            case 4:
                deleteContact();
                break;

            case 5:
                sort();
                break;

            case 6:
                display();
                break;

            case 7:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid input!\n");
        }

    } while(choice != 7);

    return 0;
}
