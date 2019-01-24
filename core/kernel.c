/** Определение максимального объема памяти */
void detect_max_memory_size() {

    byte* m   = (byte*)1;
    uint  max = 0xDFFFFFFF;
    uint  min = 0x00200000;
    uint  mid;

    while (min < max) {

        mid = (min + max) >> 1;

        // Область страниц совпала. Максимальное количество памяти в `max`
        if ((min & 0xfffff000) + 0x1000 >= (max & 0xfffff000)) {

            mm_real_max = (max & 0xfffff000);
            mm_syst_max = SYSTEM_MEMORY_MB << 20;
            mm_syst_max = max < mm_syst_max ? max : mm_syst_max;
            break;
        }

        // Проверка на способность памяти измениться в этой точке
        volatile byte a = peek(mid); m[ mid-1 ] ^= 0x55;
        volatile byte b = peek(mid); m[ mid-1 ] ^= 0x55;

        if (a == b) {
            max = mid; // Здесь mid слишком высок
        } else {
            min = mid; // Поднять mid
        }
    }
}

/** Выделение резидентной памяти */
void* kalloc(uint size) {

    mm_syst_max -= size;
    return (void*) mm_syst_max;
}

/** Инициалиазция нового GDT из старых данных */
void copy_GDT() {

    uint i;
    qword GDT_mem_base;

    // Выделить системную память под новую
    byte* m = (byte*) kalloc(65536);

    // Записать адрес таблицы
    GDT = (struct GDT_item*)m;

    // Сохранение старого GDT
    asm volatile("sgdt %0" : "=m"(GDT_mem_base) : : "memory");

    // Получение предыдущего адреса
    dword GDT_addr  =  GDT_mem_base >> 16;
    dword GDT_limit = (GDT_mem_base & 0xFFFF) + 1;

    // Копирование из предыдущего GDT
    byte* s = (byte*)GDT_addr;

    // Перенос старых данных и полная очистка таблицы
    for (i = 0; i < GDT_limit; i++) m[i] = s[i];
    for (i = GDT_limit; i < 65536; i++) m[i] = 0;

    // Количество дескрипторов будет пока что тоже самое
    GDT_mem_base = ((qword)m << 16) | (GDT_limit - 1);

    // Загрузить новый GDT
    asm volatile("lgdt %0" : : "m"(GDT_mem_base) : "memory");
}

/** Процедура инициализации ядра */
void kernel_init() {

    apic_disable();

    /* Переназначить новые прерывания */
    irq_init(IRQ_TIMER | IRQ_KEYB | IRQ_CASCADE | IRQ_PS2MOUSE);

    /* Инициализировать клавиатуру и мышь */
    kbd_init();
    ps2_init_mouse();

    /* Определение размера памяти */
    detect_max_memory_size();

    /* Перенести GDT */
    copy_GDT();

    /* Инициализация видеоподсистемы */
    init_vg();

    /* Создание страниц */
    /* Создание главной задачи */
    /* Инициализация дисков */
}
