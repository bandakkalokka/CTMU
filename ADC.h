/* 
 * File:   ADC.h
 * Author: bandakka
 *
 * Created on October 13, 2017, 1:14 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif


    void InitADC(void);
    float ADC_to_Float(unsigned int ADC_value);
    void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);
    unsigned int do_ADC(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

