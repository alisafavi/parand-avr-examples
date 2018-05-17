/*******************************************************
Project : 7segment refreshing
Version : 1.0
Date    : 17/05/2018
Author  : Amirhossein yaghoobi
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
#include <delay.h>
                       //  0      1     2     3     4
flash char display[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                       //  5      6     7    8      9
                          0x6d, 0x7d, 0x07, 0x7f, 0x6f};   
                          
                          
long int n = 00000000;
char myNumber[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void fill_mynumber(void);


void main(void)
{
    int i=0;
    char pd=0x01;
    
    DDRC = 0xFF; // Tanzim e port e C be tamaman khoroji                                                                   
    DDRD = 0xFF; // Tanzim e port e D be tamaman khoroji   
             
    DDRB = 0x00; // Tanzim e port e B be tamam vorodi
    
    // pull up kardan e 2 dokmeh
    PORTB.0 = 1;
    PORTB.2 = 1;

    while (1)
          {
             /* ***** Refreshing *****
              * Baray namayesh 8 ragham
              * royeh 7segment ba in ravesh
              * ma doneh doneh 0 ya 1 ro
              * bar asas in ke cathode moshtarak e 
              * ya anode moshtarak shift midim
              * va ragham ro roye tak tak e segment
              * ha minevisim.
             
             */
             pd = 0x01;
             for(i=0; i<8; i++){
                delay_ms(5);
                PORTD = ~pd; // baray e cathode moshtarak
                //PORTD = pd; // baray e anode moshtarak
                PORTC = display[myNumber[i]]; 
                pd = pd << 1;
                
             }
             
             if(!PINB.0)
             {
                 n++; 
                 fill_mynumber();
                 while(!PINB.0){}
             }
             if(!PINB.2)
             {
                 n--; 
                 fill_mynumber();
                 while(!PINB.2){}
             }
          }
}


void fill_mynumber()
{
    myNumber[7] = n % 10;
    myNumber[6] = (n/10) % 10;
    myNumber[5] = (n/100) % 10;
    myNumber[4] = (n/1000) % 10; 
    myNumber[3] = (n/10000) % 10;
    myNumber[2] = (n/100000) % 10;
    myNumber[1] = (n/1000000) % 10;
    myNumber[0] = (n/10000000) % 10;
}