/* 
 * File:   UART2.h
 * Author: rvyas
 *
 * Created on November 19, 2016, 9:22 PM
 */

#ifndef UART2_H
#define	UART2_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

void InitUART2(void);
void XmitUART2(unsigned char, unsigned int);

void __attribute__ ((interrupt, no_auto_psv)) _U2RXInterrupt(void);
void __attribute__ ((interrupt, no_auto_psv)) _U2TXInterrupt(void); 

void DispHex(unsigned int);
void DispHex32(unsigned long int);
void DispString(char*);
void DispDec(unsigned int);

#endif	/* UART2_H */

