#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <stdlib.h>
#include "pc.h"

#define VIDEO_HELP_TEXT "Video Controller type: integrated - 1, external - 2, AGP - 3, PCI - 4: "
#define DRIVE_HELP_TEXT "Disk Controller type: SCSI - 1, IDE - 2, ATA - 3, SATA - 4: "


int pc_read_txt(PersonalComputer *pc, FILE *in);

int pc_read_bin(PersonalComputer *pc, FILE *in);

void pc_write_bin(PersonalComputer *pc, FILE *out);

void pc_print(PersonalComputer *pc);

void pc_free(PersonalComputer *pc);

#endif