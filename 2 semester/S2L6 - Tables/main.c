#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key_functions/keys.h"
#include "lab_staff/utils.h"
#include "table_shit/table.h"
// Include the previous implementations for Table, Key, and the related functions

int main() {
    Table* table = create_table();

    random_assignment(table);
    display_table(table);

    int choice;
    while (1) {
        printf("Choose an action:\n");
        printf("1. Sort the table\n");
        printf("2. Search for a key\n");
        printf("3. Display the table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            fflush(stdin);
            continue;
        }

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1:
                linear_selection_sort(table);
                printf("Table sorted successfully.\n\n");
                break;
            case 2: {
                long long key_int;
                char key_char;
                printf("Enter the key to search (integer part followed by character part): ");
                if (scanf("%lld %c", &key_int, &key_char) != 2) {
                    printf("Invalid input. Try again.\n\n");
                    break;
                }
                void* value = binary_search(table, key_int, key_char);
                if (value != NULL) {
                    printf("Value found: %s\n\n", (char*)value);
                } else {
                    printf("Key not found in the table.\n\n");
                }
                break;
            }
            case 3:
                display_table(table);
                break;
            default:
                printf("Invalid choice. Try again.\n\n");
        }
    }

    free_table(table);
    return 0;
}
