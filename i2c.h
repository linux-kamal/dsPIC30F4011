/* 
 * File:   i2c.h
 * Author: KAMAL
 *
 * Created on October 10, 2016, 1:59 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */
void InitI2C(void);
void I2C_Start(void);
unsigned char I2C_Poll(char);
void I2C_Retart(void);
char Write_I2C_Byte(char);
char Read_I2C_Byte(void);
char Read_I2C_Byte_ACK(void);
void reset_i2c_bus();
void I2C_Stop(void);


