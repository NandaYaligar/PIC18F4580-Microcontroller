/*
 * File:   newmain.c
 * Author: Nanda
 *
 * Created on 2 April, 2025, 10:53 AM
 */


#include <xc.h>

void main(void) {
    TRISB = 0X00;
   PORTB = 0X00;
   
   volatile unsigned long int delay=0;
   int led = 0;
    while(1)
    {
        if(delay++ == 100000)
        {
            if(led < 8)
            {
            PORTB = (PORTB << 1) | 1; //turn on led left to right
            
            }
            else if(led < 16)
            {
                PORTB = PORTB << 1;//turn off led left to right
            }
            else if(led < 24)
            {
                PORTB = (PORTB >> 1) | 0X80;//turn on led right to left
            }
            else if(led < 32)
            {
                PORTB = (PORTB >> 1);//turn off led right to left
            }
            led++;
            delay = 0;
            if(led == 32)
            {
                led=0;
            }
        }
        
        
    }
}
