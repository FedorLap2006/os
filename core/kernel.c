/** Процедура инициализации ядра */
void kernel_init() {

    /* Переназначить новые прерывания */
    irq_init(IRQ_KEYB | IRQ_CASCADE | IRQ_PS2MOUSE | IRQ_TIMER);
    
    /* Инициализировать мышь */
    ps_init_mouse();
}
