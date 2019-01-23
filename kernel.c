// Ядро: инициализация
#include "core/kernel.h"

#include "core/api.h"
#include "core/io.h"
#include "core/irq.h"

// Ядро: код
#include "core/irq.c"
#include "core/kernel.c"

void main() {

    kernel_init();

    for(;;);
}
