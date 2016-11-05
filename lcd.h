/* 
 * File:   lcd.h
 * Author: KAMAL
 *
 * Created on October 1, 2016, 1:06 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

#define RS  _LATD1
#define EN  _LATD3
#define DATA_PORT   LATB


void LcdInit(void);
void convert_to_nibble(unsigned char);
void send_data(unsigned char);
void send_cmd(unsigned char);
void Lcd_Text(char *);
void Lcd_Integer(unsigned long int);
int Gotoxy(int,int);
