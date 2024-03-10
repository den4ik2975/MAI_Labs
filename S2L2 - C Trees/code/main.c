#include "btree.h"
#include <stdio.h>
#include <conio.h>

#define MENU_ITEMS 5

void handleAddNode(Node** root);
void handleDeleteNode(Node** root);
void printMenu(int current);
void executeOption(Node** root, int option);


// Обработка добавления
void handleAddNode(Node** root) {
    float value;
    printf("Enter float value to add: ");
    while(scanf("%f", &value) != 1) {
        printf("Invalid input. Please enter a float value: ");
        while(getchar() != '\n'); // Чистим инпут
    }
    *root = insertNode(*root, value);
    printf("Node added successfully.\n");
}

// Обработка удаления
void handleDeleteNode(Node** root) {
    float value;
    printf("Enter float value to delete: ");
    while(scanf("%f", &value) != 1 || nodeExists(*root, value) != true) {// Здесь же проверка на наличие ноды
        printf("No such node or invalid input. Please enter an existing node value: ");
        while(getchar() != '\n'); // Так же чистим инпут
    }
    *root = deleteNode(*root, value);
    printf("Node deleted successfully.\n");
}


int main() {
    Node* root = NULL;
    int current = 0;
    int input;

    do {
        printMenu(current);

        input = getch();
        if (input == 0 || input == 224) {
            switch (getch()) {
                case 72: // Стрелка вверх
                    current = (current + MENU_ITEMS - 1) % MENU_ITEMS;
                    break;
                case 80: // Стрелка вниз
                    current = (current + 1) % MENU_ITEMS;
                    break;
            }
        } else if (input == 13) { // Энтер
            executeOption(&root, current + 1);
            if (current != 0 && current != 2) {
                printf("\nPress any key to return to the menu...");
                getch();
            }
        }
    } while (1);
}

// Вывод меню
void printMenu(int current) {
    const char *menu[MENU_ITEMS] = {"Add Node",
                                    "Display Tree",
                                    "Delete Node",
                                    "Check if B-Tree",
                                    "Exit"};

    system("cls");
    printf("Binary Tree Operations Menu:\n");

    for (int i = 0; i < MENU_ITEMS; i++) {
        if (i == current) {
            printf(" -> %s\n", menu[i]);
        } else {
            printf("    %s\n", menu[i]);
        }
    }
}

// Ветвление для исполнения выбранной функции
void executeOption(Node** root, int option) {

    system("cls");

    switch (option) {
        case 1:
            handleAddNode(root);
            break;
        case 2:
            printf("Binary Tree:\n");
            displayTree(*root, NULL, 0);
            break;
        case 3:
            handleDeleteNode(root);
            break;
        case 4:
            if (isBTree(*root))
                printf("The tree is a B-tree.\n");
            else
                printf("The tree is not a B-tree.\n");
            break;
        case 5:
            printf("Exiting program.\n");
            exit(1);
        default:
            printf("Invalid choice, try again.\n");
    }

}