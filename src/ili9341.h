#ifndef ILI9341_H_
#define ILI9341_H_

#include "stdint.h"
#include "types_h.h"
typedef struct  
{
    u16  width;          //LCD WIDTH
    u16  height;         //LCD HEIGHT
    u16  id;               //LCD ID
    u8   dir;              //direction： 0，PORTRAIT ；1 LANDSCAPE
    u16  wramcmd;
    u16  setxcmd;
    u16  setycmd;
}_lcd_dev;
extern _lcd_dev lcddev; 
#define LCD_W 240
#define LCD_H 320
#define USE_HORIZONTAL       0
//LCD_REG       (*(volatile uint16_t*)((uint32_t)(0x60000000)))
//LCD_RAM       (*(volatile uint16_t*)((uint32_t)(0x60080000)))

/* Level 1 Commands */
#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_RGBSET              0x2D   /* Color SET */
#define LCD_RAMRD               0x2E   /* Memory Read */
#define LCD_PLTAR               0x30   /* Partial Area */
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */
#define LCD_TEON                0x35   /* Tearing Effect Line ON */
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */
#define LCD_IDMON               0x39   /* Idle Mode ON */
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */

/* Level 2 Commands */
#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define LCD_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define LCD_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define LCD_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define LCD_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define LCD_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_ID4            0xD3   /* Read ID4 */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */




// LEVEL 1 register control
//#define  ILI_NOP             0x00       // No Operation - NOP
#define   ILI_SWRESET         0x01       // Software Reset - SWRESET
//#define  ILI_RDDIDIF         0x04       // Read Display Identification Information (odczytuje dummy byte + 3 bajty informacji)
//#define  ILI_RDDST           0x09       // Read Display Status (odczytuje dummy byte + 4 bajty informacji)
//#define  ILI_RDDPM           0x0A       // Read Display Power Mode (odczytuje dummy byte + 1 bajt informacji)
//#define  ILI_RDDMADCTL       0x0B       // Read Display MADCTL (odczytuje dummy byte + 1 bajt informacji)
//#define  ILI_RDDCOLMOD       0x0C       // Read Display Pixel Format (odczytuje dummy byte + 1 bajt informacji)
//#define  ILI_RDDIM           0x0D       // Read Display Image Format (odczytuje dummy byte + 1 bajt informacji)
//#define  ILI_RDDSM           0x0E       // Read Display Signal Mode (odczytuje dummy byte + 1 bajt informacji)
//#define  ILI_RDDSDR          0x0F       // Read Display SELF-Diagnostic Result (odczytuje dummy byte + 1 bajt informacji)
//#define  ILI_SLPIN           0x10       // Enter Sleep Mode
#define   ILI_SLPOUT          0x11       // Sleep Out
//#define  ILI_PTLON           0x12       // Partial Mode ON
//#define  ILI_NORON           0x13       // Normal Display Mode ON
//#define  ILI_DINVOFF         0x20       // Display Inversion OFF
//#define  ILI_DINVON          0x21       // Display Inversion ON
#define   ILI_GAMSET          0x26       // Gamma Set (1 parametr 8b)
#define   ILI_DISPOFF         0x28       // Display OFF
#define   ILI_DISPON          0x29       // Display ON
#define   ILI_CASET           0x2A       // Column Address Set (4 parametry 8b: SC[15..8], SC[7..0], EC[15..8], EC[7..0])
#define   ILI_PASET           0x2B       // Page (row) Address Set (4 parametry 8b: SC[15..8], SC[7..0], EC[15..8], EC[7..0])
#define   ILI_RAMWR           0x2C       // Memory Write (n parametr�w 18b, wywo�ywana bez parametr�w po CASET i PASET)
//#define  ILI_RGBSET          0x2D       // Color Set (128 parametr�w 8b, 32 dla R, 64 dla G i 32 dla B)
//#define  ILI_RAMRD           0x2E       // Memory Read (n parametr�w 18b)
//#define  ILI_PLTAR           0x30       // Partial Area (4 parametry 8b: SR[15..8], SR[7..0], ER[15..8], ER[7..0])
//#define  ILI_VSCRDEF         0x33       // Vertical Scrolling Definition (6 parametr�w 8b)
//#define  ILI_TEOFF           0x34       // Tearing Effect Line OFF
//#define  ILI_TEON            0x35       // Tearing Effect Line ON (1 parametr 8b)
#define   ILI_MADCTL          0x36       // Memory Access Control (1 parametr 8b)
//#define  ILI_VSCRSADD        0x37       // Vertical Scrolling Start Address (2 parametry 8b)
#define   ILI_IDMOFF          0x38       // Idle Mode OFF
#define   ILI_IDMON           0x39       // Idle Mode ON
#define   ILI_PIXSET          0x3A       // COLMOD: Pixel Format Set (1 parametr 8b)
#define   ILI_RAMWRCont       0x3C       // Write Memory Continue (n parametr�w 18b)
//#define  ILI_RAMRDCont       0x3E       // Read Memory Continue (odczytuje dummy byte i n danych 18b)
//#define  ILI_STS             0x44       // Set Tear Scanline (2 parametry 8b)
//#define  ILI_GS              0x45       // Get Scanline (odczytuje dummy i 2 bajty informacji)
//#define  ILI_WRDISBV         0x51       // Write Display Brightness (1 parametr 8b)
//#define  ILI_RDDISBV         0x52       // Read Display Brightness (odczytuje dummy byte i 1 bajt informacji)
//#define  ILI_WRCTRLD         0x53       // Write CTRL Display (1 parametr 8b)
//#define  ILI_RDCTRLD         0x54       // Read CTRL Display (odczytuje dummy byte i 1 bajt informacji)
//#define  ILI_WRCABC          0x55       // Write Content Adaptive Brightness Control (1 parametr 8b)
//#define  ILI_RDCABC          0x56       // Read Content Adaptive Brightness Control (odczytuje dummy byte i 1 bajt informacji)
//#define  ILI_WRCABCMB        0x5E       // Write CABC Minimum Brightness (1 parametr 8b)
//#define  ILI_RDCABCMB        0x5F       // Read CABC Minimum Brightness (odczytuje dummy byte i 1 bajt informacji)
//#define  ILI_RDID1           0xDA       // Read ID1 (odczytuje dummy byte i 1 bajt informacji)
//#define  ILI_RDID2           0xDB       // Read ID2 (odczytuje dummy byte i 1 bajt informacji)
//#define  ILI_RDID3           0xDC       // Read ID3 (odczytuje dummy byte i 1 bajt informacji)
// LEVEL 2 register control
//#define  ILI_IFMODE          0xB0       // RGB  Interface Signal Control (1 parametr 8b)
#define   ILI_FRMCTR1         0xB1       // Frame Rate Control (In Normal Mode/Full Colors) (2 parametry 8b)
//#define  ILI_FRMCTR2         0xB2       // Frame Rate Control (In Idle Mode/8 Colors) (2 parametry 8b)
//#define  ILI_FRMCTR3         0xB3       // Frame Rate Control (In Partial Mode/Full Colors) (2 parametry 8b)
//#define  ILI_INVTR           0xB4       // Display Inversion Control (1 parametr 8b)
//#define  ILI_PRCTR           0xB5       // Blanking Porch Control (4 parametry 8b)
#define   ILI_DISCTRL         0xB6       // Display Function Control (4 parametry 8b)
//#define  ILI_ETMOD           0xB7       // Entry Mode Set (1 parametr 8b)
//#define  ILI_BLCTRL1         0xB8       // Backlight Control 1 (1 parametr 8b)
//#define  ILI_BLCTRL2         0xB9       // Backlight Control 2 (1 parametr 8b)
//#define  ILI_BLCTRL3         0xBA       // Backlight Control 3 (1 parametr 8b)
//#define  ILI_BLCTRL4         0xBB       // Backlight Control 4 (1 parametr 8b)
//#define  ILI_BLCTRL5         0xBC       // Backlight Control 5 (1 parametr 8b)
//#define  ILI_BLCTRL7         0xBE       // Backlight Control 7 (1 parametr 8b)
//#define  ILI_BLCTRL8         0xBF       // Backlight Control 8 (1 parametr 8b)
#define   ILI_PWCTRL1         0xC0       // Power Control 1 (1 parametr 8b)
#define   ILI_PWCTRL2         0xC1       // Power Control 2 (1 parametr 8b)
#define   ILI_VMCTRL1         0xC5       // VCOM Control 1 (2 parametry 8b)
#define   ILI_VMCTRL2         0xC7       // VCOM Control 2 (1 parametr 8b)
//#define  ILI_NVMWR           0xD0       // NV Memory Write (2 parametry 8b)
//#define  ILI_NVMPKEY         0xD1       // NV Memory Protection Key (3 parametry 8b)
//#define  ILI_RDNVM           0xD2       // NV Memory Status Read (odczyt dummy byte i 2 bajty informacji)
//#define  ILI_RDID4           0xD3       // Read ID4 (odczytuje dummy byte i 3 bajty informacji)
#define   ILI_PGAMCTRL        0xE0       // Positive Gamma Correction (15 parametr�w 8b)
#define   ILI_NGAMCTRL        0xE1       // Negative Gamma Correction (15 parametr�w 8b)
//#define  ILI_DGAMCTRL1       0xE2       // Digital Gamma Control 1 (16 parametr�w 8b)
//#define  ILI_DGAMCTRL2       0xE3       // Digital Gamma Control 2 (16 parametr�w 8b)
//#define  ILI_IFCTL           0xF6       // Interface Control (3 parametry 8b)
// EXTEND register control
#define   ILI_PCA             0xCB       // Power Control A (5 parametr�w 8b)
#define   ILI_PCB             0xCF       // Power Control B (3 parametry 8b)
#define   ILI_DTCA_ic         0xE8       // Driver Timming Control A (3 parametry 8b) - for internal clock
//#define  ILI_DTCA_ec         0xE9       // Driver Timming Control A (3 parametry 8b) - for external clock
#define   ILI_DTCB            0xEA       // Driver Timming Control B (2 parametry 8b)
#define   ILI_POSC            0xED       // Power On Sequence Control (4 parametry 8b)
#define   ILI_E3G             0xF2       // Enable 3G (1 parametr 8b)
#define   ILI_PRC             0xF7       // Pump Ratio Control (1 parametr 8b)

//------------------------------------

//------------------------------------
// color value

/* Colors for display */
#define COLOR_565_ALICEBLUE 				0xF7DF
#define COLOR_565_ANTIQUEWHITE 				0xFF5A
#define COLOR_565_AQUA 						0x07FF
#define COLOR_565_AQUAMARINE 				0x7FFA
#define COLOR_565_AZURE 					0xF7FF
#define COLOR_565_BEIGE 					0xF7BB
#define COLOR_565_BISQUE 					0xFF38
#define COLOR_565_BLACK 					0x0000
#define COLOR_565_BLANCHEDALMOND 			0xFF59
#define COLOR_565_BLUE 						0x001F
#define COLOR_565_BLUEVIOLET 				0x895C
#define COLOR_565_BROWN 					0xA145
#define COLOR_565_BURLYWOOD 				0xDDD0
#define COLOR_565_CADETBLUE 				0x5CF4
#define COLOR_565_CHARTREUSE 				0x7FE0
#define COLOR_565_CHOCOLATE 				0xD343
#define COLOR_565_CORAL 					0xFBEA
#define COLOR_565_CORNFLOWERBLUE 			0x64BD
#define COLOR_565_CORNSILK 					0xFFDB
#define COLOR_565_CRIMSON 					0xD8A7
#define COLOR_565_CYAN 						0x07FF
#define COLOR_565_DARKBLUE 					0x0011
#define COLOR_565_DARKCYAN 					0x0451
#define COLOR_565_DARKGOLDENROD 			0xBC21
#define COLOR_565_DARKGRAY 					0xAD55
#define COLOR_565_DARKGREEN 				0x0320
#define COLOR_565_DARKKHAKI 				0xBDAD
#define COLOR_565_DARKMAGENTA 				0x8811
#define COLOR_565_DARKOLIVEGREEN 			0x5345
#define COLOR_565_DARKORANGE 				0xFC60
#define COLOR_565_DARKORCHID 				0x9999
#define COLOR_565_DARKRED 					0x8800
#define COLOR_565_DARKSALMON 				0xECAF
#define COLOR_565_DARKSEAGREEN 				0x8DF1
#define COLOR_565_DARKSLATEBLUE 			0x49F1
#define COLOR_565_DARKSLATEGRAY 			0x2A69
#define COLOR_565_DARKTURQUOISE 			0x067A
#define COLOR_565_DARKVIOLET 				0x901A
#define COLOR_565_DEEPPINK 					0xF8B2
#define COLOR_565_DEEPSKYBLUE 				0x05FF
#define COLOR_565_DIMGRAY 					0x6B4D
#define COLOR_565_DODGERBLUE 				0x1C9F
#define COLOR_565_FIREBRICK 				0xB104
#define COLOR_565_FLORALWHITE 				0xFFDE
#define COLOR_565_FORESTGREEN 				0x2444
#define COLOR_565_FUCHSIA 					0xF81F
#define COLOR_565_GAINSBORO 				0xDEFB
#define COLOR_565_GHOSTWHITE 				0xFFDF
#define COLOR_565_GOLD 						0xFEA0
#define COLOR_565_GOLDENROD 				0xDD24
#define COLOR_565_GRAY 						0x8410
#define COLOR_565_GREEN 					0x0400
#define COLOR_565_GREENYELLOW 				0xAFE5
#define COLOR_565_HONEYDEW 					0xF7FE
#define COLOR_565_HOTPINK 					0xFB56
#define COLOR_565_INDIANRED 				0xCAEB
#define COLOR_565_INDIGO 					0x4810
#define COLOR_565_IVORY 					0xFFFE
#define COLOR_565_KHAKI 					0xF731
#define COLOR_565_LAVENDER 					0xE73F
#define COLOR_565_LAVENDERBLUSH 			0xFF9E
#define COLOR_565_LAWNGREEN 				0x7FE0
#define COLOR_565_LEMONCHIFFON 				0xFFD9
#define COLOR_565_LIGHTBLUE 				0xAEDC
#define COLOR_565_LIGHTCORAL 				0xF410
#define COLOR_565_LIGHTCYAN 				0xE7FF
#define COLOR_565_LIGHTGREEN 				0x9772
#define COLOR_565_LIGHTGREY 				0xD69A
#define COLOR_565_LIGHTPINK 				0xFDB8
#define COLOR_565_LIGHTSALMON 				0xFD0F
#define COLOR_565_LIGHTSEAGREEN 			0x2595
#define COLOR_565_LIGHTSKYBLUE 				0x867F
#define COLOR_565_LIGHTSLATEGRAY 			0x7453
#define COLOR_565_LIGHTSTEELBLUE 			0xB63B
#define COLOR_565_LIGHTYELLOW 				0xFFFC
#define COLOR_565_LIME 						0x07E0
#define COLOR_565_LIMEGREEN 				0x3666
#define COLOR_565_LINEN 					0xFF9C
#define COLOR_565_MAGENTA 					0xF81F
#define COLOR_565_MAROON 					0x8000
#define COLOR_565_MEDIUMAQUAMARINE 			0x6675
#define COLOR_565_MEDIUMBLUE 				0x0019
#define COLOR_565_MEDIUMORCHID 				0xBABA
#define COLOR_565_MEDIUMPURPLE 				0x939B
#define COLOR_565_MEDIUMSEAGREEN 			0x3D8E
#define COLOR_565_MEDIUMSLATEBLUE 			0x7B5D
#define COLOR_565_MEDIUMSPRINGGREEN			0x07D3
#define COLOR_565_MEDIUMTURQUOISE 			0x4E99
#define COLOR_565_MEDIUMVIOLETRED 			0xC0B0
#define COLOR_565_MIDNIGHTBLUE 				0x18CE
#define COLOR_565_MINTCREAM 				0xF7FF
#define COLOR_565_MISTYROSE 				0xFF3C
#define COLOR_565_MOCCASIN 					0xFF36
#define COLOR_565_NAVAJOWHITE 				0xFEF5
#define COLOR_565_NAVY 						0x0010
#define COLOR_565_OLDLACE 					0xFFBC
#define COLOR_565_OLIVE 					0x8400
#define COLOR_565_OLIVEDRAB 				0x6C64
#define COLOR_565_ORANGE 					0xFD20
#define COLOR_565_ORANGERED 				0xFA20
#define COLOR_565_ORCHID 					0xDB9A
#define COLOR_565_PALEGOLDENROD 			0xEF55
#define COLOR_565_PALEGREEN 				0x9FD3
#define COLOR_565_PALETURQUOISE 			0xAF7D
#define COLOR_565_PALEVIOLETRED 			0xDB92
#define COLOR_565_PAPAYAWHIP 				0xFF7A
#define COLOR_565_PEACHPUFF 				0xFED7
#define COLOR_565_PERU 						0xCC27
#define COLOR_565_PINK 						0xFE19
#define COLOR_565_PLUM 						0xDD1B
#define COLOR_565_POWDERBLUE 				0xB71C
#define COLOR_565_PURPLE 					0x8010
#define COLOR_565_RED 						0xF800
#define COLOR_565_ROSYBROWN 				0xBC71
#define COLOR_565_ROYALBLUE 				0x435C
#define COLOR_565_SADDLEBROWN 				0x8A22
#define COLOR_565_SALMON 					0xFC0E
#define COLOR_565_SANDYBROWN 				0xF52C
#define COLOR_565_SEAGREEN 					0x2C4A
#define COLOR_565_SEASHELL 					0xFFBD
#define COLOR_565_SIENNA 					0xA285
#define COLOR_565_SILVER					0xC618
#define COLOR_565_SKYBLUE 					0x867D
#define COLOR_565_SLATEBLUE 				0x6AD9
#define COLOR_565_SLATEGRAY 				0x7412
#define COLOR_565_SNOW 						0xFFDF
#define COLOR_565_SPRINGGREEN 				0x07EF
#define COLOR_565_STEELBLUE 				0x4416
#define COLOR_565_TAN 						0xD5B1
#define COLOR_565_TEAL 						0x0410
#define COLOR_565_THISTLE 					0xDDFB
#define COLOR_565_TOMATO 					0xFB08
#define COLOR_565_TURQUOISE 				0x471A
#define COLOR_565_VIOLET 					0xEC1D
#define COLOR_565_WHEAT 					0xF6F6
#define COLOR_565_WHITE 					0xFFFF
#define COLOR_565_WHITESMOKE 				0xF7BE
#define COLOR_565_YELLOW 					0xFFE0
#define COLOR_565_YELLOWGREEN 				0x9E66
#define LCD_ROW_NUM    320                // Number of rows
#define LCD_COL_NUM    240                // Number of columns
#define SCREEN_PIXELS       (LCD_ROW_NUM * LCD_COL_NUM)
#define csPin PB6
#define rsPin PB5
#define wePin PB4
#define oePin PB3

#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0XF81F
#define GRED                0XFFE0
#define GBLUE               0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN           0XBC40 //棕色
#define BRRED           0XFC07 //棕红色
#define GRAY            0X8430 //灰色
//GUI颜色

#define DARKBLUE         0X01CF //深蓝色
#define LIGHTBLUE        0X7D7C //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色
 
#define LIGHTGREEN      0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY                   0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE       0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

//#define LCD_REG       (*(volatile uint16_t*)((uint32_t)(0x60000000)))
//#define LCD_RAM       (*(volatile uint16_t*)((uint32_t)(0x60080000)))

#define swap(a,b) {uint16_t t=a;a=b;b=t;}


extern void LCD_WriteReg(uint16_t data);
extern void LCD_WriteData(uint16_t data);
extern void FILL_AREA(uint16_t color, uint32_t many_bytes);

uint32_t LCD_FILL_A_Rectangular(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color);

void LCD_initIO();
void setBus(uint16_t address);

void ioReadData();
 
void ioReadReg();
void LCD_ILI9341_init(void);

void LCD_OpenWin(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void LCD_ClrScr(uint16_t BackColor);

void LCD_DisALoop(uint16_t x0, uint16_t y0, uint8_t r, uint16_t Color);
void LCD_DisAPoint(uint16_t x0, uint16_t y0, uint16_t Color);
void LCD_DisASquare(uint16_t x0, uint16_t y0, uint16_t wide, uint16_t Color);
void LCD_DisARectangular(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color);
void LCD_DrawLine(uint16_t color, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_No_Fill_Draw(uint16_t color, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color);
void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void Start_DWT(void);
void wait_us(uint32_t us);
uint16_t getscanline(void);
//-------------------------------
uint16_t LCD_RandColor(void);
//-------------------------------
#endif /* ILI9341_H_ */


