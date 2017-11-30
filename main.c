/* 
 * File:   main.c
 * Author: rv
 *
 * Created on January 9, 2017, 5:26 PM
 */


#include "xc.h"
//#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "UART.h"
#include "Timer2.h"
#include "Timer1.h"
#include "Comparator.h"
#include "SenseCapApp.h"
#include "CVref.h"
#include "ChangeClk.h"

//// CONFIGURATION BITS ////

// Code protection 
#pragma config BSS = OFF // Boot segment code protect disabled
#pragma config BWRP = OFF // Boot sengment flash write protection off
#pragma config GCP = OFF // general segment code protecion off
#pragma config GWRP = OFF

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

// WDT
#pragma config FWDTEN = OFF // WDT is off
#pragma config WINDIS = OFF // STANDARD WDT/. Applicable if WDT is on
#pragma config FWPSA = PR32 // WDT is selected uses prescaler of 32
#pragma config WDTPS = PS1 // WDT postscler is 1 if WDT selected

//MCLR/RA5 CONTROL
#pragma config MCLRE = OFF // RA5 pin configured as input, MCLR reset on RA5 diabled

//BOR  - FPOR Register
#pragma config BORV = LPBOR // LPBOR value=2V is BOR enabled
#pragma config BOREN = BOR0 // BOR controlled using SBOREN bit
#pragma config PWRTEN = OFF // Powerup timer disabled
#pragma config I2C1SEL = PRI // Default location for SCL1/SDA1 pin

//JTAG FICD Register
#pragma config BKBUG = OFF // Background Debugger functions disabled
#pragma config ICS = PGx2 // PGC2 (pin2) & PGD2 (pin3) are used to connect PICKIT3 debugger

// Deep Sleep RTCC WDT
#pragma config DSWDTEN = OFF // Deep Sleep WDT is disabled
#pragma config DSBOREN = OFF // Deep Sleep BOR is disabled
#pragma config RTCOSC = LPRC// RTCC uses LPRC 32kHz for clock
#pragma config DSWDTOSC = LPRC // DeepSleep WDT uses Lo Power RC clk
#pragma config DSWDTPS = DSWDTPS7 // DSWDT postscaler set to 32768 


// GLOBAL VARIABLES
unsigned int temp;
unsigned int i;


// MACROS
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   // set sleep mode
#define Idle() {__asm__ volatile ("pwrsav #1");}
#define dsen() {__asm__ volatile ("BSET DSCON, #15");}



/*
 * 
 */
        
int main(void) {
    
    float capacitance = 0;
    char str[40];
    
    //Clock output on REFO
    TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0000;
     
    // Switch clock: 32 for 32kHz, 500 for 500 kHz, 8 for 8MHz 
    NewClk(8); //
    
    TRISAbits.TRISA3 = 1;          //Set AN11 as input
    TRISBbits.TRISB13 = 1;         //Set as input for capacitor
    
    small_current = 1;
    counter = 1;
    restart = 0;
    
    InitTimer23();
    InitTimer1();
    ComparatorInit();
    CVREFInit(VREF);
    CTMUInit();
    
    DispString("Discharging Capacitor!\n\r");
    CTMUCONbits.IDISSEN = 1;
    delay_ms(3000);

    DispString("Ready to go!\n\r");
    
    while(1)
    {
        T2CONbits.TON = 1;      //Turn on timer 2/3
        CurrentSourceOn();      //Turn on current source
        
        Idle();
        
        if(!restart) {
            CurrentSourceOff();    //Turn off current source
            delay_ms(3000);
            capacitance = findCapacitance(Time);
            sprintf(str, "Capacitance: %f %s \n\r", capacitance, units);
            DispString(str);
        }
        else {
            DispString("Big Capacitor!\n\r");
            CurrentSourceOff();
            delay_ms(3000);
            restart = 0;
        }
        
    }
    
    return 0;
}

