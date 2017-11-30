/* 
 * File:   SenseCapApp.h
 * Author: babaadeniran
 *
 * Created on November 20, 2017, 5:13 PM
 */

#ifndef SENSECAPAPP_H
#define	SENSECAPAPP_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern volatile unsigned int small_current;
    extern volatile char units[3];

#ifdef	__cplusplus
}
#endif

#define VREF 2.0

void CTMUInit(void);
void CurrentSourceOn(void);
void CurrentSourceOff(void);
float findCapacitance(unsigned long int time);

#endif	/* SENSECAPAPP_H */

