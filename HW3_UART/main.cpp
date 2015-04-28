/*Program Example 7.9: Sets the mbed up for async communication, and exchanges data with a
similar node, sending its own switch positions, and displaying those of the other.*/

#include "mbed.h"

Serial async_port(p9, p10); //set up TX and RX on pins 9 and 10

DigitalOut led1(LED1); //red led
DigitalOut led2(LED2); //green led
DigitalOut led3(LED3); //red led
DigitalOut led4(LED4); //green led

DigitalOut strobe(p7); //a strobe to trigger the scope

unsigned char mode;
unsigned char led;

char switch_word ; //the word we will send

char recd_val; //the received value

void send_word()
{
	//Set up the word to be sent, by testing switch inputs

	printf("Enter led: 0 - All LEDs, 1 - LED1, 2 - LED2, 3 - LED3\r\n");
	scanf("%u", &led);

	switch_word=0xa0; //set up a recognisable output pattern
	switch(led)
	{
		case 0:
			//switch_word=switch_word|0x01;
			break;
		case 1:
			switch_word=switch_word|0x01;
			break;
		case 2:
			switch_word=switch_word|0x02;
			break;
		case 3:
			switch_word=switch_word|0x03;
			break;
    default:
			break;
	}

	strobe =1; //short strobe pulse

	wait_us(10);

	strobe=0;

	async_port.putc(switch_word); //transmit switch_word
}

void recv_word()
{
	//set leds according to incoming word from slave
	led1=0; //preset both to 0
	led2=0;
	led3=0;
	led4=0;
  printf("Waiting to recv command\r\n");
  while(1)
  {
	if (async_port.readable()==1) //is there a character to be read?
	{

		recd_val=async_port.getc(); //if yes, then read it
		break;

	}
	}


	recd_val=recd_val&0x03; //AND out unwanted bits

	switch(recd_val)
	{
		case 0:
			led1 = 1;
			led2 = 1;
			led3 = 1;
			led4 = 1;
			break;
		case 1:
			led1 = 1;
			break;
		case 2:
			led2 = 1;
			break;
		case 3:
			led3 = 1;
			break;
    default:
			break;
	}


}
int main()
{

	async_port.baud(9600); //set baud rate to 9600 (ie default)


	//accept default format, of 8 bits, no parity

	printf("Enter mode: 0 - tx, 1 - rx\r\n");
	scanf("%u", &mode);

	while (1)
	{

		if(mode == 0)
		{
			send_word();
			recv_word();
		}
		else
		{
			recv_word();
			send_word();
		}

	}
}
