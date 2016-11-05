#include"header.h"


void InitAdc()
{
    TRISBbits.TRISB8 = 1;   // for adc RB8 INPUT DIRECTION
    ADPCFGbits.PCFG8 = 0;   // for adc RB8 AS ADC CHANNEL NOT DIGITAL
    ADCON3bits.ADCS = 15;  // Tad = 266ns, conversion time is 12*Tad
    ADCON1bits.ADON = 1;   // Turn ADC ON
}

int GetAdc(int channel)
{
    ADCHS = channel;          // Select the requested channel
    ADCON1bits.SAMP = 1;      // Start sampling
    __delay32(30);            // 1us delay @ 30 MIPS
    ADCON1bits.SAMP = 0;      // Start Converting
    while (!ADCON1bits.DONE); // Should take 12 * Tad = 3.2us

    return ADCBUF0;
}
/*
void InitAdc(void)
{
    TRISBbits.TRISB8 = 1;
    ADPCFGbits.PCFG8 = 0;

    ADCON1bits.ADSIDL=0;
    ADCON1bits.FORM=0;
    ADCON1bits.SSRC=7;
    ADCON1bits.SAMP=1;
    ADCON2bits.VCFG=7;
    ADCON2bits.CSCNA=1;
    ADCON2bits.SMPI=2;
    ADCON2bits.BUFM=0;
    ADCON2bits.ALTS=0;
    ADCON3bits.SAMC=31;
    ADCON3bits.ADRC=1;
    ADCON3bits.ADCS=31;
    ADCHSbits.CH0NB=0;
    ADCHSbits.CH0NA=0;
    ADCHSbits.CH0SA=0;
    ADCHSbits.CH0SB=0;
    ADCSSL=0b0000000100000000; // RB8 ADC ON
    ADCON1bits.ASAM=1;
    IFS0bits.ADIF=1;
    IEC0bits.ADIE=1;
}
 */
