

#include <p24F16KA101.h>
#include "Timer2.h"
#include "ChangeClk.h"
#include "Timer1.h"
#include "SenseCapApp.h"
#include "Comparator.h"
#include "UART.h"


void InitTimer23(void) {
    T2CONbits.T32 = 0b1;                //Set to use both TImer2 and Timer3 (32-bit)
    T2CONbits.TCKPS = 0b00;             //Set pre-scale to 1
    T2CONbits.TCS = 0b0;                //Use Internal Clock
    IEC0bits.T3IE = 1;                 //Enable the Timer Interrupt
    IPC2bits.T3IP = 7;                  //Set to second highest priority
    IFS0bits.T3IF = 0b0;                //Clear Flag status
    PR3 = 11;
}

//Timer1 Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    CompFlag = 0;
    if(small_current)
        PR3 = 3000;
    
    T2CONbits.TON = 0;
    small_current = 0;
    IFS0bits.T3IF = 0b0;                //Clear Flag status
    TMR2 = 0;
    TMR3 = 0;
    Nop();
}

