#ifndef GPIO_H
#define GPIO_H
#include <QFile>

/*
Connector P1 bananapi
pin function    usage       pin definition  IO on A20   /sys/class/gpio/..
1   3V3         -
2   5V          -
3   SDA         -
4   5V          -
5   SCL         -
6   GND         -
7   GCLK        -
8   UART_TX     -
9   GND         -
10  UART_RX     -
11  GPIO_0      encoder-A   IO-0            PI19        gpio17
12  GPIO_1      encoder-B   IO-1            PH2         gpio18 (and 19?)
13  GPIO_2      encoder-SW  IO-2            PI18        gpio27
14  GND
15  GPIO_3      PIR         IO-3            PI17        gpio22
16  GPIO_4      WHEEL       IO-4            PH20        gpio23
17  3V3
18  GPIO_5      LCD_POR     IO-5            PH21
19  SPI_MOSI
20  GND
21  SPI_MISO
22  GPIO_6      CAMERA      IO-6            PI16
23  PSI_CLK
24  SPI_CE0
25  GND
26  SPI_CE1
*/

class gpio
{
public:
    gpio(unsigned char numio, bool diroutput);
    ~gpio();
    int setVal(bool value);
    bool getVal(void);
private:
    QFile file;
    QString filename;
    qint64 opResult;
    unsigned char myNumIo;
    bool dirOutput;
};

#endif // GPIO_H
