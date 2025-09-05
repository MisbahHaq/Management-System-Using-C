#include <stdio.h>

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

        scanf("%d", &option); // <-- Missing in your original code

        switch (option)
        {
        case 1:
            printf("\nYou selected Register.\n");
            // Registration logic goes here
            break;
        case 2:
            printf("\nYou selected Login.\n");
            // Login logic goes here
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
