#include <Arduino.h>
#include <stdlib.h>
#include "ili9341.h"
#include "demos.h"
#include "GUI.h"
#include "_F103_VECTORDOTS_LIB.h" 
//==================================================
void setup() {
    Start_DWT();
    srand(DWT->CYCCNT);
    LCD_ILI9341_init();
    LCD_WriteReg(0xB1);
    LCD_WriteData(0);
    LCD_WriteData(0x1f); // down refresh rate to 60-70Hz
    LCD_direction(0);    // orientation portrait
    TFT9341_FontsIni();
}
//=======================================================
void loop() {
    while(1) {
        welcome_banner();
        delay(5000);
        start_demos();
        Calculate_VectorDots();
    }
}
//=======================================================
