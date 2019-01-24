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
#include "device/ps2/init.c"            // PS2 мышь
#include "device/kbd/init.c"            // Клавиатура
#include "device/vg/init.c"             // Видеоподсистема

// Ядро: код
#include "core/irq.c"
#include "core/stdio.c"
#include "core/kernel.c"

void main() {

    kernel_init();
    
    sti; for(;;);
}
