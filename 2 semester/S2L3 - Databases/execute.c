// ����: upgrade.c

#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include "headers/pc.h"
#include "headers/io.h"

int main(int argc, char *argv[])
{
    char *str;
    int p;
    if (argc != 3)
    {
        printf("Usage: %s <PC data file> <p>\n", argv[0]);
        return 1;
    }
    long conv = strtol(argv[2], &str, 10);
    if (*str != '\0' || conv > INT_MAX || conv < INT_MIN)
    {
        printf("Error with p argument");
        return 1;
    }
    else
    {
        p = conv;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    PersonalComputer *pc = (PersonalComputer *)malloc(sizeof(PersonalComputer));
    int pc_count = 0;

    while (pc_read_bin(pc, input_file))
    {
        if (pc->processor_count == 2 && pc->external_device_count <= p)
        {
            printf("Student \"%s\" have 2 processors and %d external devices\n", pc->owner_surname,
                   pc->external_device_count);
            pc_count++;
        }
        pc_free(pc);
    }
    pc_free(pc);
    free(pc);

    if (pc_count == 0)
    {
        printf("No student satisfies the specified parameters.\n");
    }

    fclose(input_file);
    return 0;
}