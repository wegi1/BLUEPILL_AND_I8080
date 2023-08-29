#include "Arduino.h"
#include <stdlib.h>
#include "ili9341.h"
_lcd_dev lcddev;
extern void Put_Pixel(uint16_t  plot_X, uint16_t  plot_Y, uint16_t color );
/*---------------------------------------------------------------------*/
static const uint8_t init_tab[] = {
    ILI_PCB, 3, 0x00, 0xC1, 0X30,
    ILI_POSC, 4, 0x64, 0x03, 0X12, 0X81,
    ILI_DTCA_ic, 3, 0x85, 0x10, 0x7A,
    ILI_PCA, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
    ILI_PRC, 1, 0x20,
    ILI_DTCB, 2, 0x00, 0x00,
    ILI_PWCTRL1, 1, 0x1B,
    ILI_PWCTRL2, 1, 0x01,
    ILI_VMCTRL1, 2, 0x30, 0x30,
    ILI_VMCTRL2, 1, 0XB7,
    ILI_MADCTL, 1, 0x48,
    ILI_PIXSET, 1, 0x55,
    ILI_FRMCTR1, 2, 0x00, 0x1A,
    ILI_DISCTRL, 2, 0x0A, 0xA2,
    ILI_E3G, 1, 0x00,
    ILI_GAMSET, 1, 0x01,
    ILI_PGAMCTRL, 15, 0x0F, 0x2A, 0x28, 0x08, 0x0E, 0x08, 0x54, 0XA9, 0x43, 0x0A, 0x0F, 0x00, 0x00, 0x00, 0x00,
    ILI_NGAMCTRL, 15, 0x00, 0x15, 0x17, 0x07, 0x11, 0x06, 0x2B, 0x56, 0x3C, 0x05, 0x10, 0x0F, 0x3F, 0x3F, 0x0F,
    ILI_PASET, 4, 0x00, 0x00, 0x01, 0x3f,
    ILI_CASET, 4, 0x00, 0x00, 0x00, 0xef,
    ILI_SLPOUT, 120,
    ILI_DISPON, 0,
    ILI_MADCTL, 1, 0xC9,
    0x00};

void LCD_DrawLine(uint16_t color, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (y1 == y2)
    {
        LCD_DisARectangular(x1, y1, x2, y2, color);
        return;
    }

    if (x1 == x2)
    {
        LCD_DisARectangular(x1, y1, x2, y2, color);
        return;
    }

    int steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep)
    {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx, dy;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    int err = dx / 2;
    int ystep;
    if (y1 < y2)
        ystep = 1;
    else
        ystep = -1;

    for (; x1 <= x2; x1++)
    {
        if (steep)
            Put_Pixel(y1, x1, color);
        else
            Put_Pixel(x1, y1, color);
        err -= dy;
        if (err < 0)
        {
            y1 += ystep;
            err += dx;
        }
    }
}
// ���������������������
//------------------------------------

//------------------------------------

/*--------------------------------------------------------------------*/

/********************************************************************************************************
 *  Function: LCD_OpenWin
 *  Object: lcd open window for display
 *  Input: x0,y0, x1, y1
 *  Output: none
 *  brief: none
 ********************************************************************************************************/
void LCD_OpenWin(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

    LCD_WriteReg(ILI_CASET);
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0);
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1);
    LCD_WriteReg(ILI_PASET);
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0);
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1);
    LCD_WriteReg(ILI_RAMWR);
}

/********************************************************************************************************
 *  Function: LCD_DisALoop
 *  Object: Display a loop
 *  Input: site,radius and color
 *  Output: none
 *  brief: none
 ********************************************************************************************************/
void LCD_DisALoop(uint16_t x0, uint16_t y0, uint8_t r, uint16_t Color)
{
    int16_t a, b, next;
    a = 0;
    b = r;
    next = 3 - (r << 1);
    while (a <= b)
    {
        Put_Pixel(x0 + a, y0 - b, Color);
        Put_Pixel(x0 + b, y0 - a, Color);
        Put_Pixel(x0 + b, y0 + a, Color);
        Put_Pixel(x0 + a, y0 + b, Color);
        Put_Pixel(x0 - a, y0 + b, Color);
        Put_Pixel(x0 - b, y0 + a, Color);
        Put_Pixel(x0 - a, y0 - b, Color);
        Put_Pixel(x0 - b, y0 - a, Color);
        a++;
        // use the bresenham
        if (next < 0)
            next += 4 * a + 6;
        else
        {
            next += 10 + 4 * (a - b);
            b--;
        }
    }
}
/********************************************************************************************************
 *  Function: LCD_DisAPoint
 *  Object: Display a point at screen
 *  Input: site and color
 *  Output: none
 *  brief: none
 ********************************************************************************************************/
void LCD_DisAPoint(uint16_t x0, uint16_t y0, uint16_t Color)
{
    LCD_WriteReg(ILI_CASET);
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0);
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0);
    LCD_WriteReg(ILI_PASET);
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0);
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0);
    LCD_WriteReg(ILI_RAMWR);
    LCD_WriteData(Color);
}
/********************************************************************************************************
 *  Function: LCD_DisASquare
 *  Object: Display a square
 *  Input: start point, wide, color
 *  Output: none
 *  brief: none
 ********************************************************************************************************/
void LCD_DisASquare(uint16_t x0, uint16_t y0, uint16_t wide, uint16_t Color)
{
    uint32_t i;
    LCD_OpenWin(x0, y0, x0 + wide - 1, y0 + wide - 1);
    for (i = 0; i < (wide * wide); i++)
        LCD_WriteData(Color);
}
/********************************************************************************************************
 *  Function: LCD_DisARectangular
 *  Object: Display a rectangular
 *  Input: start point, end point, color
 *  Output: none
 *  brief: none
 ********************************************************************************************************/
void LCD_DisARectangular(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color)
{
    uint32_t i;
    uint16_t x00, x01, y00, y01;

    if (x0 < x1)
    {
        x00 = x0;
        x01 = x1;
    }
    else
    {
        x00 = x1;
        x01 = x0;
    }

    if (y0 < y1)
    {
        y00 = y0;
        y01 = y1;
    }
    else
    {
        y00 = y1;
        y01 = y0;
    }

    LCD_OpenWin(x00, y00, x01, y01);

    for (i = 0; i <= ((1 + x01 - x00) * (1 + y01 - y00)); i++)
    {
        LCD_WriteData(Color);
    }
}
/********************************************************************************************************
 *  Function: LCD_ClrScr
 *  Object: lcd clear screen
 *  Input: backcolor
 *  Output: none
 *  brief: none
 ********************************************************************************************************/
void LCD_ClrScr(uint16_t BackColor)
{
  
        LCD_FILL_A_Rectangular(0, 0, lcddev.height, lcddev.width, BackColor);
//  LCD_FILL_A_Rectangular(0, 0, LCD_H, LCD_W, BackColor);
        
 
}
/*******************************************************************************************************
 * drawing no fill rectangle
 ******************************************************************************************************/
void LCD_No_Fill_Draw(uint16_t color, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_DrawLine(color, x0, y0, x1, y0);
    LCD_DrawLine(color, x0, y1, x1, y1);
    LCD_DrawLine(color, x0, y0, x0, y1);
    LCD_DrawLine(color, x1, y0, x1, y1);
}
//*******************************************************************************************************
//*******************************************************************************************************

/**************************************************************************/
/*!
   @brief    Draw a circle with filled color
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    color 16-bit 5-6-5 Color to fill with
 */
/**************************************************************************/
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    writeFastVLine(x0, y0 - r, 2 * r + 1, color);
    fillCircleHelper(x0, y0, r, 3, 0, color);
}
/**************************************************************************/
/*!
    @brief  Quarter-circle drawer with fill, used for circles and roundrects
    @param  x0       Center-point x coordinate
    @param  y0       Center-point y coordinate
    @param  r        Radius of circle
    @param  corners  Mask bits indicating which quarters we're doing
    @param  delta    Offset from center-point, used for round-rects
    @param  color    16-bit 5-6-5 Color to fill with
 */
/**************************************************************************/
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color)
{

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    int16_t px = x;
    int16_t py = y;

    delta++; // Avoid some +1's in the loop

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if (x < (y + 1))
        {
            if (corners & 1)
                writeFastVLine(x0 + x, y0 - y, 2 * y + delta, color);
            if (corners & 2)
                writeFastVLine(x0 - x, y0 - y, 2 * y + delta, color);
        }
        if (y != py)
        {
            if (corners & 1)
                writeFastVLine(x0 + py, y0 - px, 2 * px + delta, color);
            if (corners & 2)
                writeFastVLine(x0 - py, y0 - px, 2 * px + delta, color);
            py = y;
        }
        px = x;
    }
}
/*****************************************
 * help function to write H | V lines
 *****************************************/
void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    // LCD_DrawLine(color, x, y, x, y + h - 1);
    LCD_FILL_A_Rectangular(x, y, x, y + h - 1, color);
}
void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    // LCD_DrawLine(color, x, y, x + w - 1, y);
    LCD_FILL_A_Rectangular(x, y, x + w - 1, y, color);
}
/*******************************************************************************************************
 * end of screen functions
 *******************************************************************************************************/

//*******************************************************************************************************
//*******************************************************************************************************
//*******************************************************************************************************

/*****************************************************************************************************
 *
 * initialize sequence ILI_9341
 *
 ***************************************************************************************************/
void LCD_ILI9341_init(void)
{
    uint32_t i = 0;
    uint32_t i2;
    uint8_t counter;

    LCD_initIO();

    while (init_tab[i] != 0)
    {
        LCD_WriteReg((uint16_t)init_tab[i]);
        counter = init_tab[i + 1];
        i += 2;
        if (counter > 15)
        {
            delay(counter);
        }
        else if (counter > 0)
        {
            for (i2 = 0; i2 < counter; i2++)
            {
                LCD_WriteData(init_tab[i + i2]);
            }
            i += counter;
        }
    }

    /*****************/
    LCD_WriteReg(0x3A);
    LCD_WriteData(0x55);
    /*****************/
    LCD_WriteReg(0x36);
    // LCD_WriteData(0x49);
    LCD_WriteData(0x49);
    // LCD_WriteReg(0x21);
    /*****************/

    digitalWrite(PA15, HIGH);
}

void LCD_initIO()
{

    // BalckLight
    RCC->APB2ENR  |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;
    pinMode(PA15, OUTPUT);
    // GPIOA->CRH = 0x18844444;
    digitalWrite(PA15, HIGH);
    // Data bus
    // pinMode(PB15, OUTPUT); // D15
    // pinMode(PB14, OUTPUT); // D14
    // pinMode(PB13, OUTPUT); // D13
    // pinMode(PB12, OUTPUT); // D12
    // pinMode(PB11, OUTPUT); // D11
    // pinMode(PB10, OUTPUT); // D10
    // pinMode(PB9, OUTPUT);  // D9
    // pinMode(PB8, OUTPUT);  // D8
    // pinMode(PA7, OUTPUT);  // D7
    // pinMode(PA6, OUTPUT);  // D6
    // pinMode(PA5, OUTPUT);  // D5
    // pinMode(PA4, OUTPUT);  // D4
    // pinMode(PA3, OUTPUT);  // D3
    // pinMode(PA2, OUTPUT);  // D2
    // pinMode(PA1, OUTPUT);  // D1
    // pinMode(PA0, OUTPUT);  // D0

    GPIOA->CRL = 0x33333333;
    GPIOB->CRH = 0x33333333;

    // CS,RS,WE,OE
    // pinMode(PB6, OUTPUT); // CS
    // pinMode(PB5, OUTPUT); // RS
    // pinMode(PB4, OUTPUT); // WE
    // pinMode(PB3, OUTPUT); // OE
    GPIOB->CRL = 0x41333444;

    digitalWrite(csPin, LOW);  //!!!
    digitalWrite(oePin, HIGH); //!!!
    digitalWrite(wePin, HIGH); //!!!
}

void setBus(uint16_t address)
{

    GPIOA->ODR = (GPIOA->ODR & 0xFF00) | (address & 0xFF);
    GPIOB->ODR = (GPIOB->ODR & 0xFF) | (address & 0xFF00);
}

void ioWriteReg()
{

    digitalWrite(rsPin, LOW);
    digitalWrite(wePin, LOW);
    digitalWrite(wePin, HIGH);
}

void ioReadReg()
{
}

void ioReadData()
{
}
//==================================================================
uint16_t getscanline(void){

uint16_t dana1, dana2;

    LCD_WriteReg(0x45);
    GPIOA->CRL  = 0x44444444;
    GPIOB->CRH  = 0x44444444;
    wait_us(3);

    digitalWrite(oePin, LOW);
    dana1 = GPIOA->IDR & 0xff;
    digitalWrite(oePin, HIGH);
    dana1 = GPIOA->IDR & 0xff;

    digitalWrite(oePin, LOW);
    dana1 = GPIOA->IDR & 0xff;
    digitalWrite(oePin, HIGH);  
    dana1 = dana1 << 8;

    digitalWrite(oePin, LOW);
    dana2 = GPIOA->IDR & 0xff;
    digitalWrite(oePin, HIGH);  
    dana1 = dana1 | dana2;

    GPIOA->CRL  = 0x33333333;
    GPIOB->CRH  = 0x33333333;
    return dana1;
}
//==================================================================
void wait_us(uint32_t us){
    int32_t start  = DWT->CYCCNT;
    int32_t cycles = us * (72000000 / 1000000);
    while ((int32_t)DWT->CYCCNT - start < cycles);
}
//===================================================================
void Start_DWT(void){
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
//==================================================================
uint32_t LCD_FILL_A_Rectangular(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color)
{
    uint32_t i, i2;
    uint16_t x00, x01, y00, y01;
    uint32_t many_bytes;

    if (x0 < x1)
    {
        x00 = x0;
        x01 = x1;
    }
    else
    {
        x00 = x1;
        x01 = x0;
    }

    if (y0 < y1)
    {
        y00 = y0;
        y01 = y1;
    }
    else
    {
        y00 = y1;
        y01 = y0;
    }

    i = x01 - x00;
    if (i == 0)
    {
        i = 1;
    }
    i2 = y01 - y00;
    if (i2 == 0)
    {
        i2 = 1;
    }

    LCD_OpenWin(x00, y00, x01, y01);

    many_bytes = i * i2;

    FILL_AREA(Color, many_bytes);

    return many_bytes;
}

uint16_t LCD_RandColor(void)
{
    return (uint16_t)rand() & 0xFFFF;
}