#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h> // For Windows-specific password masking
#else
#include <termios.h> // For Linux/macOS password masking
#include <unistd.h>
#endif

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
void fix_fgets_input(char *string);
void input_credentials(char *username, char *password);
void mask_password(char *password);

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
        getchar(); // Clear newline from input buffer

        switch (option)
        {
        case 1:
            register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("\nLogin Successful! Welcome, %s!\n", users[user_index].username);
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
        printf("\nMaximum %d users are supported! No more registrations allowed!\n", MAX_USERS);
        return;
    }

    int new_index = user_count;
    printf("\nRegister a new user\n");
    input_credentials(users[new_index].username, users[new_index].password);
    user_count++;
    printf("\nRegistration Successful!\n");
}

int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    input_credentials(username, password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void input_credentials(char *username, char *password)
{
    printf("\nEnter a Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    mask_password(password);
}

void mask_password(char *password)
{
#ifdef _WIN32
    // Windows-specific password masking using conio.h
    char ch;
    int i = 0;
    printf("Enter password (Masking Enabled): ");
    while ((ch = _getch()) != '\r' && ch != EOF) // _getch() captures keypress without showing it
    {
        if (ch == 8) // Backspace
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); // Remove the previous character
            }
        }
        else
        {
            password[i++] = ch;
            printf("*"); // Mask the character
        }
    }
    password[i] = '\0';
    printf("\n");
#else
    // Unix-based (Linux/macOS) password masking using termios.h
    struct termios old_props, new_props;
    tcgetattr(STDIN_FILENO, &old_props);
    new_props = old_props;
    new_props.c_lflag &= ~(ECHO | ICANON); // Disable echoing and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    printf("Enter password (Masking Enabled): ");
    int i = 0;
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (ch == 127) // Handle backspace
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            putchar('*');
        }
    }
    password[i] = '\0'; // Null-terminate the password string

    tcsetattr(STDIN_FILENO, TCSANOW, &old_props); // Restore terminal settings
    printf("\n");
#endif
}

void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n");
    string[index] = '\0';
}
