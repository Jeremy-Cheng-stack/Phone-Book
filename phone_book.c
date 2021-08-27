#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//To compile -> clang -Wall phone_book.c then ./a.out
//shift+option+f to auto format
//add_person, delete_person, search_for_person, list_all_name(first name+ last name), Quit/delete_all (the functions to write)

#define MAX_STR_LEN 1024

//Storing information of the person
typedef struct Person
{
    char fname[MAX_STR_LEN];
    char lname[MAX_STR_LEN];
    char address[MAX_STR_LEN];
    int num;
} per;

//Storing the linked list of people node
typedef struct list
{
    per person;
    struct list *next;
} people;

people *Add_person(people *head, char *ffname, char *llname, char *aaddress, int nnum)
{
    people *new = head;

    if (new == NULL)
    {
        new = (people *)calloc(1, sizeof(people)); //Allocate memory for people struct
        strcpy(new->person.fname, ffname);         //Copying information in
        strcpy(new->person.lname, llname);
        strcpy(new->person.address, aaddress);
        new->person.num = nnum;
        new->next = NULL;
        return new;
    }

    while (new != NULL)
    {
        if (new->next == NULL)
        {
            people *ne = NULL;
            ne = (people *)calloc(1, sizeof(people));
            new->next = ne;
            strcpy(ne->person.fname, ffname);
            strcpy(ne->person.lname, llname);
            strcpy(ne->person.address, aaddress);
            ne->person.num = nnum;
            ne->next = NULL;
            return head;
        }
        new = new->next;
    }
    return NULL;
}

people *Delete_person(people *head, char *fname, char *lname)
{ // Delete person requires the first and last name of the person
    people *new = head;
    people *back = NULL;

    if (strcmp(new->person.fname, fname) == 0 && strcmp(new->person.lname, lname) == 0)
    { //Check if the person we are deleting is at the head
        back = new->next;
        free(new);
        printf("%s%shas been deleted.\n", fname, lname);
        return back;
    }
    while (new != NULL)
    {
        if (strcmp(new->person.fname, fname) == 0 && strcmp(new->person.lname, lname) == 0)
        {
            back->next = new->next;
            free(new);
            printf("%s%shas been deleted.\n", fname, lname);
            return head;
        }

        back = new;
        new = new->next;
    }
    printf("Person not found.\n"); //Nothing is changed, so return original pointer to head
    return head;
}

void Check_person(people *head, char *fname, char *lname)
{
    people *new = head;

    while (new != NULL)
    {
        if (strcmp(new->person.fname, fname) == 0 && strcmp(new->person.lname, lname) == 0)
        {
            printf("The information of the person you are looking for has been found.\n");
            printf("The person's first name: %s\n", new->person.fname);
            printf("The person's last name: %s\n", new->person.lname);
            printf("The person's address: %s\n", new->person.address);
            printf("The person's phone number: %d\n", new->person.num);
            return;
        }

        new = new->next;
    }
    printf("Person not found.\n"); //Nothing is changed, so return original pointer to head
}

void View_all(people *head)
{
    people *new = head;
    int count = 0;

    while (new != NULL)
    {
        count += 1;
        printf("PERSON %d\n", count);
        printf("%s%s\n", new->person.fname, new->person.lname);

        new = new->next;
    }
}

void Quit(people *head)
{
    people *new = head;
    people *back = NULL;

    while (new != NULL)
    {
        back = new;
        free(new);
        new = back->next;
    }
}

int main()
{
    int cont = 1; // more people is 1 or true and no more is 0 or false
    char input_fname[MAX_STR_LEN];
    char input_lname[MAX_STR_LEN];
    char input_address[MAX_STR_LEN];
    int input_num;
    people *head = NULL;

    printf("Note that this phone book does not handle duplicate first AND last name. This means you can't store Joe Hank twice as an example.\n");
    printf("Type 1 for adding new contact | 2 for deleting a contact | 3 for checking contact information | 4 for viewing all contacts | 5 to QUIT : ");
    scanf("%d", &cont);
    getchar();

    while (cont > 0 && cont < 5)
    {

        if (cont == 1)
        {
            printf("Enter first name: "); //Getting User input
            fgets(input_fname, MAX_STR_LEN, stdin);
            //char *n_pos = strchr(input_fname, '\n');
            //*n_pos = '\0';
            printf("Enter last name: ");
            fgets(input_lname, MAX_STR_LEN, stdin);
            //char *m_pos = strchr(input_lname, '\n');
            //*m_pos = '\0';
            printf("Enter address: ");
            fgets(input_address, MAX_STR_LEN, stdin);
            //char *s_pos = strchr(input_address, '\n');
            //*s_pos = '\0';
            printf("Enter phone number (Only numbers): ");
            scanf("%d", &input_num);
            getchar();
            head = Add_person(head, input_fname, input_lname, input_address, input_num);
        }
        else if (cont == 2)
        {
            printf("Enter first name: "); //Getting User input (need the person's first and last name)
            fgets(input_fname, MAX_STR_LEN, stdin);
            printf("Enter last name: ");
            fgets(input_lname, MAX_STR_LEN, stdin);
            head = Delete_person(head, input_fname, input_lname);
        }
        else if (cont == 3)
        {
            printf("Enter first name: "); //Getting User input (need the person's first and last name)
            fgets(input_fname, MAX_STR_LEN, stdin);
            printf("Enter last name: ");
            fgets(input_lname, MAX_STR_LEN, stdin);
            Check_person(head, input_fname, input_lname);
        }
        else if (cont == 4)
        {
            View_all(head);
        }

        printf("Do you want to continue? Type 1 for adding new contact | 2 for deleting a contact | 3 for checking contact information | 4 for viewing all contacts | 5 to QUIT :");
        scanf("%d", &cont);
        getchar();
    }
    printf("The program will now quit. Goodbye.\n");
    Quit(head);//Function that goes to each allocated memory and free them

    return 0;
}
