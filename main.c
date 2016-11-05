#include"header.h"
#include<xc.h>


#define LED _LATD2
/*--------------------------- Configuration words ----------------------------*/
//#pragma config FPR=HS
#pragma config FPR=XT_PLL16
#pragma config FOS=PRI
#pragma config WDT = WDT_OFF
#pragma config FPWRT = PWRT_OFF
/*----------------------------------------------------------------------------*/
int data0, data1;
char Uart2_buffer[30];
int flag = 0;

/*----------------------------------------------------------------------------*/
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void);   // PSV model not specified

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);

int main(void)
{
    int adc_value = 0;

    ADPCFG = 0x00FF;
    TRISB = 0XFF00;
    //_TRISD2 = 1;
    TRISD = 0X00;

    TRISCbits.TRISC13 = 0;      //U1TX
    TRISCbits.TRISC14 = 1;      //U1RX

    LcdInit();
    InitAdc();
    Init_Uart2();
    InitPWM();
/*
    Gotoxy(5,1);
    Lcd_Text("LINE 2");
    delay(10);
    Gotoxy(6,2);
    Lcd_Text("LINE 1");
    delay(10);
    Gotoxy(7,3);
    Lcd_Text("LINE 3");    
    delay(10);
  */
    /*-------------Timer1 Initialization and configuration------------------- */
    T1CON = 0;
    TMR1 = 0;
    PR1 = 50000;
    T1CONbits.TCS = 0;  // SELECT CLK SRC
    T1CONbits.TCKPS = 0;    // PRESACLER
    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;  // or could be write like this _T1IF = 0;
    IEC0bits.T1IE = 1;  // _T1IE
    T1CONbits.TON = 1;  // or could be write like _TON
    
    unsigned char temp,temp2,temp3,temp4;
    
    temp4=((16/10)<<4)|(16%10);

    InitI2C();
    I2C_Start();
    Write_I2C_Byte(0XD0);
    Write_I2C_Byte(0X02);
    Write_I2C_Byte(temp4);
    reset_i2c_bus();

    
    while(1)
    {
    temp = 100;
    InitI2C();
    I2C_Start();
    
    
    Write_I2C_Byte(0XD0);
    Write_I2C_Byte(0X02);
    I2C_Retart();
    Write_I2C_Byte(0XD1);
    temp = Read_I2C_Byte();

    temp2 = (10*(temp>>4)) + (temp&0x0F);
    temp3 = (((temp&0b01110000)>>4)*10)+(temp&0b00001111);

    //Now write time back to RTC Module
    //temp=((sec/10)<<4)|(sec%10);
    //temp4=((59/10)<<4)|(59%10);
    
    Uart2_String("Read : ");
    Uart2_Byte(temp);
    Uart2_Byte(':');
    Uart2_Integer(temp);
    Uart2_Byte(':');
    Uart2_Integer(temp2);
    Uart2_Byte(':');
    Uart2_Integer(temp3);
    Uart2_Byte(':');
    Uart2_Integer(temp4);

    Uart2_Byte('\n');
    
    //delay(200);
}
    //temp = I2C_Poll(0XD1);  //READ
    
    //Uart2_Integer(temp);
    
    while(1);
    {
        //printf("Data Is : %d \r\n",67);
        // delay(500);
        //Uart2_String("\n HELLO HI THIS IS A TEST \n");
        //Uart2_Integer(12345);
        //Uart2_Byte('\n');
        delay(1000);
        //if (flag == 1)
        {
            Uart2_String("HELLO HI THIS IS A TEST:");
            Uart2_Integer(12345);
            Uart2_Byte('\n');
            Uart2_String(Uart2_buffer);
            Uart2_Byte('\n');
            //memset(Uart2_buffer,0,sizeof(char)*30);
        }
            
        /*
        while (U1STAbits.TRMT==0);
        if(U1MODEbits.PDSEL == 3)
            U1TXREG = 35;
        else
            U1TXREG = 35 & 0xFF;
        */
        
 /*     Gotoxy(1,4);
        Lcd_Integer(TMR1);
        Lcd_Text("  ");
        adc_value = GetAdc(8);
        Gotoxy(8,4);
        Lcd_Text("READ ADC:");
        Lcd_Integer(adc_value);
        Lcd_Text("");
        delay(300);
  */
    }
    while(1)
    {
        LED = 1;
        delay(40);
        LED = 0;
        delay(200);
        
        Gotoxy(1,4);
        delay(2);
        Lcd_Integer(data0);
        Gotoxy(10,4);
        delay(2);
        Lcd_Integer(data1);
        
        //printf("A");
    }
    
    return 0;
}
/*----------------------------------------------------------------------------*/
void delay(unsigned int ms)
{
    while(ms--)
      __delay32(5000);
}
/*------------------------------- INT ----------------------------------------*/
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{	
        _T1IF = 0;      // Clear Timer 1 interrupt flag
	if (_LATD2) _LATD2 = 0; else _LATD2 = 1;

        static int kam = 0;
      
            if(kam>70)
                kam = 0;
            duty(kam++);
}
void __attribute__((__interrupt__)) _U2RXInterrupt(void) {
    char temp;
    static int i = 0;
    IFS1bits.U2RXIF = 0;
    temp = U2RXREG;
    Uart2_buffer[i++] = temp;
    if (temp == '$')
        flag = 1;
    //U2TXREG = temp;
    //while(!U2STAbits.TRMT)
    //{}
    // strcpy/memcpy
}
