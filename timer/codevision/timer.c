/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :  Timer
Version :  1.0
Date    : 24/05/2018
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
#include <stdio.h>

int tenth = 0 , sec = 0, min = 0 , hour = 0;
char st[20];
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{

     
      tenth++;
      if(tenth == 10) {
        sec++;
        tenth = 0;
        if(sec == 60)
        {
            min++; 
            sec=0;
            if(min == 60)
            {
                hour++;
                min = 0;
                if(hour == 24) { hour = 0; }
            }
        }
        

      }
    sprintf(st, "%02d:%02d:%02d:%d",hour,min, sec, tenth);
    lcd_gotoxy(3,0);
    lcd_puts(st);
}

void main(void)
{

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 0/977 kHz
// Mode: CTC top=OCR0
// OC0 output: Toggle on compare match
// Timer Period: 99/328 ms
// Output Pulse(s):
// OC0 Period: 0/19866 s Width: 99/328 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (1<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x60;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<OCIE0) | (0<<TOIE0);

lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
