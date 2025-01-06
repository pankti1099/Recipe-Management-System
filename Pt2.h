#ifndef Pt2_H
#define Pt2_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recipe structure declaration
typedef struct
{
    char name[25];
    char ingredients[45];
    char secret_ingredients[10];
} Recipe;

// Macros
#define FILENAME "recipes.txt"

// Function prototypes
void clearInputBuffer();
void printAllRecords();
void searchRecipeByName();
void writeRecipeToFile();
void searchBySecretIngredient();
void searchByIngredient();
void storeUserRecipes();
void quit();

#endif
