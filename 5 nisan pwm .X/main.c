/*
 * File:   main.c
 * Author: stajyer.elektronik
 *
 * Created on 05 Nisan 2024 Cuma, 10:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
/*
 *
 */

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
#define _XTAL_FREQ 4000000
unsigned char dutyValue;

void SETPWM(int PWM){

   CCPR3L=PWM>>2;
    CCP3CON=CCP3CON & 0xCF;
    CCP3CON=CCP3CON | (0x30&(PWM<<4));
}
void delay_ms(unsigned int milliseconds){
    for(unsigned int i = 0; i < milliseconds; i++){
        __delay_ms(1); // Mikrodenetleyici kütüphanesinden gelen haz?r fonksiyon
    }
}

void main(void){
    TRISAbits.TRISA2=0;

 CCP3CON = 0b00001111; // PWM mode, DC1B<1:0> = 11
    T2CON = 0b00001111;   // Prescaler 1:16
    PR2 = 49;             // PWM period
    T2CONbits.TMR2ON=1;


    while(1){
        for(int i=0;i<1024;i++){
            SETPWM(i);
            __delay_us(10);

        }
         for(int i=1023;i>0;i--){
            SETPWM(i);
            __delay_us(10);

        }
    }
}