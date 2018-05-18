/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :    lcd character fly
Version : 
Date    : 18/05/2018
Author  :   Amirhossein Yaghoobi 
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

void main(void)
{

char loc=0;  // mogheiat e alan e character
char direction = 1; // jahat e harekat: 1 -> LTR,  -1  -> RTL

/* ------------------------------------------ *
                 lcd ro roye port A mibandim
                 | LCD |                         | AVR |
                  RS      --------->     PA0
                  RW     --------->     PA1
                  E         --------->     PA2
                
                 D4       --------->     PA4
                 D5       --------->     PA5
                 D6       --------->     PA6
                 D7       --------->     PA7                                    
 * ------------------------------------------ */
lcd_init(16);

while (1)
      {
            lcd_clear();
            
            lcd_gotoxy(loc, 0);  // maamoli
            //lcd_gotoxy(loc, loc % 2);  // Zig zagi  
            
            lcd_putchar('*');
            
            if(loc == 15)   {  direction = -1;  }
            if(loc ==   0)    {   direction  =  1;  } 
            
            loc += direction;
            
            delay_ms(200);

      }
}
