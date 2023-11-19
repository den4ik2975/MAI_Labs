#include <stdio.h>
#include <ctype.h>

typedef enum {
    START,
    SCAN,
    WORD_SCAN,
    WAITING
} State;

unsigned int generate_bit_mask(){
    unsigned int bit_mask = 0;
    char vowels[6] = "aeiouy";

    for (int i=0; i <= 5; ++i){
        int index = vowels[i] - 'a';
        bit_mask |= (1 << index);
    }

    return bit_mask;
};

int main(){
    State state = START;
    char symbol;
    unsigned int bit_mask = generate_bit_mask();

    while (scanf("%c", &symbol) != EOF){
        symbol = tolower(symbol);

        switch (state) {
            case START:
            case SCAN:
                if (isalpha(symbol)){
                   unsigned int current_mask = 0;
                    int index = symbol - 'a';
                    current_mask |= (1 << index);

                    if ((bit_mask | current_mask) == bit_mask){
                        state = WORD_SCAN;
                    } else {
                        state = WAITING;
                    }
                } else {
                    state = SCAN;
                }
                break;

            case WORD_SCAN:
                if (isalpha(symbol)){
                    unsigned int current_mask = 0;
                    int index = symbol - 'a';
                    current_mask |= (1 << index);

                    if ((bit_mask | current_mask) == bit_mask){
                        state = WORD_SCAN;
                    } else {
                        state = WAITING;
                    }
                } else {
                    printf("God damn YES!!!");
                    return 0;
                }
                break;

            case WAITING:
                if (isalpha(symbol)){
                    state = WAITING;
                } else {
                    state = SCAN;
                }
        }
    }

    if (state == WORD_SCAN){
        printf("God damn YES!!!");
    } else {
        printf("No vowel word!");
    }

    return 0;
};