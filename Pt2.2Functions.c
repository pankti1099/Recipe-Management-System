#include "Pt2.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Function to print all records from the file.
void printAllRecords()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("Error: File not found.\n");
        return;
    }

    char line[256]; // Buffer for reading lines
    int id = 1;     // Recipe ID counter

    printf("All Recipes:\n");
    while (fgets(line, sizeof(line), file))
    {
        // Extracting and printing only the first 25 characters as the recipe name
        char name[26];           // Additional space for the null terminator
        strncpy(name, line, 25); // Copy the first 25 characters
        name[25] = '\0';         // Null-terminate the string

        // Trim the newline character if it's part of the extracted name
        size_t len = strlen(name);
        if (name[len - 1] == '\n')
        {
            name[len - 1] = '\0';
        }

        printf("ID:%d\tName: %s\n", id++, name);
    }

    fclose(file);
}

void searchRecipeByName()
{
    char searchName[25];
    printf("Enter the name of the recipe you want to search for: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("Error: File not found.\n");
        return;
    }

    char fileLine[256]; // Buffer for reading each line from the file
    int found = 0;

    while (fgets(fileLine, sizeof(fileLine), file))
    {
        // Extract and trim the recipe name
        char name[25];
        strncpy(name, fileLine, 24);
        name[24] = '\0';
        // Trim the trailing spaces
        int end = strlen(name) - 1;
        while (end >= 0 && name[end] == ' ')
            name[end--] = '\0';

        if (strcmp(name, searchName) == 0)
        {
            // Now extract and trim ingredients and secret ingredients
            char ingredients[45];
            char secretIngredients[10];

            // Ingredients starts from position 25 and spans 44 characters
            strncpy(ingredients, fileLine + 24, 44);
            ingredients[44] = '\0';
            // Trim trailing spaces
            end = strlen(ingredients) - 1;
            while (end >= 0 && ingredients[end] == ' ')
                ingredients[end--] = '\0';

            // Secret ingredients starts from position 69 and spans 9 characters
            strncpy(secretIngredients, fileLine + 69, 9);
            secretIngredients[9] = '\0';
            // Trim trailing spaces
            end = strlen(secretIngredients) - 1;
            while (end >= 0 && secretIngredients[end] == ' ')
                secretIngredients[end--] = '\0';

            printf("Matched Recipe:\n");
            printf("        Name: %s\n", name);
            printf("        Ingredients: %s\n", ingredients);
            printf("        Secret Ingredients: %s\n", secretIngredients);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Recipe not found.\n");
    }

    fclose(file);
}

void writeRecipeToFile()
{
    Recipe newRecipe = {0};
    char buffer[256]; // Temporary buffer to hold user input

    // Read the recipe name
    printf("Enter recipe name (max 24 characters): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    if (strlen(buffer) > 24)
    {
        printf("Error: Recipe name exceeds the maximum length of 24 characters.\n");
        return;
    }
    strncpy(newRecipe.name, buffer, 24);

    // Read the ingredients
    printf("Enter ingredients (max 44 characters): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    if (strlen(buffer) > 44)
    {
        printf("Error: Ingredients list exceeds the maximum length of 44 characters.\n");
        return;
    }
    strncpy(newRecipe.ingredients, buffer, 44);

    // Read the secret ingredients
    printf("Enter secret ingredients (max 9 characters): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    if (strlen(buffer) > 9)
    {
        printf("Error: Secret ingredients exceed the maximum length of 9 characters.\n");
        return;
    }
    strncpy(newRecipe.secret_ingredients, buffer, 9);

    // Open the file in append mode
    FILE *file = fopen(FILENAME, "a");
    if (!file)
    {
        printf("Error: File could not be opened.\n");
        return;
    }

    // Ensure ingredients start from the 26th position and secret ingredients from the 70th
    fprintf(file, "%-24s %-44s %-9s\n", newRecipe.name, newRecipe.ingredients, newRecipe.secret_ingredients);

    printf("Recipe has been added to the file.\n");

    fclose(file);
}

void searchBySecretIngredient()
{
    char secretIngredient[10];
    printf("Enter the secret ingredient you want to search for (max 9 characters): ");
    fgets(secretIngredient, sizeof(secretIngredient), stdin);
    secretIngredient[strcspn(secretIngredient, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("Error: File not found.\n");
        return;
    }

    char line[256]; // Buffer for reading each line from the file
    int found = 0;
    int matchedCount = 0; // Count of matched recipes
    char outputFilename[20];
    snprintf(outputFilename, sizeof(outputFilename), "%s.txt", secretIngredient); // Create output file name

    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile)
    {
        printf("Error: Cannot create output file.\n");
        fclose(file);
        return;
    }

    // Write the title line with proper spacing
    fprintf(outputFile, "%-24s %-44s %-15s\n", "Name", "Ingredients", "Secret Ingredient");

    while (fgets(line, sizeof(line), file))
    {
        // Extract the ingredients and secret ingredient from the line
        char name[25], ingredients[45], secIngredient[10];
        sscanf(line, "%24[^\t\n] %44[^\t\n] %9[^\t\n]", name, ingredients, secIngredient);

        // Check if the specified secret ingredient is part of the secret ingredient field
        if (strstr(secIngredient, secretIngredient) != NULL)
        {
            // Write the recipe to the new file in the same format as recipes.txt
            fprintf(outputFile, "%-24s %-44s %-15s\n", name, ingredients, secIngredient);
            found = 1;
            matchedCount++;
        }
    }

    if (!found)
    {
        printf("No recipes found with the secret ingredient: %s.\n", secretIngredient);
        // Optionally, remove the created file as it's empty
        remove(outputFilename);
    }
    else
    {
        printf("Recipes with the secret ingredient '%s' have been stored in '%s'.\n", secretIngredient, outputFilename);
        printf("Found %d matched recipes.\n", matchedCount);
    }

    fclose(file);
    fclose(outputFile);
}

void searchByIngredient()
{
    char ingredient[45];
    printf("Enter the ingredient you want to search for (max 44 characters): ");
    fgets(ingredient, sizeof(ingredient), stdin);
    ingredient[strcspn(ingredient, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("Error: File not found.\n");
        return;
    }

    char line[256]; // Buffer for reading each line from the file
    int found = 0;
    int matchedCount = 0; // Count of matched recipes
    char outputFilename[50];
    snprintf(outputFilename, sizeof(outputFilename), "%s.txt", ingredient); // Create output file name

    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile)
    {
        printf("Error: Cannot create output file.\n");
        fclose(file);
        return;
    }

    // Write the title line with proper spacing
    fprintf(outputFile, "%-24s %-44s %-15s\n", "Name", "Ingredients", "Secret Ingredient");

    while (fgets(line, sizeof(line), file))
    {
        // Extract the ingredients and secret ingredient from the line
        char name[25], ingredients[45], secretIngredient[10];
        sscanf(line, "%24[^\t\n] %44[^\t\n] %9[^\t\n]", name, ingredients, secretIngredient);

        // Check if the specified ingredient is part of the ingredients list
        if (strstr(ingredients, ingredient) != NULL)
        {
            // Write the recipe to the new file in the same format as recipes.txt
            fprintf(outputFile, "%-24s %-44s %-15s\n", name, ingredients, secretIngredient);
            found = 1;
            matchedCount++;
        }
    }

    if (!found)
    {
        printf("No recipes found with the ingredient: %s.\n", ingredient);
        // Optionally, remove the created file as it's empty
        remove(outputFilename);
    }
    else
    {
        printf("Recipes with the ingredient '%s' have been stored in '%s'.\n", ingredient, outputFilename);
        printf("Found %d matched recipes.\n", matchedCount);
    }

    fclose(file);
    fclose(outputFile);
}

void storeUserRecipes()
{
    int startIndex, endIndex;
    printf("Enter the start ID of the recipe you want to store in a new file: ");
    scanf("%d", &startIndex);
    printf("Enter the end ID of the recipe you want to store in a new file: ");
    scanf("%d", &endIndex);
    clearInputBuffer(); // Clear the input buffer after reading the indices

    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("Error: File not found.\n");
        return;
    }

    FILE *outputFile = fopen("random.txt", "w");
    if (!outputFile)
    {
        printf("Error: Cannot create output file.\n");
        fclose(file);
        return;
    }

    char line[256];        // Buffer for reading each line from the file
    int lineCount = 0;     // Count of lines processed
    int recipesStored = 0; // Count of recipes stored in the new file

    while (fgets(line, sizeof(line), file))
    {
        lineCount++;
        if (lineCount >= startIndex && lineCount <= endIndex)
        {
            fputs(line, outputFile);
            recipesStored++;
        }
    }

    fclose(file);
    fclose(outputFile);

    if (recipesStored == endIndex - startIndex + 1)
    {
        printf("Recipes with desired range have been stored in the file 'random.txt'.\n");
        printf("Found %d matched records in the file.\n", recipesStored);
    }
    else
    {
        printf("The index is out of range.\n");
    }
}

// Dummy quit function to match the function pointer signature
void quit()
{
    printf("Exiting program.\n");
}