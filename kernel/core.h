int create_gdt(uint32_t, uint32_t, uint8_t);

// Драйвер видеокарты
struct DriverVG {
    
    // Видеохолст (задний буфер)
    uint32_t* canvas; 

    // Установка точки (x, y, color)    
    void (*pset)(int, int, int);   
    
    // LINE (x1,y1)-(x2,y2),color,bf
    void (*block)(int, int, int, int, int); 
};

// Обработчик графикии
struct DriverVG vg;
