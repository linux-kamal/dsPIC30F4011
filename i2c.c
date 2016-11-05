#include"header.h"

void InitI2C(void)
{
    int temp;
    //int BRG;
    //int FSCL = 100;
    //BRG = ((FCY/FSCL)-(FCY/1111111))-1;
    I2CBRG = 267;   // For 100 Khz
    I2CCONbits.I2CEN = 0;   // right now disable I2C module
    I2CCONbits.DISSLW = 0;   // disable slew rate control
    IFS0bits.MI2CIF = 0; // clear I2C interrupts
    I2CCONbits.I2CEN = 1;   // enable I2C module
    temp = I2CRCV;
    reset_i2c_bus();
}
void reset_i2c_bus()
{
    int x = 0;
    I2CCONbits.PEN = 1;     // initiate stop bit

    while(I2CCONbits.PEN)
    {
        delay(1000);
        x++;
        if(x>20) break;
    }
    I2CCONbits.RCEN = 0;
    IFS0bits.MI2CIF = 0; // clear I2C interrupts
    I2CSTATbits.IWCOL = 0;
    I2CSTATbits.BCL = 0;
    delay(10);
}

unsigned char I2C_Poll(char address)
{
    unsigned char temp;
    I2C_Start();
    temp = Write_I2C_Byte(address);
    reset_i2c_bus();
    return temp;
}
void I2C_Start(void)
{
    int x = 0;
    delay(500);
    I2CCONbits.SEN = 1; // initiate start condition
    Nop();
    while(I2CCONbits.SEN)
    {
        delay(1000);
        x++;
        if(x>20) break;
    }
    delay(10);
}
char Write_I2C_Byte(char data)
{
    int i;
    while(I2CSTATbits.TBF){}
        IFS0bits.MI2CIF = 0; // clear I2C interrupts
        I2CTRN = data;  //load data to be transmit
        for(i=0;i<500;i++)
        {
            if(!I2CSTATbits.TRSTAT) break;
                delay(1000);
        }
        if(i == 500)
            return 1;
        if(I2CSTATbits.ACKSTAT == 1)
        {
            reset_i2c_bus();
            return 1;
        }
        delay(10);
        return 0;
}
char Read_I2C_Byte(void)    // NO-ACK
{
    int i=0;
    char data=0;
    I2CCONbits.RCEN = 1;
    while(!I2CSTATbits.RBF)
    {
        i++;
        if(i>2000)
            break;
        delay(500);
    }
    data = I2CRCV;
    return data;
}
char Read_I2C_Byte_ACK(void)    // With-ACK
{
    int i=0;
    char data=0;
    I2CCONbits.RCEN = 1;
    while(!I2CSTATbits.RBF)
    {
        i++;
        if(i>2000)
            break;
        delay(500);
    }
    data = I2CRCV;
    I2CCONbits.ACKEN = 1;
    delay(10);
    return data;
}
void I2C_Retart(void)
{
    int x=0;
    I2CCONbits.RSEN = 1;
    Nop();
    while(I2CCONbits.RSEN)
    {
        delay(200);
        x++;
        if(x>100) break;
    }
    delay(10);
}
void I2C_Stop(void)
{
    int x = 0;
    I2CCONbits.PEN = 1;     // initiate stop bit
    while(I2CCONbits.PEN)
    {
        delay(500);
        x++;
        if(x>50) break;
    }
    I2CCONbits.RCEN = 1;
    IFS0bits.MI2CIF = 0; // clear I2C interrupts
    I2CCONbits.I2CEN = 0;   // right now disable I2C module
    I2CCONbits.I2CEN = 0;   // enable I2C module
    reset_i2c_bus();
    delay(100);
}
