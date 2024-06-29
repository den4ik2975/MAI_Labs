#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "headers/io.h"
#include "headers/pc.h"

int get_type_input(char HELP_TEXT[], FILE* in) {
    printf("%s", HELP_TEXT);
    int type;
    fscanf(in, "%d", &type);
    while (type > 4) {
        printf("%s", HELP_TEXT);
        fscanf(in, "%d", &type);
    }
    return type;
}

void deleteLastSpace(char data[MAX_NAME_LENGTH]) {
    if (data[strlen(data) - 1] == '\n') {
        data[strlen(data) - 1] = '\0';
    }
}

char *getDiskType(int num) {
    switch (num) {
        case 0:
            return "SCSI";
        case 1:
            return "IDE";
        case 2:
            return "ATA";
        case 3:
            return "SATA";
        default:
            return "Unknowd disk type";
    }
}

char *getVideoType(int num) {
    switch (num) {
        case 0:
            return "INTEGRATED";
        case 1:
            return "EXTERNAL";
        case 2:
            return "AGP";
        case 3:
            return "PCI";
        default:
            return "Unknown video controller type";
    }
}

int pc_read_txt(PersonalComputer *pc, FILE *in) {
//    fscanf(in, "%s", pc->owner_surname);
    do {
        fgets(pc->owner_surname, sizeof(char) * MAX_NAME_LENGTH, in);
    } while (strcmp(pc->owner_surname, "\n") == 0);
    deleteLastSpace(pc->owner_surname);
    fscanf(in, "%d", &pc->processor_count);
//    while (pc->processor_count > 2) {
//        fscanf(in, "%d", &pc->processor_count);
//    }
    int count = pc->processor_count;
    for (int i = 0; i < count; ++i) {
        Processor *pr = (Processor *) malloc(sizeof(Processor));
//        fscanf(in, "%s", pr->type);
        do {
            fgets(pr->type, sizeof(char) * MAX_NAME_LENGTH, in);
        } while (strcmp(pr->type, "\n") == 0);
        deleteLastSpace(pr->type);
        pc->processors[i] = pr;
    }
    fscanf(in, "%d", &pc->ram_size);
    int video_type = get_type_input(VIDEO_HELP_TEXT, in);
    pc->video_controller_type = video_type - 1;
    fscanf(in, "%d", &pc->video_memory_size);
    fscanf(in, "%d", &pc->disks_count);
    while (pc->disks_count > MAX_DRIVES) {
        fscanf(in, "%d", &pc->disks_count);
    }
    count = pc->disks_count;
    for (int i = 0; i < count; ++i) {
        HardDrive *dr = (HardDrive *) malloc(sizeof(HardDrive));
        int drive_type = get_type_input(DRIVE_HELP_TEXT, in);
        dr->disk_controller_type = drive_type - 1;
        fscanf(in, "%d", &dr->capacity);
        pc->drives[i] = dr;
    }
    fscanf(in, "%d", &pc->external_device_count);
    count = pc->external_device_count;
    for (int i = 0; i < count; ++i) {
        ExternalDevice *ex = (ExternalDevice *) malloc(sizeof(ExternalDevice));
//        fscanf(in, "%s", ex->type);
        do {
            fgets(ex->type, sizeof(char) * MAX_NAME_LENGTH, in);
        } while (strcmp(ex->type, "\n") == 0);
        deleteLastSpace(ex->type);
        pc->external_devices[i] = ex;
    }
//    fscanf(in, "%s", pc->os);
    do {
        fgets(pc->os, sizeof(char) * MAX_NAME_LENGTH, in);
    } while (strcmp(pc->os, "\n") == 0);
    deleteLastSpace(pc->os);
    return !feof(in);
}

int pc_read_bin(PersonalComputer *pc, FILE *in) {
    fread(pc->owner_surname, sizeof(char), MAX_NAME_LENGTH, in);
    fread(&(pc->processor_count), sizeof(int), 1, in);
    int count = pc->processor_count;
    for (int i = 0; i < count; ++i) {
        Processor *pr = (Processor *) malloc(sizeof(Processor));
        fread(pr->type, sizeof(char), MAX_NAME_LENGTH, in);
        pc->processors[i] = pr;
//        free(pr);
    }
    fread(&(pc->ram_size), sizeof(int), 1, in);
    fread(&(pc->video_controller_type), sizeof(int), 1, in);
    fread(&(pc->video_memory_size), sizeof(int), 1, in);
    fread(&(pc->disks_count), sizeof(int), 1, in);
    count = pc->disks_count;
    for (int i = 0; i < count; ++i) {
        HardDrive *dr = (HardDrive *) malloc(sizeof(HardDrive));
        fread(&dr->capacity, sizeof(int), 1, in);
        fread(&dr->disk_controller_type, sizeof(int), 1, in);
        pc->drives[i] = dr;
//        free(dr);
    }
    fread(&(pc->external_device_count), sizeof(int), 1, in);
    count = pc->external_device_count;
    for (int i = 0; i < count; ++i) {
        ExternalDevice *ex = (ExternalDevice *) malloc(sizeof(ExternalDevice));
        fread(ex->type, sizeof(char), MAX_NAME_LENGTH, in);
        pc->external_devices[i] = ex;
//        free(ex);
    }
    fread(pc->os, sizeof(char), MAX_NAME_LENGTH, in);
    return !feof(in);
}

void pc_write_bin(PersonalComputer *pc, FILE *out) {
    fwrite(pc->owner_surname, sizeof(char), MAX_NAME_LENGTH, out);
    fwrite(&(pc->processor_count), sizeof(int), 1, out);
    for (int i = 0; i < pc->processor_count; ++i) {
        fwrite(pc->processors[i]->type, sizeof(char), MAX_NAME_LENGTH, out);
    }
    fwrite(&(pc->ram_size), sizeof(int), 1, out);
    fwrite((&pc->video_controller_type), sizeof(int), 1, out);
    fwrite(&(pc->video_memory_size), sizeof(int), 1, out);
    fwrite(&(pc->disks_count), sizeof(int), 1, out);

    for (int i = 0; i < pc->disks_count; ++i) {
        fwrite(&pc->drives[i]->capacity, sizeof(int), 1, out);
        fwrite(&pc->drives[i]->disk_controller_type, sizeof(int), 1, out);
    }
    fwrite(&(pc->external_device_count), sizeof(int), 1, out);
    for (int i = 0; i < pc->external_device_count; ++i) {
        fwrite(pc->external_devices[i]->type, sizeof(char), MAX_NAME_LENGTH, out);
    }
    fwrite(pc->os, sizeof(char), MAX_NAME_LENGTH, out);
}

void pc_print(PersonalComputer *pc) {
    printf("Owner surname: %s\n", pc->owner_surname);
    printf("Processor count: %d\n", pc->processor_count);
    for (int i = 0; i < pc->processor_count; ++i) {
        printf("Processor #%d type: %s\n", i + 1, pc->processors[i]->type);
    }
    printf("RAM capacity: %d\n", pc->ram_size);
    printf("Video controller type: %s\n", getVideoType(pc->video_controller_type));
    printf("Video memory capacity: %d\n", pc->video_memory_size);
    printf("Drives count: %d\n", pc->disks_count);
    for (int i = 0; i < pc->disks_count; ++i) {
        printf("Disk #%d:\n", i + 1);
        printf("Disk capacity: %d\n", pc->drives[i]->capacity);
        printf("Disk controller type: %s\n", getDiskType(pc->drives[i]->disk_controller_type));
    }
    printf("External devices count: %d\n", pc->external_device_count);
    for (int i = 0; i < pc->external_device_count; ++i) {
        printf("External device #%d: %s\n", i + 1, pc->external_devices[i]->type);
    }
    printf("OS: %s\n", pc->os);
}

void pc_free(PersonalComputer *pc) {
    int count = pc->processor_count;
    for (int i = 0; i < count; ++i) {
        free(pc->processors[i]);
        pc->processors[i] = NULL;
    }
    count = pc->disks_count;
    for (int i = 0; i < count; ++i) {
        free(pc->drives[i]);
        pc->drives[i] = NULL;
    }
    count = pc->external_device_count;
    for (int i = 0; i < count; ++i) {
        free(pc->external_devices[i]);
        pc->external_devices[i] = NULL;
    }
    for (int i = 0; i < MAX_NAME_LENGTH; ++i) {
        pc->owner_surname[i] = '\0';
    }
    for (int i = 0; i < MAX_NAME_LENGTH; ++i) {
        pc->os[i] = '\0';
    }
//    pc = (PersonalComputer *) malloc(sizeof(PersonalComputer));
}