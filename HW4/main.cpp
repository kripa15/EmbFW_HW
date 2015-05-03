/*Program Example 7.9: Sets the mbed up for async communication, and exchanges data with a
similar node, sending its own switch positions, and displaying those of the other.*/

#include "mbed.h"

Serial async_port(p9, p10); //set up TX and RX on pins 9 and 10

Serial pc(USBTX, USBRX); // tx, rx 
DigitalOut ledArr[4] = {DigitalOut(LED1), DigitalOut(LED2), DigitalOut(LED3), DigitalOut(LED4)}; 
DigitalOut led1(LED1); 
DigitalOut led2(LED2); 
DigitalOut led3(LED3); 
DigitalOut led4(LED4); 

/*Disaplay Hex digit on LEDs*/
void DisplayLed(int ch) 
{ 
    int i=0;

    if (ch>='0' && ch<='9')
        ch-='0';
    else if (ch>='A' && ch<='F') {
        ch-='A';
        ch+=10;
    } else if (ch>='a' && ch<='f') {
        ch-='a';
        ch+=10;
    } else
        ch=0;

    for (i=0; i<4; i++) { 
        if(ch& (1<<i))
            ledArr[i] = 1; 
        else
            ledArr[i] = 0;
    } 
} 

/* Non blocking read of character from terminal.
If entered char is Hexadecimal, it is sent to 
UART */
void send_word()
{
	//Set up the word to be sent, by testing switch inputs

  char ch;

  if(pc.readable()==1)
  {
	  led1=0; led2=0; led3=0; led4=0;    

    ch = pc.getc(); 
    pc.putc(ch);
    if( (ch>='0' && ch<='9') || (ch>='A' && ch<='F') || (ch>='a' && ch<='f') )
    {
      async_port.putc(ch);
    }
    pc.printf("\r\nEnter:");
  }
	
}

/* Non blocking read of character from UART.
Character is sent to Hex LED display function.*/
void recv_word()
{
	//set leds according to incoming word from slave
  char recd_val;
	if (async_port.readable()==1) //is there a character to be read?
	{
		recd_val=async_port.getc(); //if yes, then read it
    DisplayLed(recd_val);
	}
}
/* Loops infinitely looking for input from UART & PC serial ports.*/
int main()
{
	async_port.baud(9600); //set baud rate to 9600 (ie default)
	//accept default format, of 8 bits, no parity

  pc.printf("\r\nEnter:");
	while (1)
	{
			send_word();
			recv_word();
	}
}
