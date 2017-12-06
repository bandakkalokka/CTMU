/* 
 * File:   Comparator.h
 * Author: babaadeniran
 *
 * Created on October 30, 2017, 1:45 PM
 */

#ifndef COMPARATOR_H
#define	COMPARATOR_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif


extern volatile unsigned long int Time;
extern volatile unsigned int CompFlag;

void ComparatorInit(void);

void __attribute__((interrupt, no_auto_psv))_CompInterrupt(void);

#endif	/* COMPARATOR_H */

