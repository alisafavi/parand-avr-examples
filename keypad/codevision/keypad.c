/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 18/05/2018
Author  : 
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

void main(void)
{
    char ch;
    DDRD = 0x0F;
    PORTD = 0xF0;
    
    lcd_init(16);
        
    while (1)
          {
             ch = keypad();     
             switch(ch)
             {
                case 'C':
                    lcd_clear();
                    break;
                default:
                    lcd_putchar(ch);
             
             }
          }
}

char keypad(){
    int row;
    int column = -1;
     
    while(1){
        for(row=0; row<4 ; row++)
        {
            PORTD = shift[row];
            
            if(!C0) { column = 0; }
            if(!C1) { column = 1; }
            if(!C2) { column = 2; }
            if(!C3) { column = 3; }
            
            if(column != -1)
            {
                while(!C0) { }
                while(!C1) { }
                while(!C2) { }
                while(!C3) { }  
                
                return layout[row][column];
            }  
            delay_ms(50);
        }
    }

}
