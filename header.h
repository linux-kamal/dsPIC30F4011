/* 
 * File:   header.h
 * Author: KAMAL
 *
 * Created on October 1, 2016, 12:04 PM
 */

#ifndef HEADER_H
#define	HEADER_H
#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
}
#endif
#endif	/* HEADER_H */

#include<xc.h>
#include<libpic30.h>
#include<stdio.h>

#include"adc.h"
#include "lcd.h"
#include"i2c.h"
#include"uart.h"
#include"pwm.h"

void delay(unsigned int);
#define FCPU    7372800
#define FCY (FCPU/4)  // NO PLL MULTIPLICATION TILL NOW
#define BAUD    9600
#define UART1_BRG_VALUE1   (FCY/BAUD)
#define UART1_BRG_VALUE2   (UART1_BRG_VALUE1/16)
#define UART1_BRG_VALUE   (UART1_BRG_VALUE2-1)

