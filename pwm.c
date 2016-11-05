#include"header.h"

void InitPWM(void)
{
    TRISE = 0X00;
    PWMCON1 = 0x00FF;
    PTCON = 0;
    _PTCKPS = 3;        //(0=1:1, 1=1:4, 2=1:16, 3=1:64)
    
    PTPER = 35;       //[20 ms period] PTPER = PWM PERIOD/(TCY*PRESCALER) [15-bit register max value 32768 or [0-32767]]
    PTMR = 0;
    PTCONbits.PTEN = 1;
}
void duty(unsigned int value)
{
    PDC1 = value;  //Duty Cycle has a max value of [2xPeriod] OR PDC = PTPER means 50% duty
}

