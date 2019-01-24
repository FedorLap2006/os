// https://wiki.osdev.org/ISA_DMA

/** Установка DMA Channel 2 на передачу данных в [0x1000 - 0x33ff] */
void fd_dma_init() {

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

/** Подготовить диск на запись */
void fd_dma_write() {

    IoWrite8(0x0A, 0x06);       // mask DMA channel 2 and 0 (assuming 0 is already masked)
    IoWrite8(0x0B, 0x5A);       // 01011010 single transfer, address increment, autoinit, write, channel2)
    IoWrite8(0x0A, 0x02);       // unmask DMA channel 2
}

/** Подготовить диск на чтение */
void fd_dma_read() {

    IoWrite8(0x0A, 0x06);       // mask DMA channel 2 and 0 (assuming 0 is already masked)
    IoWrite8(0x0B, 0x56);       // 01010110 single transfer, address increment, autoinit, read, channel2)
    IoWrite8(0x0A, 0x02);       // unmask DMA channel 2
}

// https://wiki.osdev.org/Floppy_Disk_Controller :: Programming Details
// http://bos.asmhackers.net/docs/floppy/docs/floppy_tutorial.txt
