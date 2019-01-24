// https://wiki.osdev.org/ISA_DMA
// https://wiki.osdev.org/Floppy_Disk_Controller :: Programming Details
// http://bos.asmhackers.net/docs/floppy/docs/floppy_tutorial.txt

/** Установка DMA Channel 2 на передачу данных в [0x1000 - 0x33ff] */
void fdc_dma_init() {

    IoWrite8(0x0A, 0x06);       // mask DMA channel 2 and 0 (assuming 0 is already masked)

    // Запись адреса
    IoWrite8(0x0C, 0xFF);       // reset the master flip-flop
    IoWrite8(0x04, 0x00);       // address to 0x00 (low byte)
    IoWrite8(0x04, 0x10);       // address to 0x10 (high byte)

    // Запись количества
    IoWrite8(0x0C, 0xFF);       // reset the master flip-flop (again!!!)
    IoWrite8(0x05, 0xFF);       // count to 0x23ff (low byte)
    IoWrite8(0x05, 0x23);       // count to 0x23ff (high byte)

    // Верхний адрес
    IoWrite8(0x81, 0x00);       // external page register to 0 for total address of 00 10 00
    IoWrite8(0x0A, 0x02);       // unmask DMA channel 2
}

/** Подготовить диск на чтение */
void fdc_dma_read() {

    IoWrite8(0x0A, 0x06);       // mask DMA channel 2 and 0 (assuming 0 is already masked)
    IoWrite8(0x0B, 0x56);       // 01010110 single transfer, address increment, autoinit, read, channel2)
    IoWrite8(0x0A, 0x02);       // unmask DMA channel 2
}

/** Подготовить диск на запись */
void fdc_dma_write() {

    IoWrite8(0x0A, 0x06);       // mask DMA channel 2 and 0 (assuming 0 is already masked)
    IoWrite8(0x0B, 0x5A);       // 01011010 single transfer, address increment, autoinit, write, channel2)
    IoWrite8(0x0A, 0x02);       // unmask DMA channel 2
}

/** Запись данных */
void fdc_write_reg(byte reg) {

    while ((IoRead8(MAIN_STATUS_REGISTER) & 0x80) != 0x80);
    IoWrite8(DATA_FIFO, reg);
}

/** Чтение данных */
byte fdc_read_reg() {

    while ((IoRead8(MAIN_STATUS_REGISTER) & 0xC0) != 0xC0);
    return IoRead8(DATA_FIFO);
}

/** Включение мотора */
void fdc_motor_on() {
    IoWrite8(DIGITAL_OUTPUT_REGISTER, 0x1C);
}

/** Выключить мотор */
void fdc_motor_off() {
    IoWrite8(DIGITAL_OUTPUT_REGISTER, 0);
}

/** Включить IRQ после SEEK */
byte fdc_sensei() {

    byte r;

    do {

        fdc_write_reg(SENSE_INTERRUPT); // get interrupt status command
        r = fdc_read_reg();             // получение результата

    } while (r & 0x80);

    // Возвращается номер цилиндра
    return fdc_read_reg();
}

/** Сбор результирующих данных: если > 0, то ошибка */
int fdc_get_result() {

    fdc.st0         = fdc_read_reg();
    fdc.st1         = fdc_read_reg();
    fdc.st2         = fdc_read_reg();
    fdc.cyl         = fdc_read_reg();
    fdc.head_end    = fdc_read_reg();
    fdc.head_start  = fdc_read_reg();
    fdc_read_reg();

    return (fdc.st0 & 0xC0);
}

/** Чтение и запись в DMA => IRQ #6
 * write = 0 READ; 1 WRITE
 * head=0..1
 * cyl=0..79
 * */
void fdc_rw(byte write, byte head, byte cyl, byte sector) {

    // MFM_bit = 0x40 | (W=0x45 | R=0x46)

    /* 0 */ fdc_write_reg(write ? 0x45 : 0x46);
    /* 1 */ fdc_write_reg(head << 2);
    /* 2 */ fdc_write_reg(cyl);
    /* 3 */ fdc_write_reg(head);
    /* 4 */ fdc_write_reg(sector);
    /* 5 */ fdc_write_reg(2);       // Размер сектора (2 ~> 512 bytes)
    /* 6 */ fdc_write_reg(18);      // Последний сектор в цилиндре
    /* 7 */ fdc_write_reg(0x1B);    // Длина GAP3
    /* 8 */ fdc_write_reg(0xFF);    // Длина данных, игнорируется

    fdc.irq_ready = 0;
    fdc.status = FDC_STATUS_RW;
}

/** Чтение сектора в $1000 */
void fdc_read(int lba) {
    
}

/** Запись сектора из $1000 */
void fdc_write(int lba) {
    
}

/** Поиск дорожки => IRQ #6 */
void fdc_seek(byte head, byte cyl) {

    fdc_write_reg(0x0F);
    fdc_write_reg(head << 2);
    fdc_write_reg(cyl);

    fdc.irq_ready = 0;
    fdc.status = FDC_STATUS_SEEK;
}
