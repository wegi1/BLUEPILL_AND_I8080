
.cpu cortex-m3
    .arch armv7-m
    .fpu softvfp

    .thumb
    .thumb_func
    .syntax unified

    .global my_utoa
    .global LCD_WriteData
    .global LCD_WriteReg
    .global FILL_AREA
    .global Set_Many_Plots
    .global Put_Pixel
 
    .type   my_utoa, %function
    .type   LCD_WriteData, %function
    .type   LCD_WriteReg, %function
    .type   FILL_AREA, %function
    .type   Put_Pixel , %function
    .type   Set_Many_Plots , %function

    .text
    .align    2
//=========================================================
//========================================================
// DECIMAL CONVERSION OF ANY UNSIGNED VALUE UP TO 32 BIT
//========================================================
       // INPUT:
       //    R0, =  ; POINTER TO OUTPUT char DATA BUFFER
       //    R1, =  ; VALUE TO DECIMAL CONVERT


       // OUTPUT: R0 = LENGTH OF PRODUCED BYTES OF STRING
//========================================================
my_utoa:
        PUSH {R1-R5}  // store registers
        MOV   R5, #0  // LENGTH OF STRING
CALC01:
        //------------------
        //- R4 = R1 DIV 10 -
        //------------------
        LDR   R3, = 0xCCCCCCCD // MAGIC VALUE (!!!)
        UMULL R4,R3,R3,R1      // this three lines looks a bit strange
        LSR   R4,R3, #3        // but here we gotta divide by 10 (seriously!)
        //----------------------------------------------
        MOV   R2, R4         // R2 = R1 div by 10 without the rest
        MOV   R3, #0x0A      // R3 = 10
        MUL   R4, R4, R3     // R4 = R4 * 10

        // mod 10 calculate
        // R4 = R1 mod 10
        SUB   R4, R1, R4     // CALCULATE THE REST r4 = r1 - r4

        ORR   R4, R4, #0x30  // CHANGE TO ASCII NUMBER VALUE "0..9"
        STRB  R4, [R0,R5]    // store next decimal row
        ADD   R5, R5, #1     // R5 = length of string
        MOV   R1, R2         // R1 = before stored value in R2 = (R1 div 10)
        CMP   R1, #0         // R1 = 0? (that was last one operation?)
        BNE   CALC01         // if R1 != 0 then continue CALC01 loop

        // R1 = 0            // R1 = 0, R5 = length of produced string
        STRB  R1, [R0, R5]   // FIRST TIME R1 = 0 SO NULL TERMINATED STRING MAKE NULL
        PUSH  {R5}           // TEMPRARY STORE LENGTH OF STRING
        SUB   R5, R5, #1     // SET OFFSET AT THE END OF STRING (BACKWARD POSSITION)

        // R0 = POINTER TO OUTPUT NULL TERMINATED STRING
        // R5 = OFFSET TO THE END OF STRING (BACKWARD POSSITION)
        // R1 = OFFSET TO THE START OF STRING (FORWARD POSSITION) R1 = 0 AT THE END CALC01 ROUTINE
        // R4 = BACKWARD BYTE (BYTE FROM "RIGHT SIDE")
        // R2 = FORWARD  BYTE (BYTE FROM "LEFT  SIDE")
CALC02:
        LDRB  R4, [R0, R5] // GET DATA FROM THE END (FROM RIGT SIDE)
        LDRB  R2, [R0, R1] // GET DATA FROM THE START (LEFT SIDE)
        STRB  R2, [R0, R5] // GET DATA FROM THE "LEFT  SIDE INTO THE RIGHT SIDE"
        STRB  R4, [R0, R1] // GET DATA FROM THE "RIGHT SIDE INTO THE LEFT  SIDE"
        ADD   R1, R1, #1   // ACTUALIZE STRING FORWARD POSSITION
        SUB   R5, R5, #1   // ACTUALIZE STRING BACKWARD POSSITION
        CMP   R5, R1       // R5 =< R1 ?
        BEQ   END_CALC     // if R5 = R1 go to finish
        BGT   CALC02       // if R5 > R1 continue loop - otherway finish (R5 < R1)

END_CALC:
        // acording declaration this functin is "int" and
        // acordind AAPCS should be returned int value in R0
        // simple "return datalength;" in C
        POP   {R0}         // OUTPUT: R0 = LENGTH OF PRODUCED BYTES OF STRING R0 = R5

        POP {R1-R5}        // restore registers

        BX LR  // ADIOS :)

//=====================================================

//==============================================================
LCD_WriteData:
        //PUSH   {R0-R3}             // save used registers

        // after invoke in R0 16bit data to send -> = AACP STANDARD
//===============================================
//= store 16 bit data from R0 into FSMC DATABUS =
//===============================================
        LDR    R2, =  0x40010800  // GPIO A ADDRESS POINTER
        MOV    R1, R0             // transfer data to send into R1
        AND    R1, 0x00FF         // and lowest 8 bit to use in GPIO A
        LDR    R3, [R2, #0x0C]    // read GPIO_A ODR
        AND    R3, 0xFF00         // mask 8 high bits
        ORR    R3, R1             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R3, [R2, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        AND    R0, 0xFF00         // use high 8 bits our data to send
        LDR    R3, [R2, #0x040C]  // addres pointer added to sign GPIO_B ODR
        AND    R3, 0x00FF         // prepare for high 8 bits from R0
        ORR    R3, R0             // join data to send
        STR    R3, [R2, #0x040C]  // and finally store high byte our data on the DATABUS

        LDR    R0, = 0x00100020   // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        STR    R0, [R2, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        MOV    R0, 0x10           // [GPIO_B->BSRR] NWE = 1 
        STR    R0, [R2, #0x0410]  // [GPIO_B->BSRR] NWE = 1 


        //POP    {R0-R3}            // restore used registers vaues
        BX     LR
//=============================================================
       // INPUT:
       //    R0, =  ; 16 bit data value to store on the FSMC DATABUS

       // output: no output
//================================================================
LCD_WriteReg:
       // PUSH   {R0-R3}             // save used registers

        // after invoke in R0 16bit data to send -> = AACP STANDARD

//===============================================
//= store 16 bit data from R0 into FSMC DATABUS =
//===============================================
        LDR    R2, =  0x40010800  // GPIO A ADDRESS POINTER
  //      MOV    R1, R0             // transfer data to send into R1
        AND    R0, 0x00FF         // and lowest 8 bit to use in GPIO A
        LDR    R3, [R2, #0x0C]    // read GPIO_A ODR
        AND    R3, 0xFF00         // mask 8 high bits
        ORR    R3, R0             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R3, [R2, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

//      AND    R0, 0xFF00         // use high 8 bits our data to send
//      LDR    R3, [R2, #0x040C]  // addres pointer added to sign GPIO_B ODR
//      AND    R3, 0x00FF         // prepare for high 8 bits from R0
//      ORR    R3, R0             // join data to send
//      STR    R3, [R2, #0x040C]  // and finally store high byte our data on the DATABUS

        MOV    R0, 0x30           // [GPIO_B] NWE = 0 RS = 0
        STR    R0, [R2, #0x0414]  // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        MOV    R0, 0x10
        STR    R0, [R2, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

       // POP    {R0-R3}            // restore used registers vaues
        BX     LR
//==============================================================
       // INPUT:
       //    R0, =  ; 16 bit data value to store on the FSMC DATABUS
       //    R1, =  many bytes to repeat write

       // output: no output
//================================================================
FILL_AREA:

        //PUSH   {R0-R3}           // save used registers
        PUSH   {R1}              // save one more time our R1 reg. where we gotta many bytes to copy value

        // after invoke in R0 16bit data to send -> = AACP STANDARD
        // in R1 many bytes to copy (fill rect)
//===============================================
//= store 16 bit data from R0 into FSMC DATABUS =
//===============================================
        LDR    R2, = 0x40010800  // GPIO A ADDRESS POINTER
        MOV    R1, R0             // transfer data to send into R1
        AND    R1, 0x00FF         // and lowest 8 bit to use in GPIO A
        LDR    R3, [R2, #0x0C]    // read GPIO_A ODR
        AND    R3, 0xFF00         // mask 8 high bits
        ORR    R3, R1             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R3, [R2, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        AND    R0, 0xFF00         // use high 8 bits our data to send
        LDR    R3, [R2, #0x040C]  // addres pointer added to sign GPIO_B ODR
        AND    R3, 0x00FF         // prepare for high 8 bits from R0
        ORR    R3, R0             // join data to send
        STR    R3, [R2, #0x040C]  // and finally store high byte our data on the DATABUS
//---
        LDR    R0, = 0x00100020   // [GPIO_B->BSRR] NWE = 0 RS = 1
        MOV    R3, 0x10           // [GPIO_B->BRR] PB4 bits to clear
        POP    {R1}               // restore many bytes to send value
fill_lp0:
        STR    R0, [R2, #0x0410]  // [GPIO_B->BSRR] NWE = 0 ; RS = 1 [GPIO B]
        SUBS   R1, R1, #1         // DECREASE MANY BYTES TO SEND VALUE (COUNT) AND UPDATE FLAGS
        STR    R3, [R2, #0x0410]  // [GPIO B->BSRR] NWE = 1 
        BNE    fill_lp0

        //POP    {R0-R3}            // restore used registers vaues
        BX     LR   
//==============================================================
 
//Set_Many_Plots(uint16_t * plots_X, uint16_t * plots_y, uint32_t ManyPlots, uint16_t color );

// R0 = PLOT X POINTER
// R1 = PLOT Y POINTER
// R2 = MANY PLOTS TO PASTE
// R3 = UINT16_T COLOR

// R4 OFFSET TO BUFFERS
// R5 = GPIO ODR OFFSET
// R6 DATA TO SEND (REGISTER NUMBER OR X-Y COORDINATES)
// R7 GPIO_ODR VALUE
// R8-R9 DATA FOR CLICK NWE FOR WRITEREG OPERATION
// R10 BACKUP OF R6 REGISTER
// R11 = 0x00100020  => [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
// R12 GPIOB->ODR VALUE (HIGH 8 BYTES OF PERIPH ARE 8 HIGHEST BYTES ON THE DATABUS)
Set_Many_Plots:

        PUSH   {R3-R12}
        MOV    R4, #0              // OFFSET TO TABLES
        LDR    R5, = 0x40010800    // GPIOA ADDRESS POINTER
        MOV    R8,  #0x30          // [GPIO_B->BRR] NWE = 0 RS = 0
        MOV    R9,  #0x10          // [GPIO_B->BSRR] NWE = 1 
        LDR    R11, = 0x00100020   // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        LDR    R7, [R5, #0x0C]     // read GPIO_A ODR
        LDR    R12, [R5, #0x040C]  // read GPIO_B ODR (addres pointer added to sign GPIO_B ODR #0x040C)
SET_PLOT_LOOP:

//--- SEND REGISTER NUMBR 0x2A
        MOV    R6, #0x2A          // R6 = DATA TO SEND
        
        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        LDRH   R10, [R1, R4]       // READ Y COORD
        STR    R8, [R5, #0x0414]   // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        MOV    R6, R10, LSR #8     // HIGH 8 BITS FIRST           // COPY Y COORD
        STR    R9, [R5, #0x0410]   // [GPIO_B->BSRR] NWE = 1 

//--- FIRST Y COORD SEND ---

        // DON'T NEED BEFOR WE READ PORT A
        //LDR    R7, [R5, #0x0C]    // read GPIO_A ODR
        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 
//---
        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10, LSR #8    // HIGH 8 BITS FIRST
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits        
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//- 2nd TIME PUT Y COORD ---
        
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, #0x2B          // R6 = DATA TO SEND
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//--- SEND REGISTER NUMBR 0x2B
        
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS
        LDRH   R10,  [R0, R4]       // READ X COORD
        STR    R8,   [R5, #0x0414]  // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        MOV    R6,   R10, LSR #8    // COPY X COORD
        STR    R9,   [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

//*************************

//--- NOW X COORD SEND ---
        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS   


        MOV    R6, R10, LSR #8
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//- 2nd TIME PUT X COORD ---

        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, #0x2C          // R6 = DATA TO SEND
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//--- SEND REGISTER NUMBR 0x2C
        
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        MOV    R6, R3            // GAVE COLOR AND PUT 16 BITS OF COLOR TO DATABUS
        STR    R8, [R5, #0x0414]  // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS  

        MOV    R6, R3            // RESTORE COLOR FOR PUT 8 HIGH BITS TO DATABUS
        AND    R6, 0xFF00

        
        AND    R12, 0x00FF         // prepare for high 8 bits from R0
        ORR    R12, R6             // join data to send
        STR    R12, [R5, #0x040C]  // and finally store high byte our data on the DATABUS
        //FINALLY LATCH THE COLOR
       
        ADD    R4, R4, #0x02      // increase offset 
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        SUBS   R2, R2, #1         // manyDots count
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1   

        BNE    SET_PLOT_LOOP
//****************************

        POP    {R3-R12}
        BX     LR
//==============================================================
//Put_Pixel(uint16_t  plot_X, uint16_t  plot_Y, uint16_t color );

// R0 = PLOT X VALUE
// R1 = PLOT Y VALUE
// R2 = COLOR
// R3 UNUSED

// R4 = GPIOB->ODR VALUE (HIGH 8 BYTES OF PERIPH ARE 8 HIGHEST BYTES ON THE DATABUS)
// R5 = GPIO ODR OFFSET
// R6 DATA TO SEND (REGISTER NUMBER OR X-Y COORDINATES)
// R7 GPIO_ODR VALUE
// R8-R9 DATA FOR CLICK NWE FOR WRITEREG OPERATION
// R10 BACKUP OF R6 REGISTER
// R11 = 0x00100020  => [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]

Put_Pixel:

        PUSH   {R4-R11}

        LDR    R5, = 0x40010800   // GPIOA->ODR ADDRESS POINTER
        MOV    R8,  #0x30         // [GPIO_B] NWE = 0 RS = 0
        MOV    R9,  #0x10         // [GPIO_B->BSRR] NWE = 1 
        LDR    R11, = 0x00100020  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        LDR    R7, [R5, #0x0C]    // read GPIO_A ODR
        LDR    R4, [R5, #0x040C]  // read GPIO_B ODR (addres pointer added to sign GPIO_B ODR #0x040C)

//--- SEND REGISTER NUMBR 0x2A
        MOV    R6, #0x2A          // R6 = DATA TO SEND
        
        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        MOV    R10, R1            // READ Y COORD
        STR    R8, [R5, #0x0414]  // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        MOV    R6, R10, LSR #8    // HIGH 8 BITS FIRST           // COPY Y COORD
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

//--- FIRST Y COORD SEND ---

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 


        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10, LSR #8    // HIGH 8 BITS FIRST
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits        
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//- 2nd TIME PUT Y COORD ---
        
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 


        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, #0x2B          // R6 = DATA TO SEND
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//--- SEND REGISTER NUMBR 0x2B
        

        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        MOV    R10,  R0             // READ X COORD
        STR    R8,   [R5, #0x0414]  // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        MOV    R6,   R10, LSR #8    // COPY X COORD
        STR    R9,   [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

//*************************

//--- NOW X COORD SEND ---

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS   


        MOV    R6, R10, LSR #8
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]

        AND    R7, 0xFF00         // mask 8 high bits
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//- 2nd TIME PUT X COORD ---
        
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, R10
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 


        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS        

        MOV    R6, #0x2C          // R6 = DATA TO SEND
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        AND    R7, 0xFF00         // mask 8 high bits
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1         
//---
//--- SEND REGISTER NUMBR 0x2C
        
        
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS

        MOV    R6, R2            // GAVE COLOR AND PUT 16 BITS OF COLOR TO DATABUS
        STR    R8, [R5, #0x0414]  // [GPIO_B->BRR] NWE = 0, RS = 0 [GPIO B]
        AND    R6, 0xFF
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1 

        
        
        AND    R7, 0xFF00         // mask 8 high bits
        ORR    R7, R6             // join ODR  GPIO_A prepared value with a nev lowest 8 bits
        STR    R7, [R5, #0x0C]    // store lowest 8 bits into GPIO_A as our low byte DATABUS  

        MOV    R6, R2            // RESTORE COLOR FOR PUT 8 HIGH BITS TO DATABUS
        AND    R6, 0xFF00

        
        AND    R4, 0x00FF         // prepare for high 8 bits from R0
        ORR    R4, R6             // join data to send
        STR    R4, [R5, #0x040C]  // and finally store high byte our data on the DATABUS
        //FINALLY LATCH THE COLOR
       
        
        STR    R11,[R5, #0x0410]  // [GPIO_B->BSRR] NWE = 0, RS = 1 [GPIO B]
        NOP
        STR    R9, [R5, #0x0410]  // [GPIO_B->BSRR] NWE = 1   

       
//****************************
        POP    {R4-R11}
        BX     LR
//==============================================================