#ifndef PC_H
#define PC_H

#define MAX_NAME_LENGTH 24
#define MAX_PROCESSORS 5
#define MAX_DRIVES 10
#define MAX_EXTERNAL 100
typedef enum {
    INTEGRATED = 0,
    EXTERNAL,
    AGP,
    PCI
} VideoControllerType;

char *getVideoType(int num);

typedef enum {
    SCSI = 0,
    IDE,
    ATA,
    SATA
} DiskControllerType;

char *getDiskType(int num);

typedef struct {
    char type[MAX_NAME_LENGTH];
} Processor;
typedef struct {
    int capacity;
    DiskControllerType disk_controller_type;
} HardDrive;

typedef struct {
    char type[MAX_NAME_LENGTH];
} ExternalDevice;

typedef struct {
    char owner_surname[MAX_NAME_LENGTH];
    int processor_count;
    Processor *processors[MAX_PROCESSORS];
    int ram_size;
    VideoControllerType video_controller_type;
    int video_memory_size;
    int disks_count;
    HardDrive *drives[MAX_DRIVES];
    int external_device_count;
    ExternalDevice *external_devices[MAX_EXTERNAL];
    char os[MAX_NAME_LENGTH];
} PersonalComputer;

#endif
