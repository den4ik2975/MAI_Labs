#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "headers/pc.h"
#include "headers/io.h"

int main()
{
    FILE *input_file = fopen("../input.txt", "r");
    FILE *output_file = fopen("../data.bin", "w");
    if (!output_file || !input_file)
    {
        printf("Error opening file.\n");
        return 1;
    }
    PersonalComputer *pc = (PersonalComputer *)malloc(sizeof(PersonalComputer));
    while (pc_read_txt(pc, input_file))
    {
        pc_write_bin(pc, output_file);
        pc_free(pc);
    }
    pc_write_bin(pc, output_file);
    pc_free(pc);
    free(pc);
    fclose(output_file);
    fclose(input_file);
    return 0;
}