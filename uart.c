#include"header.h"

void Init_Uart2(void)
{
    U2BRG = 191;    ///baud rate 9600 
    //U1MODEbits.ALTIO = 0;
    IEC1bits.U2RXIE = 1;
    //U1STA &= 0xfffc;
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;
}
void Uart2_String(char *string)
{
    unsigned int i=0;
    while(*(string+i) != '\0')
    {
        Uart2_Byte(*(string+i));
        i++;
    }
    //delay(2);
}
void Uart2_Integer(int value)
{
    char str[10];
    int val;
    val = value;
    sprintf(str,"%d",val);
    Uart2_String(str);
    //delay(2);
}
void Uart2_Byte(char data)
{
    U2TXREG = data;
    while(!U2STAbits.TRMT){}
}

