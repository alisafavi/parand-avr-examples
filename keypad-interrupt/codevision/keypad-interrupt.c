/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :   Keypad interrupt
Version : 1.0
Date    : 18/05/2018
Author  :    Amirhossein Yaghoobi
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 1/000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <alcd.h>
#include <delay.h>
#include <sleep.h>


#define C0 PIND.4
#define C1 PIND.5
#define C2 PIND.6
#define C3 PIND.7

flash char shift[4] = {0xFE, 0xFD, 0xFB, 0xF7};
flash char layout[4][4] = {
                                            { '7', '8', '9', '/' },
                                            { '4', '5', '6', '*' },
                                            { '1', '2', '3', '-' },
                                            { 'C', '0', '=', '+' }
                                            }; 
                                           


char keypad(void);                                         

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
    char ch =  keypad();
    
    if( ch == 'C') { lcd_clear(); }
    else { lcd_putchar(ch); }
}

void main(void)
{
    /* --------------------------------------------------------------- *
     *                                             keypad Settings                                                    *
     * --------------------------------------------------------------- */
    DDRD    = 0x0F;    // 4bit dovom vorodi, 4bit aval khoroji
    PORTD = 0xF0;    // pull-up 4bit dovom
     /* ------------------------------------------------------------ */ 
       
    lcd_init(16);  
    
    /*  --------------------------------------------------------------- *
    *                                                Interrupt Settings                                                *
    *  --------------------------------------------------------------- */
    //          INT1 = OFF  | INT0 = OFF | INT2 = ON
    GICR|=(0<<INT1) | (0<<INT0) | (1<<INT2);

    // INT2 Mode: Falling Edge
    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);
    GIFR=(0<<INTF1) | (0<<INTF0) | (1<<INTF2);
     /* ------------------------------------------------------------ */


    // Faal sazi e interrupt ha
    #asm("sei")

    while (1)
    {
        idle();
    }
}

char keypad()
{
    int row, column = -1; 
    for(row=0; row<4; row++)
    {
        PORTD = shift[row];
        if(!C0) { column = 0; }
        if(!C1) { column = 1; }
        if(!C2) { column = 2; }
        if(!C3) { column = 3; }
        
        if( column != -1)
        {
            PORTD = 0xF0; // Reset kardan e shift
            return layout[row][column];
        }
    }
}
