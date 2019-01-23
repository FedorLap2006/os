
// Писать в (port) данные data
// ---------------------------------------------------------------------

static inline void IoWrite8(word port, byte data) {
    __asm__ volatile("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

static inline void IoWrite16(word port, word data) {
    __asm__ volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

static inline void IoWrite32(word port, uint data) {
    __asm__ volatile("outl %0, %w1" : : "a" (data), "Nd" (port));
}

// Читать данные из порта (port)
// ---------------------------------------------------------------------
static inline byte IoRead8(word port) {

    byte data;
    __asm__ volatile("inb %1, %0" : "=a" (data) :"Nd" (port));
    return data;
}

static inline word IoRead16(word port) {

    word data;
    __asm__ volatile("inw %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline uint IoRead32(word port) {

    uint data;
    __asm__ volatile("inl %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}
