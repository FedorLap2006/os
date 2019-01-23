// Ядро: инициализация
#include "core/kernel.h"

#include "core/api.h"
#include "core/io.h"
#include "core/irq.h"
#include "device/ps2.h"

// Устройства
#include "device/ps2/init.c"

// Ядро: код
#include "core/irq.c"
#include "core/kernel.c"

void main() {

    kernel_init();

    for(;;);
}
