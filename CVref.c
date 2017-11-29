
#include <p24F16KA101.h>
#include "CVref.h"

#define LOWER 0.78      // If voltage is below this limit, use CVRR = 1
#define UPPER 2.24      // If voltage is above this limit, set CVR = 15
#define CVRSRC 3.115     // True source voltage level of PICKit (As seen on oscilloscope)

void CVREFInit(float vref){
    if(vref < LOWER && vref >= 0.0) // Check for voltage input greater than 0 and less than LOWER
    { 
        CVRCONbits.CVRR = 1; // Set CVRR to 1 for better resolution at lower voltage output
        //TRISBbits.TRISB14 = 0; // Set RB14 to output
        CVRCONbits.CVRSS = 0; // Set CVR to use VSS- and VDD+
        
        unsigned int CVR;     // Variable to hold CVR value
        float f_CVR = vref * 24 / CVRSRC; // Calculation to determine CVR
        
        // Round CVR up to the nearest integer if its decimal is >= 0.5 
        // and round it down if it's not 
        if (f_CVR - (unsigned int)f_CVR >= 0.5)
            CVR = (unsigned int)f_CVR + 1;
        else
            CVR = (unsigned int)f_CVR;
        
        CVRCONbits.CVR = CVR; // Set CVR 
        CVRCONbits.CVREN = 1; // Enable CVR
        CVRCONbits.CVROE = 0; // CVREF voltage connected from CVREF pin
    }
    else if (vref >= LOWER && vref <= UPPER) // Check for voltage input greater than LOWER and less than UPPER
    {
        CVRCONbits.CVRR = 0; // Set CVRR to 0 to obtain higher voltage output
        //TRISBbits.TRISB14 = 0; // Set RB14 to output
        CVRCONbits.CVRSS = 0; // Set CVR to use VSS- and VDD+
        
        unsigned int CVR;    // Variable to hold CVR value
        float f_CVR = (vref - CVRSRC/4)*32/CVRSRC; // Calculation to determine CVR
        
        // Round CVR up to the nearest integer if its decimal is >= 0.5 
        // and round it down if it's not 
        if (f_CVR - (unsigned int)f_CVR >= 0.5)
            CVR = (unsigned int)f_CVR + 1;
        else
            CVR = (unsigned int)f_CVR;
        
        CVRCONbits.CVR = CVR; // Set CVR
        CVRCONbits.CVREN = 1; // Enable CVR
        CVRCONbits.CVROE = 0; // CVREF voltage disconnected from CVREF pin
    }
    else if (vref < 0) // If the input is negative we will output zero volts
    {
        CVRCONbits.CVR = 0; // Set CVR to 0 for 0 volts
        CVRCONbits.CVRR = 1; // Set CVRR to 1 to allow for zero volt output
        CVRCONbits.CVRSS = 0; // Set CVR to use VSS- and VDD+
        CVRCONbits.CVREN = 1; // Enable CVR
        CVRCONbits.CVROE = 0; // CVREF voltage connected from CVREF pin
    }
    else if (vref > UPPER) // If the input is greater than the threshold, we will output the maximum amount
    {
        CVRCONbits.CVR = 15; // Set CVR to 15 for max output
        CVRCONbits.CVRR = 0; // Set CVRR to 0 to allow for max volt output
        CVRCONbits.CVRSS = 0; // Set CVR to use VSS- and VDD+
        CVRCONbits.CVREN = 1; // Enable CVR
        CVRCONbits.CVROE = 0; // CVREF voltage connected from CVREF pin
    }
}
