#include <p24F16KA101.h>
#include "Comparator.h"
#include "UART.h"
#include "Timer2.h"

volatile unsigned long int Time;
void ComparatorInit(void)
{  
    CMSTATbits.CMIDL = 0;       // Allow operation of comparator in idle mode
    CM2CONbits.CREF = 1;        // Non-inverting input of comparator connects to CVref
    CM2CONbits.CCH = 1;         // Inverting input of comparator connects to C2INC pin
    CM2CONbits.CPOL = 1;        // Set polarity to inverted
    CM2CONbits.EVPOL = 0b01;    // Set interrupt to be triggered on high-to-low
    CM2CONbits.CLPWR = 1;       // Allow comparator to operate in low power mode
    CM2CONbits.CEVT = 0;        // Clear comparator event bit
    IPC4bits.CMIP = 6;          // Set comparator interrupt to highest priority
    IFS1bits.CMIF = 0;          // Clear comparator interrupt flag
    IEC1bits.CMIE = 1;          // Enable Comparator interrupt
    CM2CONbits.COE = 1;         // Enable the comparator output
    CM2CONbits.CON = 1;         // Turn on comparator
    TRISAbits.TRISA6 = 0;       
}

void __attribute__((interrupt, no_auto_psv))_CompInterrupt(void)
{
    CTMUCONbits.EDG2STAT = 1; //turn off current source
    
    unsigned long int temp3, temp2;
    temp3 = (unsigned long int)TMR3;
    temp2 = (unsigned long int)TMR2;
    Time = (unsigned long int)(temp3 << 16) | temp2;
    T2CONbits.TON = 0;             // Turn off timer
    T3CONbits.TON = 0;
    TMR3HLD = 0;
    TMR2 = 0;
    counter = 0;
    IFS1bits.CMIF = 0;
    CM2CONbits.CEVT= 0; 
    Nop();
    
    return;
}
