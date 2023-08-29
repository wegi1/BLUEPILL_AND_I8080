/*
 * GUI.h
 *
 *  Created on: Jun 22, 2023
 *      Author: BOLO
 */

#ifndef GUI_H_
#define GUI_H_

#include "types_h.h"
#include "fonts.h"

//*********************************

typedef struct
{
  uint32_t  TextColor;
  uint32_t  BackColor;
  sFONT     *pFont;
}LCD_DrawPropTypeDef;

//***************************************************

//************************************************

void TFT9341_FontsIni(void);
void Draw_Char(u16 x, u16 y, char s);
void move_cursor_x(void);
void move_cursor_y(void);

int LCD_Printchar(char s);
void clear_cursor(void);
void set_cursor(u16 x, u16 y);
void center_line_print(char* buffor);
void center_screen(u16 x_many_char, u16 y_many_char);
void center_x(u16 many_char);
void center_y(u16 many_char);
void lcd_print_buffor(char * buffor);

void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

void GUI_DrawPoint(u16 x,u16 y,u16 color);


void LCD_ShowString(u16 x,u16 y,u8 size,char *p);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 size);
void LCD_PrintNum( u32 num);
 

void LCD_direction(u8 direction);
void welcome_banner(void);
//****************************************************
#endif /* GUI_H_ */
