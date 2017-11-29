

#include <p24F16KA101.h>
#include "ADC.h"

void InitADC(void) {
//    AD1CON1bits.FORM = 0;           // unisigned int
//    AD1CON1bits.SSRC = 7;           // Ends sampling and start conversion
//    AD1CON1bits.ASAM = 0;           // Sampling begins and SAMP bit is set
//    AD1CON2bits.VCFG = 0;           // Set Vreference to VDD and VSS
//    AD1CON2bits.CSCNA = 0;          // Scan Input selection for MUX A
//    AD1CON2bits.SMPI = 0;           // Interrupt at completion for each sample/convert sequence
//    AD1CON2bits.BUFM = 0;           // Buffer is set as a 16 word buffer
    AD1CON2bits.ALTS = 0;           // Always use MUX A and set mux settings
    //AD1CON3bits.ADRC = 0;           // Use System Clock
    //AD1CON3bits.SAMC = 31;          // Slowest sampling time time
    AD1CHSbits.CH0NA = 0;           // Negative input of VR-
    //AD1CON3bits.ADCS = 31;          // 
    AD1CHSbits.CH0SA = 11;           // Positive input of VR+
    AD1PCFGbits.PCFG11 = 0;          // Set as AN5 as analog input
    AD1CSSLbits.CSSL11 = 0;         // Analog channel omitted from input scan
    //IPC3bits.AD1IP = 7;             // Set to Highest Priority interrupt
    //AD1CON1bits.ADSIDL = 0;         // Set to work with idle
    //IFS0bits.AD1IF = 0;             // Clear interrupt flag
    //IEC0bits.AD1IE = 1;             // Enable ADC interrupt
    AD1CON1bits.ADON = 1;           // Powers the ADC module
    AD1CON1bits.SAMP = 1; 
}

unsigned int do_ADC(void) {
    AD1CON1bits.SAMP = 1;           // When Turns on sampling
    
    //Idle();
    
    unsigned int ADC_value = ADC1BUF0; 
            
    //AD1CON1bits.ADON = 0;           // Power off  the ADC module
    
    return ADC_value;
}


float ADC_to_Float(unsigned int ADC_value) {
    return (3.15/1023)*ADC_value;
}


//ADC interrupt subroutine

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void) {
    
    IFS0bits.AD1IF = 0;         // Clear the ADC1 Interrupt Flag
               
    AD1CON1bits.SAMP = 0;           // Turn off sampling
}