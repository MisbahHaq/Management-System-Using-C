#include <stdio.h>

#define MAX_USERS 10
typedef struct
{
    char username[30];
    char password[30];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user();
int login_user();

int main()
{
    int option;
    while (1)
    {
        printf("\nWelcome to User Management");
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nSelect an option: ");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("\nYou selected Register.\n");
            break;
        case 2:
            printf("\nYou selected Login.\n");
            break;
        case 3:
            printf("\nExiting Program\n");
            return 0;
        default:
            printf("\nInvalid option. Please try again.\n");
            break;
        }
    }
}
