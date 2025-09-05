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
    int user_index;
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
            register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("Login Successfull!, Welcome, %s!", users[user_index].username);
            }
            else
            {
                printf("\nLogin Failed! Incorrect Username or Password.\n");
            }
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

void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\nMaximum %d users are supported! No more registrations Allowed!!!\n", MAX_USERS);
        return;
    }
    printf("\nRegister a new user\n");
    printf("\nEnter a username: ");
}

int login_user()
{
    return -1;
}