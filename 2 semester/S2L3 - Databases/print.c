#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "headers/pc.h"
#include "headers/io.h"

int main() {
    FILE *output_file = fopen("../data.bin", "r");
    if (!output_file) {
        printf("Error opening file.\n");
        return 1;
    }
    PersonalComputer *pc = (PersonalComputer*) malloc(sizeof(PersonalComputer));
    while (pc_read_bin(pc, output_file)) {
        pc_print(pc);
        pc_free(pc);
        printf("------");
    }
    pc_free(pc);
    free(pc);
//    while (status)
//    {
//        pc_print(pc);
//        printf("\n");
////        pc = (PersonalComputer *)malloc(sizeof(PersonalComputer));
//        status = pc_read_bin(pc, output_file);
//    }
//    pc_free(pc);

    fclose(output_file);
    return 0;
}