/* 
 * File:   Timer2.h
 * Author: bandakka
 *
 * Created on September 18, 2017, 5:14 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TIMER2_H */

extern volatile unsigned int restart;

extern volatile unsigned int counter;

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void);

void InitTimer23(void);
