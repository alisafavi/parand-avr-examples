/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Timer in milliseconds
Version : Amirhossein Yaghoobi
Date    : 24/05/2018
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
#include <stdio.h>

int ms = 0 , sec = 0, min = 0 , hour = 0;
char st[20];

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
      ms++;

      //  har 1000 millisecond === 1 second
      if(ms == 1000) {
        sec++;
        ms = 0; // millisecond ro reset mikonim
        if(sec == 60)
        {
            min++; 
            sec=0; // second ro reset mikonim
            if(min == 60)
            {
                hour++;
                min = 0;
                if(hour == 24) { hour = 0; }
            }
        }
      }
      /*
       * -----------------------------------
       * |           Tavajoh               |
       * ----------------------------------
       * Be dalil in ke zaman anjam mohasebat fogh
       * be hamrah amaliat e namayesh zaman roye lcd
       * bishtar az yek millisecond mishavad
       * namayesh bar roye lcd ra nabayad dar in ghesmat anjam dahim
       * va an ra dar ghesmat while(true){} dar function main anjam midahim
       */
}

void main(void)
{

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125/000 kHz
// Mode: CTC top=OCR0
// OC0 output: Toggle on compare match
// Timer Period: 1 ms
// Output Pulse(s):
// OC0 Period: 2 ms Width: 1 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (1<<COM00) | (1<<WGM01) | (0<<CS02) | (1<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x7C;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {
                // Namayesh meghdar timer bar roye lcd
                sprintf(st, "%02d:%02d:%02d:%03d", hour, min, sec, ms);
                lcd_gotoxy(2,0);
                lcd_puts(st); 
      }
}
