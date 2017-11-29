/* 
 * File:   Timer1.h
 * Author: bandakka
 *
 * Created on November 27, 2017, 1:49 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#ifdef	__cplusplus
extern "C" {
#endif


    void delay_ms(int time);
    void InitTimer1(void);
    void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

