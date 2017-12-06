#include <p24F16KA101.h>
#include "SenseCapApp.h"
#include "UART.h"
#include "Comparator.h"

volatile unsigned int small_current;
volatile char units[3];

void CTMUInit(void)
{
    AD1CON2bits.ALTS = 0;               // Always use MUX A and set mux settings
    AD1CHSbits.CH0NA = 0;               // Negative input of VR-
    AD1CHSbits.CH0SA = 11;              // Positive input of VR+
    AD1PCFGbits.PCFG11 = 0;             // Set as AN5 as analog input
    AD1CSSLbits.CSSL11 = 0;             // Analog channel omitted from input scan
    AD1CON1bits.ADON = 1;               // Powers the ADC module
    AD1CON1bits.SAMP = 1; 
    
    CTMUCONbits.CTMUSIDL = 0;           // Allow CTMU to operate in idle
    CTMUCONbits.TGEN = 0;               // Disable edge delay
    CTMUCONbits.EDGEN = 0;              // Disable edges
    CTMUCONbits.EDGSEQEN = 0;           // No edge sequence needed
    
    CTMUCONbits.IDISSEN = 0;            // Don't ground output of current source
    CTMUCONbits.EDG1STAT = 1;           // DO NOT TOUCH   
    CTMUCONbits.EDG2STAT = 1;           // Use to turn on/off current source
    CTMUCONbits.CTMUEN = 1;             // Enable CTMU
}

void CurrentSourceOn(void) {
    if(small_current) {
        CTMUICONbits.IRNG = 2;              // Set to 5.5 uA
        CTMUICONbits.ITRIM = 0b111111;     // Nominal current set by IRNG prev(111101)
    }else{
        CTMUICONbits.IRNG = 3;              // Set to 55 uA
        CTMUICONbits.ITRIM = 0b000110;     // Nominal current set by IRNG prev(000110)
    } 

    // Turn current source on
    CTMUCONbits.IDISSEN = 0;            // Don't ground output of current source
    CTMUCONbits.EDG2STAT = 0;           // Turn on current source
    
}


void CurrentSourceOff(void) {   
    CTMUCONbits.EDG2STAT = 1;             // Turn off current source
    CTMUCONbits.IDISSEN = 1;              // Ground output of current source
}

float findCapacitance(unsigned long int TMR) {
    Time = 0;
    float divisor = 0;
    float capacitance = 0;

    
    if(small_current) {
        divisor = 1.45454545;
        capacitance = (TMR/divisor)-61;
        if(capacitance > 1000) {        // nano range
            capacitance /= 1000;
            units[0] = 'n';
            units[1] = 'F';
            units[2] = '\0';
        }
        else {
            units[0] = 'p';
            units[1] = 'F';
            units[2] = '\0';
        }
    }
    else {
        divisor = 0.1454545;
        capacitance = (TMR/divisor)-57;
        capacitance /= 1000000;
        if(capacitance > 1000) {
            capacitance /= 1000;
            units[0] = 'm';
            units[1] = 'F';
            units[2] = '\0';
        }
        else {
            units[0] = 'u';
            units[1] = 'F';
            units[2] = '\0';
        }
    }
   return (capacitance <= 0) ? 0 : capacitance;
}
