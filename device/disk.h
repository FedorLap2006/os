/** ШИНЫ
 ------------------
 * 00-03 ATA 
 * 04-05 FLOPPY
 * 08-FF PCI
 ------------------
 */

// Для доступа к I/O ATA
#define ATA_REG_DATA    0
#define ATA_REG_ERR     1
#define ATA_REG_COUNT   2
#define ATA_REG_SEC_NUM 3
#define ATA_REG_LBA_LO  3
#define ATA_REG_LBA_MID 4
#define ATA_REG_LBA_HI  5
#define ATA_REG_DEVSEL  6
#define ATA_REG_CMD     7

// Тип устройства
#define DISK_DEV_UNKNOWN      0
#define DISK_DEV_PATAPI       1
#define DISK_DEV_SATAPI       2
#define DISK_DEV_PATA         3
#define DISK_DEV_SATA         4

// Устройство ATA
struct ATA_DEVICE {

    word base;          // Базовый адрес
    word start;         // Стартовый сектор (0 или 1)
    word dev_ctl;       // Управляющий
    byte type;          // Тип девайса, например ATADEV_PATA
    byte identify[512]; // Информация от устройства
};

struct ATA_DEVICE ata_drive[4];  // 4 канала
