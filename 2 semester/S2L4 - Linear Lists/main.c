#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MENU_ITEMS 6

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
void printList(Node* head);
void insertNode(Node** head, int data, int index);
void deleteNode(Node** head, int index);
int countNodes(Node* head);
void clearListWithValue(Node** head, int value);
void appendNode(Node** head, int data);
void printMenu(int current);
void executeOption(Node** lst, int option);

void handleInsert(Node** lst) {
    int index;
    char holder;
    int value;
    printf("Enter int index: ");
    if (scanf("%d", &index) != 1) {
        return;
    }

    printf("Enter int value to add: ");
    scanf("%c", &holder);
    if (scanf("%d", &value) != 1) {
        return;
    }

    insertNode(lst, value, index);
    printf("Node added successfully.\n");
}

void handleAppend(Node** lst) {
    char holder;
    int value;

    printf("Enter int value to add: ");
    scanf("%c", &holder);
    if (scanf("%d", &value) != 1) {
        return;
    }

    appendNode(lst, value);
    printf("Node added successfully.\n");
}

void handleShit(Node** lst) {
    char holder;
    int value;

    printf("Enter int value to check: ");
    scanf("%c", &holder);
    if (scanf("%d", &value) != 1) {
        return;
    }

    clearListWithValue(lst, value);
}


int main() {
    Node* head = NULL;
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
            executeOption(&head, current + 1);
            if (current == 2 || current == 3) {
                printf("\nPress any key to return to the menu...");
                getch();
            }
        }
    } while (1);
}

// Вывод меню
void printMenu(int current) {
    const char *menu[MENU_ITEMS] = {"Insert node ",
                                    "Append node",
                                    "Print list",
                                    "Print length",
                                    "Execute the function",
                                    "Exit"};

    system("cls");
    printf("Node Operations Menu:\n");

    for (int i = 0; i < MENU_ITEMS; i++) {
        if (i == current) {
            printf(" -> %s\n", menu[i]);
        } else {
            printf("    %s\n", menu[i]);
        }
    }
}

// Ветвление для исполнения выбранной функции
void executeOption(Node** lst, int option) {

    system("cls");

    switch (option) {
        case 1:
            handleInsert(lst);
            break;
        case 2:
            handleAppend(lst);
            break;
        case 3:
            printList(*lst);
            break;
        case 4:
            int ln = countNodes(*lst);
            printf("List length: %d", ln);
            break;
        case 5:
            handleShit(lst);
            break;
        case 6:
            printf("Exiting program.\n");
            exit(1);
        default:
            printf("Invalid choice, try again.\n");
    }

}

//int main() {
//    Node* head = NULL;
//
//    // Insert some nodes
//    appendNode(&head, 10);
//    printf("Printing the list:\n");
//    printList(head);
//    appendNode(&head, 20);
//    printf("Printing the list:\n");
//    printList(head);
//    appendNode(&head, 30);
//    printf("Printing the list:\n");
//    printList(head);
//    insertNode(&head, 40, 0);
//    printf("Printing the list:\n");
//    printList(head);
//
//    printf("\nInserting 50 at index 2:\n");
//    insertNode(&head, 50, 2);
//    printList(head);
//
//    printf("\nDeleting node at index 0:\n");
//    deleteNode(&head, 0);
//    printList(head);
//
//    printf("\nNumber of nodes: %d\n", countNodes(head));
//
//    printf("\nClearing list with value 30:\n");
//    clearListWithValue(&head, 30);
//    printList(head);
//
//    return 0;
//}

// Function to print the list
void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

// Function to insert a new node
void insertNode(Node** head, int data, int index) {
    if (index < 0) {
        return;
    } else if (index >= countNodes(*head) ) {
        appendNode(head, data);
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if (*head == NULL) {
        *head = newNode;
        newNode->next = newNode;
        return;
    }

    Node* current = *head;
    int count = 0;
    while (count < (index % countNodes(*head)) - 1) {
        current = current->next;
        count++;
    }

    if (count == 0) {
        Node* last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        newNode->next = *head;
        last->next = newNode;
        *head = newNode;
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}


void appendNode(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if (*head == NULL) {
        *head = newNode;
        newNode->next = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != *head) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = *head;
}


// Function to delete a node
void deleteNode(Node** head, int index) {
    if (*head == NULL) {
        return;
    }

    Node* current = *head;
    Node* prev = NULL;
    int count = 0;

    if (index == 0) {
        Node* last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        last->next = (*head)->next;
        free(*head);
        *head = last->next;
        return;
    }

    while (count < index % countNodes(*head)) {
        prev = current;
        current = current->next;
        count++;
    }

    prev->next = current->next;
    free(current);
}

// Function to count the number of nodes
int countNodes(Node* head) {
    if (head == NULL) {
        return 0;
    }

    Node* current = head;
    int count = 0;
    do {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}


// Function to clear the entire list if it contains an element equal to the specified value
void clearListWithValue(Node** head, int value) {
    Node* current = *head;
    Node* prev = NULL;
    int valueFound = 0;

    if (*head == NULL) {
        return;
    }

    do {
        if (current->data == value) {
            valueFound = 1;
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *head);

    if (valueFound) {
        current = *head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
            if (current == *head) {
                break;
            }
        }
        *head = NULL;
    }
}

