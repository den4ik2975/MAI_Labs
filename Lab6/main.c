#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    START,
    SCAN,
    HEX_SCAN,
    HEX_SAVE,
    LAST_SAVE,
    END
} State;

int is_hex(char c) {
    return (isdigit(c) || (tolower(c) >= 'a' && tolower(c) <= 'f'));
}


int main() {
    State state = START;
    char symbol;
    char current_hex[256] = {0};
    char last_hex[256] = {0};
    char penultimate_hex[256] = {0};
    int index_counter = 0;

    while (scanf("%c", &symbol) != EOF){
        switch (state) {
            case START:
            case SCAN:
                if (is_hex(symbol)){
                    current_hex[index_counter++] = symbol;
                    state = HEX_SCAN;
                } else {
                    state = SCAN;
                }
                break;

            case HEX_SCAN:
                if (is_hex(symbol)){
                    current_hex[index_counter++] = symbol;
                    state = HEX_SCAN;
                } else {
                    state = HEX_SAVE;
                }
                break;

            case HEX_SAVE:
                current_hex[index_counter] = '\0';
                strcpy(penultimate_hex, last_hex);
                strcpy(last_hex, current_hex);
                index_counter = 0;
                current_hex[0] = '\0';

                if (is_hex(symbol)){
                    current_hex[index_counter++] = symbol;
                    state = HEX_SCAN;
                } else {
                    state = SCAN;
                }
                break;

            default:
                break;
        }
    }

    if (state == HEX_SCAN || HEX_SAVE) {
        state = LAST_SAVE;
        current_hex[index_counter] = '\0';
        strcpy(penultimate_hex, last_hex);
        strcpy(last_hex, current_hex);
    }
    state = END;

    if (penultimate_hex[0] != '\0') {
        printf("Penultimate hex number: %s\n", penultimate_hex);
    } else {
        printf("There's only one hex number.\n");
    }

    return 0;
}
