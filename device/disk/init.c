#include "ata.c"

// Получение типа диска
int disk_get_type(byte disk_id) {

    switch (disk_id) {

        case 0: /* ata bus 0 master */
        case 1: /* ata bus 0 slave */
        case 2: /* ata bus 1 master */
        case 3: /* ata bus 1 slave */
            return ata_drive[ disk_id ].type;

        case 4: /* fd 0 */ break;
        case 5: /* fd 1 */ break;
    }

    return DISK_DEV_UNKNOWN;
}

void init_disk() {

    int device_id;

    // Назначить методы
    disk.get_type = & disk_get_type;

    // Просмотр всех ATA-устройств
    for (device_id = 0; device_id < 4; device_id++) {
brk;
        // Определить тип устройства
        ata_drive[ device_id ].base    = device_id < 2 ? 0x1F0 : 0x170;
        ata_drive[ device_id ].dev_ctl = device_id < 2 ? 0x3F6 : 0x376;
        ata_drive[ device_id ].type    = ata_detect_devtype(device_id & 1, & ata_drive[ device_id ]);

        // Если устройство не готово
        if (!ata_identify(device_id)) {
            ata_drive[ device_id ].type = DISK_DEV_UNKNOWN;
        }
    }
}
