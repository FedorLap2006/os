#include "ata.c"
#include "floppy.c"

// Получение типа диска
int disk_get_type(byte disk_id) {

    switch (disk_id) {

        case 0: /* ata bus pri master */
        case 1: /* ata bus pri slave */
        case 2: /* ata bus sec master */
        case 3: /* ata bus sec slave */
            return ata_drive[ disk_id ].type;

        case 4: /* fd 0 */ break;
        case 5: /* fd 1 */ break;
    }

    return DISK_DEV_UNKNOWN;
}

/** Обработчик прерывания от FDC */
void fdc_irq() {

    byte cyl;

    switch (fdc.status) {

        /** Поиск дорожки */
        case FDC_STATUS_SEEK:

            // @todo проверить
            cyl = fdc_sensei();

            // @todo запуск чтения или записи данных
            break;

        /** Чтение или запись */
        case FDC_STATUS_RW:

            if (fdc_get_result()) {
                // произошла ошибка поиска
            }

            break;
    }

    fdc.irq_ready = 1;
}

void init_disk() {

    int device_id;

    // Диск выключен
    fdc.irq_ready   = 0;
    fdc.status      = FDC_STATUS_NONE;

    // Назначить методы
    pic.fdc = & fdc_irq;

    // Получение типа диска
    disk.get_type = & disk_get_type;

    // Подготовка DMA
    fdc_dma_init();

    // Просмотр всех ATA-устройств
    for (device_id = 0; device_id < 4; device_id++) {

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
