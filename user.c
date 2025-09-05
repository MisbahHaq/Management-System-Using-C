#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30
typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user();
int login_user();
void fix_fgets_input(char *);
void input_password(char *);

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

    int new_index = user_count;
    printf("\nRegister a new user\n");
    printf("\nEnter a Username: ");
    fgets(users[new_index].username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(users[new_index].username);
    input_password(users[new_index].password);
    user_count++;
    printf("\nRegistration Successful!\n");
}

int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    printf("\nEnter a Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);
    input_password(password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password))
        {
            return i;
        }
    }
    return -1;
}

void input_password(char *password)
{
    printf("\nEnter password : ");
    fgets(password, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(password);
}
void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n");
    string[index] = '\0';
}