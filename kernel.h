
// Макросы для управления процессором
// ---------------------------------------------------------------------

#define brk __asm__ __volatile__("xchg %bx, %bx");
#define sti __asm__ __volatile__("sti");
#define cli __asm__ __volatile__("cli");

// Типы данных
// ---------------------------------------------------------------------
// См. http://ru.cppreference.com/w/cpp/language/types

#define byte     unsigned char          //  8 bit
#define word     unsigned short         // 16 bit
#define uint     unsigned int           // 32 bit
#define ulong    unsigned long long     // 64 bit

// Описание полей дескриптора
#define D_PRESENT     0x80
#define T_TSS_AVAIL   0x09

// Функции в startup.asm
// ---------------------------------------------------------------------

void apic_disable();            // Отключить LAPIC
void INT_null();                // Заглушка INT
void IRQ_timer();
void IRQ_keyboard();
void IRQ_ps2mouse();
void IRQ_cascade();
void IRQ_master();
void IRQ_slave();
void delay();

// Структуры
// ---------------------------------------------------------------------

// Указатель на GDT
struct __attribute__((__packed__)) GDT_ptr {

    word limit;
    uint base;
};

// Элемент GDT http://neurofox.net/sasm/14_descriptor
struct __attribute__((__packed__)) GDT_item {

    word    limit;
    word    addrlo;     // 15:0  Адрес
    byte     addrhl;     // 23:16 Адрес
    byte     access;     //       Биты доступа и типов
    byte     limithi;    // 19:16 Предел + GDXU-атрибуты
    byte     addrhh;     // 31:24 Адрес
};

// 32-х битный дескриптор прерывания
struct __attribute__((__packed__)) IDT_Item {

    word low_addr;
    word selector;
    word attr;
    word hi_addr;
};

// Расположение Global Descriptor Table
struct GDT_item* GDT;
