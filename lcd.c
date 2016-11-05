#include"header.h"

void LcdInit(void)
{
/* Uncomment Lines for 8-bit mode operation
 * send_cmd(0X01);
    delay(5);
    send_cmd(0X38);
    delay(5);
    send_cmd(0X08);
    delay(5);
    send_cmd(0X01);
    delay(5);
    send_cmd(0X06);
    delay(5);
    send_cmd(0X0C);
    delay(5);
    send_cmd(0X0F);
    delay(5);
 */
    send_cmd(0X33);
    delay(2);
    send_cmd(0X32);
    delay(2);
    send_cmd(0X28);
    delay(2);
    send_cmd(0X0E);
    delay(2);
    send_cmd(0X01);
    delay(2);
    send_cmd(0X06);
    delay(2);
    send_cmd(0X80);
    delay(2);
}
void send_cmd(unsigned char cmd)
{
    /*
    DATA_PORT = cmd;
    delay(2);
    RS = 0;
    EN = 1;
    delay(1);
    EN = 0;
    delay(5);
    */
    DATA_PORT = (cmd&0XF0);
    delay(2);
    RS = 0;
    EN = 1;
    delay(1);
    EN = 0;
    DATA_PORT = ((cmd<<4)&0XF0);
    delay(2);
    RS = 0;
    EN = 1;
    delay(1);
    EN = 0;
    delay(5);
}
void send_data(unsigned char data)
{
    /*
    RS = 1;
    DATA_PORT = data;
    delay(2);
    EN = 1;
    delay(1);
    EN = 0;
    delay(5);
    */
    DATA_PORT = (data&0XF0);
    delay(2);
    RS = 1;
    EN = 1;
    delay(1);
    EN = 0;
    DATA_PORT = ((data<<4)&0XF0);
    delay(2);
    RS = 1;
    EN = 1;
    delay(1);
    EN = 0;
    delay(5);
}
void Lcd_Text(char *string)
{
    unsigned int i=0;
    while(*(string+i) != '\0')
    {
        send_data(*(string+i));
        i++;
    }
    delay(2);
}
void Lcd_Integer(unsigned long int value)
{
    char str[10];
    unsigned long int val;
    val = value;
    sprintf(str,"%ld",val);
    Lcd_Text(str);
    delay(2);
}
int Gotoxy(int x, int y)
{
    int i=0;
    if(x<1)
        x = 1;
    if(y<1)
        y = 1;
    if(x>20)
        x = 20;
    if(y>4)
        y = 4;
    
    switch(y)
    {
        case 1:
            send_cmd(0X80);
            break;
        case 2:
            send_cmd(0XC0);
            break;
        case 3:
            send_cmd(0X94);
            break;
        case 4:
            send_cmd(0XD4);
            break;
        default:
            break;
    }
    delay(1);
    for(i=1;i<x;i++)
    {
        send_cmd(0X14);
        delay(1);
    }
    return 0;
}
