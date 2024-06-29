#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "sort.h"
#include <conio.h>

#define MENU_ITEMS 7

void printMenu(int current);
void executeOption(deck** dk, int option);


// Обработка добавления
void handlePushBack(deck** dk) {
    int key;
    char holder;
    char value;
    printf("Enter int key to add: ");
    scanf("%d", &key);

    printf("Enter char value to add: ");
    scanf("%c", &holder);
    scanf("%c", &value);

    data_type var1 = {key, value};
    deck_push_back(*dk, var1);
    printf("Node added successfully.\n");
}

// Обработка удаления
void handlePushFront(deck** dk) {
    int key;
    char holder;
    char value;
    printf("Enter int key to add: ");
    scanf("%d", &key);
    printf("Enter char value to add: ");
    scanf("%c", &holder);
    scanf("%c", &value);

    data_type var1 = {key, value};
    deck_push_front(*dk, var1);
    printf("Node added successfully.\n");
}



int main() {
    deck* dk = malloc(sizeof(deck));
    deck_create(dk);
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
            executeOption(&dk, current + 1);
            if (current == 3) {
                printf("\nPress any key to return to the menu...");
                getch();
            }
        }
    } while (1);
}

// Вывод меню
void printMenu(int current) {
    const char *menu[MENU_ITEMS] = {"Add node to front ",
                                    "Add node to back",
                                    "Sort deck",
                                    "Display deck",
                                    "Delete front",
                                    "Delete back",
                                    "Exit"};

    system("cls");
    printf("Deck Operations Menu:\n");

    for (int i = 0; i < MENU_ITEMS; i++) {
        if (i == current) {
            printf(" -> %s\n", menu[i]);
        } else {
            printf("    %s\n", menu[i]);
        }
    }
}

// Ветвление для исполнения выбранной функции
void executeOption(deck** dk, int option) {

    system("cls");

    switch (option) {
        case 1:
            handlePushFront(dk);
            break;
        case 2:
            handlePushBack(dk);
            break;
        case 3:
            deck* sort_res = quickSort(*dk);

            while ((*dk)->size > 0){
                deck_pop_back(*dk);
            }
            for (size_t i = 0; i < sort_res->size; i++) {
                deck_push_back(*dk, sort_res->data[i]);
            }
            break;
        case 4:
            deck_print(*dk);
            break;
        case 5:
            deck_pop_front(*dk);
            break;
        case 6:
            deck_pop_back(*dk);
            break;
        case 7:
            printf("Exiting program.\n");
            exit(1);
        default:
            printf("Invalid choice, try again.\n");
    }

}

//int main() {
//    data_type var = {1, 'a'};
//    data_type var2 = {2, 'b'};
//    data_type var3 = {3, 'c'};
//    data_type var4 = {4, 'd'};
//    data_type var5 = {5, 'e'};
//
//    deck* dk = (deck*)malloc(sizeof(deck));
//    deck_create(dk);
//
//    deck_push_back(dk, var);
//    deck_push_back(dk, var2);
//    deck_push_front(dk, var3);
//    deck_push_front(dk, var4);
//    deck_push_back(dk, var5);
//
//    deck_print(dk);
//
//    deck* sorted_deck = quickSort(dk);
//
//    deck_print(sorted_deck);
//
//    deck_pop_back(dk);
//    deck_pop_front(dk);
//
//    deck_print(dk);
//
//}
