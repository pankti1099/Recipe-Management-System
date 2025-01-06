#include "Pt2.h"



int main()
{
    void (*menuFunctions[])() = {
        printAllRecords,
        searchRecipeByName,
        writeRecipeToFile,
        searchBySecretIngredient,
        searchByIngredient,
        storeUserRecipes,
        quit};
    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1) Print All Records\n");
        printf("2) Search Recipe by Name\n");
        printf("3) Write Recipe to File\n");
        printf("4) Search By Secret Ingredient\n");
        printf("5) Search By Ingredient\n");
        printf("6) Store User Recipes\n");
        printf("7) Quit\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number 1-7.\n");
            clearInputBuffer(); // Clear the input buffer to prevent infinite loop
            continue;
        }
        clearInputBuffer(); // Clear the buffer after a valid choice is entered

        // Adjust choice to match the array index
        choice--;

        // Validate choice range
        if (choice >= 0 && choice < sizeof(menuFunctions) / sizeof(menuFunctions[0]))
        {
            // Call the selected function
            (*menuFunctions[choice])();
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6); // Adjust based on your menu options (quit option index)

    return 0;
}
