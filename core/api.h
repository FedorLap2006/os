// Видеоподсистема
struct DriverVG {

    // Размер по ширине и высоте
    uint w, h;

    // Видеохолст (задний буфер)
    word* canvas;

    // Установка точки (x, y, color)
    void (*pset)(int, int, uint);

    // LINE (x1,y1)-(x2,y2),color,bf
    void (*block)(int, int, int, int, uint);
};

// Программируемые прерывания
struct DriverPIC {
    
    void (*keyboard)();
    void (*ps2mouse)();
    void (*timer)();

};

// Обработчик графикии
struct DriverVG  vg;
struct DriverPIC pic;
