// Ядро: инициализация
#include "core/kernel.h"

#include "core/api.h"
#include "core/io.h"
#include "core/irq.h"

// Устройства
#include "device/ps2.h"
#include "device/kbd.h"
#include "device/ps2/init.c"
#include "device/kbd/init.c"

// Ядро: код
#include "core/irq.c"
#include "core/kernel.c"

void main() {

    kernel_init();

    sti; for(;;);
}
