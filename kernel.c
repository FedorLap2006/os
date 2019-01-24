// Ядро: инициализация
#include "core/kernel.h"

#include "core/api.h"
#include "core/io.h"
#include "core/irq.h"
#include "core/stdio.h"

// Устройства
#include "device/ps2.h"
#include "device/kbd.h"
#include "device/vg.h"
#include "device/disk.h"

#include "device/ps2/init.c"            // PS2 мышь
#include "device/kbd/init.c"            // Клавиатура
#include "device/vg/init.c"             // Видеоподсистема
#include "device/disk/init.c"           // Дисковая подсистема

// Ядро: код
#include "core/irq.c"
#include "core/stdio.c"
#include "core/kernel.c"

void main() {

    kernel_init();

    sti;

    brk;
//    fdc_reset();

    // чтение сектора
    // fdc_read(0);

    fdc_motor_on();
    fdc_seek(0, 0);
    while (fdc.irq_ready == 0);

brk;
    fdc_dma_read();
    fdc_rw(0, 0, 0, 1);

    while (fdc.irq_ready == 0);

    for(;;);
}
