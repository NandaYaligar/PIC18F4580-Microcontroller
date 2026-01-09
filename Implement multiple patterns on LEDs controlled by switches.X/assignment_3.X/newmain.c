/*
 * File:   newmain.c
 * Author: Nanda
 *
 * Created on 18 April, 2025, 10:39 AM
 */


#include <xc.h>

void init_config()
{
    TRISB = 0X00 ;
    PORTB = 0X00 ;
    TRISC = TRISC | 0X0F ;
}

char read_dkp_edge()
{
    static unsigned char onces = 1 ;
    
    if(((PORTC & 0X0F)!=0X0F) && onces )
    {
        onces = 0 ;
        return PORTC & 0X0F ;
    }
    else if((PORTC & 0X0F)==0X0F)
    {
        onces = 1 ;
    }
    return 0X0F ;
}


void main(void) 
{
    init_config() ;
    volatile unsigned long int delay = 0 ,i = 0 ;
    unsigned char key , flag= 0 ,mark = 0 ;
    
    
    while(1)
    {
        mark = flag ;
        key = read_dkp_edge() ;
        
        if(key==0X0E)
        flag = 1 ;
        else if(key==0X0D)
        flag = 2 ;
        else if(key==0X0B)
        flag = 3 ;
        else if(key == 0X07)
        flag = 4 ;
        if(mark != flag)
        {
            i= 0 ;
            PORTB = 0X00 ;
        }
        
        if(flag==1)
        {
            if(delay++ == 40000)
            {
                delay = 0 ; 
                if(i<8)
                {
                    PORTB = (PORTB << 1) | 1 ;   // turning on from left to right 
                }
                else if(i >= 8 && i<16)
                { 
                    PORTB = (PORTB << 1)  ;       // turning off from left to right 
                }
                else if(i >=16 && i<24)
                {
                    PORTB = (PORTB >> 1) | 0X80 ;   //turning on led from right to left
                }
                else if(i>=24 && i<32)
                {
                    PORTB = PORTB >> 1 ;           //turning off led from right to left
                }
                i++ ;
                
                if(i>31)
                i = 0 ;

            }
        }
        else if(flag==2)
        {
            if(delay++ == 40000)
            {
                delay =  0 ;
                if(i<8)
                {
                    PORTB = (PORTB << 1) | 1 ;   // turning on from left to right 
                }
                else if(i>=8 && i<16)
                { 
                    PORTB = (PORTB << 1)  ;       // turning off from left to right 
                    
                }
                i++ ;
                if(i>15)
                i = 0 ;

            }
        }
        else if(flag==3)
        {   
            if(delay++ == 30000)
            {
                delay = 0 ;
                if(i<4)
                {
                    PORTB = 0X055 ;
                }
                else if(i>=4 && i<8)
                {
                    PORTB = 0XAA ;
                }
                i++ ;
                if(i>7)
                {
                    i=0 ;
                }
            }
            
        }
        else if(flag==4)
        {
            
            if(delay++ == 40000)
            {
                delay = 0 ;
                if(i<1)
                {
                    PORTB = 0X0F ;
                }
                else if(i==1)
                {
                    PORTB = 0XF0 ;
                }
                i++ ;
                if(i>1)
                {
                    i=0 ;
                }
            }
        }
        
        mark = flag ;
        
    }
}   
       

    
    


