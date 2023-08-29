/*
 * GUI.c
 *
 *  Created on: Jun 22, 2023
 *      Author: BOLO
 */

//****************************************************
#include "GUI.h"
#include "ili9341.h"
#include <stdio.h>
//******************************************************
extern int my_utoa(char* buffer, uint32_t data);
u16 CURSOR_X = 0;
u16 CURSOR_Y = 0;
char num_buff[14] = {0};


//*********************************************************
LCD_DrawPropTypeDef lcdprop;
//*********************************************************

//*********************************************************

//*********************************************************
void center_line_print(char* buffor){
    u32 i=0;
    while(buffor[i] != 0){
        i++;
    }
    center_x(i);
    lcd_print_buffor(buffor);
}
//*********************************************************
void lcd_print_buffor(char * buffor){
    u32 i;
    i = 0;
    while(buffor[i] != 0){
        LCD_Printchar(buffor[i]);
        i++;
    }
}
void center_screen(u16 x_many_char, u16 y_many_char){
    center_x(x_many_char);
    center_y(y_many_char);
}
void center_x(u16 many_char){
    if(many_char * lcdprop.pFont->Width >= lcddev.width) {many_char=0;}
    CURSOR_X = (u16) (lcddev.width >> 1) -  ((many_char * lcdprop.pFont->Width) >> 1);
}
void center_y(u16 many_char){
    if(many_char * lcdprop.pFont->Height >= lcddev.height) {many_char=1;}
    CURSOR_Y = (u16) (lcddev.height >> 1)-((many_char * lcdprop.pFont->Height) >> 1);
}
//*******************************************************
void LCD_PrintNum( u32 num){
    my_utoa((char *)&num_buff,  num);
    lcd_print_buffor(num_buff);
}
//*******************************************************
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 size){

    my_utoa(num_buff,  num);
    set_cursor(x, y);

    lcdprop.pFont  = &Font20;

    lcd_print_buffor(num_buff);
}
//*******************************************************
void LCD_ShowString(u16 x,u16 y,u8 size,char *p){
    set_cursor(x, y);

    lcdprop.pFont  = &Font20;
    lcd_print_buffor(p);
}

/*******************************************************************
 * @name       :void GUI_DrawPoint(u16 x,u16 y,u16 color)
 * @date       :2018-08-09
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
                y:the y coordinate of the point
                                color:the color value of the point
 * @retvalue   :None
********************************************************************/
void GUI_DrawPoint(u16 x,u16 y,u16 color)
{
    LCD_OpenWin(x,y,x,y);
    LCD_WriteData(color);
}


//*******************************************************
void clear_cursor(void){
    CURSOR_X = 0;
    CURSOR_Y = 0;
}
//*******************************************************
void set_cursor(u16 x, u16 y){

    if(x >= lcddev.width){
        x = 0;
    }
    if(y >= lcddev.height){
        y = 0;
        x = 0;
    }
    CURSOR_X = x;
    CURSOR_Y = y;
}
//********************************************************************************************************************
int LCD_Printchar(char s){

    u32 i;

    if(CURSOR_X + lcdprop.pFont->Width > lcddev.width) {
        CURSOR_X = 0;
        CURSOR_Y += lcdprop.pFont->Height;
    }
    if(CURSOR_Y + lcdprop.pFont->Height > lcddev.height){
        CURSOR_Y = 0;
        CURSOR_X = 0;
    }
    if (s == '\n')
    {
        move_cursor_y();
        CURSOR_X = 0;
        return 0;
    }
    if (s == '\r')
    {
        CURSOR_X = 0;
        return 0;
    }
    else if (s == '\t')
    {
        for(i=0; i<4; i++){
            move_cursor_x();
            return 0;
        }
    } else {
        Draw_Char(CURSOR_X, CURSOR_Y, s);
        move_cursor_x();
    }
    return 0;
}
//**********************************************************
void move_cursor_y(void){
    CURSOR_Y += lcdprop.pFont->Height;
    if(CURSOR_Y + lcdprop.pFont->Height > lcddev.height){
        CURSOR_Y = 0;
        CURSOR_X = 0;
    }
}
//**********************************************************
void move_cursor_x(void){
    CURSOR_X +=lcdprop.pFont->Width;
    if(CURSOR_X > lcddev.width) {
        CURSOR_X = 0;
        move_cursor_y();
    }
}
//**********************************************************
void Draw_Char(u16 x, u16 y, char s){
    u32 i, i2, i3;
    u16 width, height;
    u32 fontsize = 0;
    u32 fontoffset;
    u32 b_width;
    u16 font_color, back_color;
    u8  font_byte;

    u8* pFont_ADDR;

    width   = lcdprop.pFont->Width;
    height  = lcdprop.pFont->Height;
    b_width = (width / 8) + 1;

    font_color = lcdprop.TextColor;
    back_color = lcdprop.BackColor;


        fontsize = 40;


    fontoffset = ((s - 32) * fontsize);
    pFont_ADDR = (u8*) (fontoffset + (u32) lcdprop.pFont->table);


    if(x+width >= lcddev.width){
        x = 0;
        y = y + height;
    }
    if(y+height >= lcddev.height){
        y = 0;
        x = 0;
    }

    LCD_SetWindows(x,y, x+width-1, y+height-1);
    // LCD_OpenWin(x,y, x+width-1, y+height-1);
    // LCD_OpenWin(x,y, x+19, y+13); //!!!

    for(i=0; i<height;i++){
            font_byte =  pFont_ADDR[0];
            for(i3=0; i3<8; i3++){
                if(font_byte > 127){
                    LCD_WriteData(font_color);
                } else {
                    LCD_WriteData(back_color);
                }
                font_byte = font_byte << 1;
            }
            font_byte = pFont_ADDR[1];
            for(i3=0; i3<6; i3++){
                if(font_byte > 127){
                    LCD_WriteData(font_color);
                } else {
                    LCD_WriteData(back_color);
                }
                font_byte = font_byte << 1;
            }
            pFont_ADDR+=2;
        }
    
}
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
                                yStar:the bebinning y coordinate of the LCD display window
                                xEnd:the endning x coordinate of the LCD display window
                                yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
 ******************************************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
    LCD_WriteReg(lcddev.setxcmd);
    LCD_WriteData(xStar>>8);
    LCD_WriteData(xStar);
    LCD_WriteData(xEnd>>8);
    LCD_WriteData(xEnd);

    LCD_WriteReg(lcddev.setycmd);
    LCD_WriteData(yStar>>8);
    LCD_WriteData(yStar);
    LCD_WriteData(yEnd>>8);
    LCD_WriteData(yEnd);

    LCD_WriteReg(lcddev.wramcmd); //开始写入GRAM
}   
/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
                                                    2-180 degree
                                                    3-270 degree
 * @retvalue   :None
 ******************************************************************************/
void LCD_direction(u8 direction)
{ 
    lcddev.setxcmd=0x2A;
    lcddev.setycmd=0x2B;
    lcddev.wramcmd=0x2C;
    switch(direction){
    case 0:
        lcddev.dir = direction;
        lcddev.width=LCD_W;
        lcddev.height=LCD_H;
        LCD_WriteReg(0x36);
        LCD_WriteData((1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
        break;
    case 1:
        lcddev.dir = direction;
        lcddev.width=LCD_H;
        lcddev.height=LCD_W;
        LCD_WriteReg(0x36);
        LCD_WriteData((1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
        break;
    case 2:
        lcddev.width=LCD_W;
        lcddev.height=LCD_H;
        lcddev.dir = direction;
        LCD_WriteReg(0x36);
        LCD_WriteData((1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
        break;
    case 3:
        lcddev.width=LCD_H;
        lcddev.height=LCD_W;
        lcddev.dir = direction;
        LCD_WriteReg(0x36);
        LCD_WriteData((1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
        break;
    default:break;
    }
}
//-------------------------------------------------------------------
void welcome_banner(void){
     LCD_ClrScr(BLACK);
    clear_cursor(); 
    center_line_print("STM32F103C8T6");
    CURSOR_Y += 30;
    center_line_print("SOMETIMES...");
    lcd_print_buffor("\n");
    center_line_print("CALLED AS:");
    CURSOR_Y += 30;

    LCD_DisARectangular(74, 0, 106, 239, RED);
    center_line_print("FAMOUST BLUEPILL");
    CURSOR_Y += 15;
    lcd_print_buffor(" SMALL BENCHMARK");
    CURSOR_Y += 6;

    lcd_print_buffor("\nPARAMETERS:\n");
    lcd_print_buffor("ARM32 @72MHz\n");
    lcd_print_buffor("20K RAM 64K FLASH");
    lcd_print_buffor("ILI9341 320*200\n");
    CURSOR_Y += 10;
    lcd_print_buffor("512 VECTORDOTS\n");
    CURSOR_Y += 15;
    lcd_print_buffor("LCD INTERFACE:\n");
    CURSOR_Y += 10;
    center_line_print("16BIT Intel 8080");
}
//*******************************************************
void TFT9341_FontsIni(void)
{
 
    Font20.Height=20;
    Font20.Width=14;
    lcdprop.BackColor=BLACK;
    lcdprop.TextColor=YELLOW;
    lcdprop.pFont=&Font20;
}
//**********************************************************
