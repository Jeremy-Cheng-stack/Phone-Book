#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//To compile -> clang phone_book.c then ./a.out
//shift+option+f to auto format
//add_person, delete_person, search_for_person, list_all_name(first name+ last name), Quit/delete_all

#define MAX_STR_LEN 1024

//Storing information of the person here
typedef struct Person
{
    char fname[MAX_STR_LEN];
    char lname[MAX_STR_LEN];
    char address[MAX_STR_LEN];
    int num;
} per;

//Storing the linked list of people node here
typedef struct list
{
    per *person;
    struct list *next;
} people;

people *Add_person(people *head, char *ffname, char *llname, char *aaddress, int nnum)
{
    people *new = head;

    if (new == NULL)
    {
        new = (people *)calloc(1, sizeof(people));   //Allocate memory for people struct
        new->person = (per *)calloc(1, sizeof(per)); //Must then also alocate memory for per struct since it doesn't auto do it above
        strcpy(new->person->fname, ffname);          //Copying information in
        strcpy(new->person->lname, llname);
        strcpy(new->person->address, aaddress);
        new->person->num = nnum;
        new->next = NULL;
        return new;
    }

    while (new != NULL)
    {
        if (new->next == NULL)
        {
            people *ne = NULL;
            ne = (people *)calloc(1, sizeof(people));
            ne->person = (per *)calloc(1, sizeof(per));
            new->next = ne;
            strcpy(ne->person->fname, ffname);
            strcpy(ne->person->lname, llname);
            strcpy(ne->person->address, aaddress);
            ne->person->num = nnum;
            ne->next = NULL;
            return head;
        }
        new = new->next;
    }
    return NULL;
}

//people *delete_person(people *head, char fname, char last name){// Delete person requires the first and last name of the person

//}

int main()
{
    int more_people = 1; // more people is 1 or true and no more is 0 or false
    char input_fname[MAX_STR_LEN];
    char input_lname[MAX_STR_LEN];
    char input_address[MAX_STR_LEN];
    int input_num;
    people *head = NULL;

    while (more_people == 1)
    {
        printf("Enter first name:"); //Getting User input
        fgets(input_fname, MAX_STR_LEN, stdin);
        printf("Enter last name:");
        fgets(input_lname, MAX_STR_LEN, stdin);
        printf("Enter address:");
        fgets(input_address, MAX_STR_LEN, stdin);
        printf("Enter phone number:");
        scanf("%d", &input_num);
        getchar();
        head = Add_person(head, input_fname, input_lname, input_address, input_num);
        //printf("Do you want to continue? Type 1 for adding new contact | 2 for deleting a contact | 3 for checking contact | 4 for viewing all contacts | 5 to QUIT :");
        //scanf("%d", &more_people);
        //getchar();
    }

    printf("The first name of the person you entered is: %s\n", head->person->fname);
    printf("The last name of the person you entered is: %s\n", head->person->lname);
    printf("The address of the person you entered is: %s\n", head->person->address);
    printf("The phone number of the person you entered is: %d\n", head->person->num);
    free(head);

    return 0;
}
