/*
 * demos.c
 *
 *  Created on: 03.10.2019
 *      Author: bolo
 */

//-------------------------
#include <Arduino.h>
#include "demos.h"

//-------------------------
extern u16 getscanline(void);
extern void Put_Pixel(uint16_t  plot_X, uint16_t  plot_Y, uint16_t color );
//-------------------------
#define sq_size 100
#define rect_size 100
#define t_wait 2
#define __IO volatile

static void half_sec_delay(void);
static void wait_t(void);

static void demo_01(void);
static void demo_02(void);
static void demo_03(void);
static void demo_04(void);
static void demo_05(void);
static void demo_06(void);
static void demo_07(void);
static void demo_08(void);
static void demo_09(void);
static void demo_10(void);
 
static void demo_12(void);
static void demo_13(void);

static void demo_77(void);
static void LCD_DisACirc(uint16_t x0, uint16_t y0, uint8_t r, uint16_t Color);
static void LCD_DisACirc2(uint16_t x0, uint16_t y0, uint8_t r, uint16_t Color);
//--------------------------------------------------------

//-------------------------
__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
    micros *= (72000000 / 1000000) / 5;
    while (micros--)
        ;
}
//-------------------------
void start_demos(void)
{
    // LCD_ClrScr(COLOR_565_BLACK);

    demo_01();
    demo_02();
    demo_03();
    demo_04();
    demo_05();
    demo_06();
    demo_07();
    demo_08();
    demo_09();
    demo_10();

    demo_12();
    demo_13();

    LCD_ClrScr(COLOR_565_BLACK);

    half_sec_delay();
}
//------------------------------

//=======================================================
void demo_13(void)
{
    LCD_ClrScr(COLOR_565_BLUE);
    HAL_Delay(1000);
    LCD_ClrScr(0);
}
void demo_12(void)
{
    u16 color = COLOR_565_BLUE;
    u16 x0, y0;
    u8 movetype = 0; // x++ y++
    u32 counter = 0;

    u8 half_circle = rect_size >> 1;

    x0 = half_circle;
    y0 = half_circle;

    LCD_ClrScr(COLOR_565_BLACK);
    fillCircle(x0, y0, half_circle, color);

    while (counter < 1000)
    {
        //-----------
        if (movetype == 0)
        {
            if (x0 < LCD_ROW_NUM - half_circle)
            {
                if (y0 < LCD_COL_NUM - half_circle)
                {
                    LCD_DisALoop(x0, y0, half_circle + 2, 0);
                    LCD_DisALoop(x0, y0, half_circle + 1, 0);
                    LCD_DisALoop(x0, y0, half_circle + 3, 0);
                    x0++;
                    y0++;
                    fillCircle(x0, y0, half_circle, color);

                    // wait_t();
                }
                else
                {
                    movetype = 1; // x++ y--
                }
            }
            else
            {
                movetype = 3; //
            }
        }
        //--------------
        if (movetype == 1)
        {
            if (x0 < LCD_ROW_NUM - half_circle)
            {
                if (y0 > half_circle)
                {
                    LCD_DisALoop(x0, y0, half_circle + 2, 0);
                    LCD_DisALoop(x0, y0, half_circle + 1, 0);
                    LCD_DisALoop(x0, y0, half_circle + 3, 0);
                    x0++;
                    y0--;
                    fillCircle(x0, y0, half_circle, color);

                    // wait_t();
                }
                else
                {
                    movetype = 0; //
                }
            }
            else
            {
                movetype = 2; // x-- y--
            }
        }
        //--------------
        if (movetype == 2)
        {
            if (x0 > half_circle)
            {
                if (y0 > half_circle)
                {
                    LCD_DisALoop(x0, y0, half_circle + 2, 0);
                    LCD_DisALoop(x0, y0, half_circle + 1, 0);
                    LCD_DisALoop(x0, y0, half_circle + 3, 0);

                    x0--;
                    y0--;
                    fillCircle(x0, y0, half_circle, color);
                    // wait_t();
                }
                else
                {
                    movetype = 3; // x-- y++
                }
            }
            else
            {
                movetype = 1; //
            }
        }
        //--------------
        if (movetype == 3)
        {
            if (x0 > half_circle)
            {
                if (y0 < LCD_COL_NUM - half_circle)
                {
                    LCD_DisALoop(x0, y0, half_circle + 2, 0);
                    LCD_DisALoop(x0, y0, half_circle + 1, 0);
                    LCD_DisALoop(x0, y0, half_circle + 3, 0);
                    x0--;
                    y0++;
                    fillCircle(x0, y0, half_circle, color);
                    // wait_t();
                }
                else
                {
                    movetype = 2;
                }
            }
            else
            {
                movetype = 0; // x-- y--
            }
        }
        //--------------

        counter++;

    } // while(counter < 2000)
    HAL_Delay(1000);
}
//------------------------------

//------------------------------
void demo_10(void)
{
    u16 i;
    LCD_ClrScr(COLOR_565_BLACK);
    // fillCircle(160,120,110,0xf800);
    for (i = 0; i < 2500; i++)
    {
        fillCircle((uint16_t)rand() % 220 + 50,
                   (uint16_t)rand() % 140 + 50,
                   (uint16_t)rand() % 50,
                   (uint16_t)rand() & 0xFFFF);
    }
    HAL_Delay(1000);
}
//------------------------------
void demo_09(void)
{
    u16 x0, y0, x1, y1, color, i;

    LCD_ClrScr(COLOR_565_BLACK);

    for (i = 0; i < 100; i++)
    {
        color = LCD_RandColor();
        x0 = (uint16_t)rand() % LCD_ROW_NUM;
        x1 = (uint16_t)rand() % LCD_ROW_NUM;
        y0 = (uint16_t)rand() % LCD_COL_NUM;
        y1 = (uint16_t)rand() % LCD_COL_NUM;

        LCD_No_Fill_Draw(color, x0, y0, x1, y1);
        HAL_Delay(10);
    }
    HAL_Delay(1000);
}
//------------------------------
void demo_08(void)
{

    LCD_ClrScr(COLOR_565_BLACK);
    int16_t x0, y0, x1, y1;
    x0 = 0;
    y0 = 0;
    x1 = 4;
    y1 = 239;

    while (y0 < 239)
    {
        LCD_DrawLine(COLOR_565_BLUE, x0, y0, x1, y1);
        y0 = y0 + 6;
        x1 = x1 + 8;
        HAL_Delay(10);
    }

    x0 = 319;
    y0 = 239;
    x1 = 315;
    y1 = 0;

    while (y0 > 0)
    {
        LCD_DrawLine(COLOR_565_BLUE, x0, y0, x1, y1);
        y0 = y0 - 6;
        x1 = x1 - 8;
        HAL_Delay(10);
    }

    x0 = 0;
    y0 = 239;
    x1 = 4;
    y1 = 0;

    while (y0 > 0)
    {
        LCD_DrawLine(COLOR_565_RED, x0, y0, x1, y1);
        y0 = y0 - 6;
        x1 = x1 + 8;
        HAL_Delay(10);
    }

    x0 = 319;
    y0 = 0;
    x1 = 315;
    y1 = 239;

    while (y0 < 239)
    {
        LCD_DrawLine(COLOR_565_RED, x0, y0, x1, y1);
        y0 = y0 + 6;
        x1 = x1 - 8;
        HAL_Delay(10);
    }

    HAL_Delay(1000);
}
//------------------------------
void demo_07(void)
{
    u16 color = COLOR_565_RED;
    u16 x0, y0, x1, y1;
    u8 movetype = 0; // x++ y++
    u16 counter = 0;
    x0 = 0;
    x1 = x0 + sq_size;
    y0 = 0;
    y1 = y0 + sq_size;

    LCD_ClrScr(COLOR_565_BLACK);
    LCD_DisARectangular(x0, y0, x1, y1, color);

    while (counter < 1000)
    {
        //-----------
        if (movetype == 0)
        {
            if (x0 < LCD_ROW_NUM - sq_size)
            {
                if (y0 < LCD_COL_NUM - sq_size)
                {
                    LCD_DrawLine(0, x0, y0, x1, y0); // gorna
                    LCD_DrawLine(0, x0, y0, x0, y1); // prawa
                    x0++;
                    x1++;
                    y0++;
                    y1++;
                    LCD_DrawLine(color, x0, y1, x1, y1); // dolna
                    LCD_DrawLine(color, x1, y0, x1, y1); // lewa
                    wait_t();
                }
                else
                {
                    movetype = 1; // x++ y--
                }
            }
            else
            {
                movetype = 3; //
            }
        }
        //--------------
        if (movetype == 1)
        {
            if (x0 < LCD_ROW_NUM - sq_size)
            {
                if (y0 > 0)
                {
                    LCD_DrawLine(0, x0, y0, x0, y1); // prawa
                    LCD_DrawLine(0, x0, y1, x1, y1); // dolna
                    x0++;
                    x1++;
                    y0--;
                    y1--;
                    LCD_DrawLine(color, x1, y0, x1, y1); // lewa
                    LCD_DrawLine(color, x0, y0, x1, y0); // gorna

                    wait_t();
                }
                else
                {
                    movetype = 0; //
                }
            }
            else
            {
                movetype = 2; // x-- y--
            }
        }
        //--------------
        if (movetype == 2)
        {
            if (x0 > 0)
            {
                if (y0 > 0)
                {
                    LCD_DrawLine(0, x0, y1, x1, y1); // dolna
                    LCD_DrawLine(0, x1, y0, x1, y1); // lewa
                    x0--;
                    x1--;
                    y0--;
                    y1--;
                    LCD_DrawLine(color, x0, y0, x1, y0); // gorna
                    LCD_DrawLine(color, x0, y0, x0, y1); // prawa
                    wait_t();
                }
                else
                {
                    movetype = 3; // x-- y++
                }
            }
            else
            {
                movetype = 1; //
            }
        }
        //--------------
        if (movetype == 3)
        {
            if (x0 > 0)
            {
                if (y0 < LCD_COL_NUM - sq_size)
                {
                    LCD_DrawLine(0, x0, y0, x1, y0); // gorna
                    LCD_DrawLine(0, x1, y0, x1, y1); // lewa
                    x0--;
                    x1--;
                    y0++;
                    y1++;
                    LCD_DrawLine(color, x0, y1, x1, y1); // dolna
                    LCD_DrawLine(color, x0, y0, x0, y1); // prawa
                    wait_t();
                }
                else
                {
                    movetype = 2;
                }
            }
            else
            {
                movetype = 0; // x-- y--
            }
        }
        //--------------

        counter++;

    } // while(counter < 2000)
}
//------------------------------
void demo_06(void)
{
    u16 x0, y0, x1, y1, color, i;

    for (i = 0; i < 2000; i++)
    {
        color = LCD_RandColor();
        x0 = (uint16_t)rand() % LCD_ROW_NUM;
        x1 = (uint16_t)rand() % LCD_ROW_NUM;
        y0 = (uint16_t)rand() % LCD_COL_NUM;
        y1 = (uint16_t)rand() % LCD_COL_NUM;

        LCD_FILL_A_Rectangular(x0, y0, x1, y1, color);
    }
    half_sec_delay();
}
//------------------------------
void demo_05(void)
{
    u16 i, color;
    u16 x0, y0, x1, y1;

    LCD_ClrScr(COLOR_565_BLACK);

    for (i = 0; i < LCD_COL_NUM; i++)
    {
        LCD_DrawLine(LCD_RandColor(), 0, i, LCD_ROW_NUM - 1, i);
    }
    half_sec_delay();
    for (i = 0; i < LCD_ROW_NUM; i++)
    {
        LCD_DrawLine(LCD_RandColor(), i, 0, i, LCD_COL_NUM - 1);
    }
    half_sec_delay();

    x0 = 0;
    x1 = LCD_ROW_NUM - 1;
    y0 = 0;
    y1 = LCD_COL_NUM - 1;

    for (i = 0; i < LCD_COL_NUM / 2; i++)
    {
        color = LCD_RandColor();
        LCD_No_Fill_Draw(color, x0, y0, x1, y1);
        x0++;
        x1--;
        y0++;
        y1--;
    }
    half_sec_delay();
    LCD_ClrScr(COLOR_565_BLACK);

    LCD_ClrScr(COLOR_565_BLACK);
}
//------------------------------
void demo_04(void)
{
    u32 i;
    LCD_ClrScr(COLOR_565_BLACK);

    for (i = 0; i < 1500; i++)
    {
        LCD_DisALoop((uint16_t)rand() % 280 + 20,
                     (uint16_t)rand() % 200 + 20,
                     (uint16_t)rand() % 20,
                     LCD_RandColor());
        HAL_Delay(1);
    }
    half_sec_delay();
    LCD_ClrScr(COLOR_565_BLACK);
}
//------------------------------
void demo_03(void)
{
    u32 i;
    LCD_ClrScr(COLOR_565_BLACK);

    for (i = 0; i < 1000; i++)
    {
        LCD_DrawLine(LCD_RandColor(), (uint16_t)rand() % LCD_ROW_NUM,
                     (uint16_t)rand() % LCD_COL_NUM, (uint16_t)rand() % LCD_ROW_NUM,
                     (uint16_t)rand() % LCD_COL_NUM);
        HAL_Delay(1);
    }
    half_sec_delay();
    LCD_ClrScr(COLOR_565_BLACK);
}
//------------------------------
void demo_02(void)
{
    u32 i;
    LCD_ClrScr(COLOR_565_BLACK);
    for (i = 0; i < 15000; i++)
    {
        Put_Pixel((uint16_t)rand() % LCD_ROW_NUM,
                      (uint16_t)rand() % LCD_COL_NUM,
                      (uint16_t)rand() % 0xffff);
        wait_us(100);
    }
    half_sec_delay();
    LCD_ClrScr(COLOR_565_BLACK);
}
//------------------------------
void demo_01(void)
{
    LCD_ClrScr(COLOR_565_RED);
    HAL_Delay(1000);
}
//-----------------------------------
void half_sec_delay(void)
{
    HAL_Delay(500);
}
//----------
void wait_t(void)
{
    HAL_Delay(t_wait);
}
//-----------------------------------

//-----------------------------------