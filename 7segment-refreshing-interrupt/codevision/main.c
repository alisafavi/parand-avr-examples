/*******************************************************

Project : 7segment refreshing with interrupt
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



// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
    n++;
    fill_mynumber();
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
    n--;
    fill_mynumber();
}

void main(void)
{

int i=0;
char pd=0x01;
    
DDRA = 0xFF; // Tanzim e port e A be tamaman khoroji                                                                   
DDRB = 0xFF; // Tanzim e port e B be tamaman khoroji

/* ------------------------------- *
 * in qesmat tebq e gofteye ostad ezafe shode
 * yani baray interrupt ham bayad tarif konim
 * ke interrupt hast va ham migim vorodi hast
 * va pull-up mikonim
 
 =================================================================
 | toye test i ke man kardam age in qesmat                       |
 | ro ham nazarim (yani faghat interrupt ro tarif konim)         |
 | baaz ham code kar mikone                                      |
 | estefade kardan ya nakardan in qesmat be ohdeye khodeton :-)  |
 =================================================================
*/
DDRD = 0x00; // Tanzim e port e D be tamman vorodi
PORTD.2 = 1; // pull-up
PORTD.3 = 1; // pull-up
/* ---------------------------------------- */


// Tanzim e interrupt ha
//    INT1 = ON    INT0 = ON   INT2 = OFF
GICR|=(1<<INT1) | (1<<INT0) | (0<<INT2);


// Tanzim e interrupt roye labeye paeen ravandeh
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(1<<INTF1) | (1<<INTF0) | (0<<INTF2);



// in dastor interrupt haro faal mikone roye avr
#asm("sei")

    while (1)
    {     
        pd = 0x01;
        for(i=0; i<8; i++){
            delay_ms(5);
            PORTB = ~pd; // baray e cathode moshtarak
            //PORTB = pd; // baray e anode moshtarak
            PORTA = display[myNumber[i]]; 
            pd = pd << 1;                          
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