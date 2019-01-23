/** Процедура инициализации ядра */
void kernel_init() {

    apic_disable();    

    /* Переназначить новые прерывания */
    irq_init(IRQ_TIMER | IRQ_KEYB | IRQ_CASCADE | IRQ_PS2MOUSE);

    /* Инициализировать клавиатуру и мышь */
    kbd_init();
    ps2_init_mouse();
}
