// HW01
// Assigned Dip pin# 29 
// port 0, pin 5 
#include<mbed.h>
#include<stdint.h>
#include<LPC17xx.h>
#include<stdio.h>
/* GPIOs                                                                      */
#define LPC_GPIO_BASE         (0x2009C000UL)

/*!< Defines 'read / write' permissions              */
#define     __IO    volatile             
#define     __O    volatile             


#define LPC_GPIO_PORT_OFFSET        (0x20UL)
#define LPC_GPIO0_BASE        (LPC_GPIO_BASE + 0x00000)
#define LPC_GPIO1_BASE        (LPC_GPIO_BASE + 0x00020)
#define LPC_GPIO2_BASE        (LPC_GPIO_BASE + 0x00040)
#define LPC_GPIO3_BASE        (LPC_GPIO_BASE + 0x00060)
#define LPC_GPIO4_BASE        (LPC_GPIO_BASE + 0x00080)

#define LPC_GPIO0             ((LPC_GPIO_TypeDef      *) LPC_GPIO0_BASE    )
#define LPC_GPIO1             ((LPC_GPIO_TypeDef      *) LPC_GPIO1_BASE    )
#define LPC_GPIO2             ((LPC_GPIO_TypeDef      *) LPC_GPIO2_BASE    )
#define LPC_GPIO3             ((LPC_GPIO_TypeDef      *) LPC_GPIO3_BASE    )
#define LPC_GPIO4             ((LPC_GPIO_TypeDef      *) LPC_GPIO4_BASE    )

#define TOGGLE_FREQ  1MHz
/*
#if (TOGGLE_FREQ == 1Hz)
#define DELAY 1000000
#elif (TOGGLE_FREQ == 10Hz)
#define DELAY 100000
#elif (TOGGLE_FREQ == 100Hz)
#define DELAY 
*/
#define BUF_LEN  1024

unsigned char buffer[BUF_LEN];
// Toggles at 50MHz for 40 cycles and then there is a 3 times long half cycle 
// Introduced by branch
void toggle_gpio_50MHz(void)
{
	register unsigned char mask = (1 << 2);
	volatile unsigned char* FIOSET2 = &LPC_GPIO1->FIOSET2;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO1->FIOCLR2;

	LPC_GPIO1->FIODIR2 = mask;
	while (1) 
	{ 
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;

	}

}

// Toggles at 25MHz for 10 cycles and then there is a 1.5 times long half cycle 
// Introduced by branch
void toggle_gpio_25MHz(void)
{

	register unsigned char mask = (1 << 2);
	volatile unsigned char* FIOSET2 = &LPC_GPIO1->FIOSET2;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO1->FIOCLR2;

	LPC_GPIO1->FIODIR2 = mask;
	while (1) 
	{ 
		// CYCLE 1
		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
		*FIOCLR2 = mask;

		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;
	}

}

// Function that toggles GPIO P1.pin6 at 16.667 MHz
// which is the fastest possible 50-50 dutycycle frequency
// that is achievable with mbed runing at 96 MHz (10ns time period)
void toggle_gpio_16MHz(void)
{

	register unsigned char mask = (1 << 2);
	volatile unsigned char* FIOSET2 = &LPC_GPIO1->FIOSET2;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO1->FIOCLR2;

	LPC_GPIO1->FIODIR2 = mask;
	while (1) 
	{ 
		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOSET2 = mask;
		*FIOCLR2 = mask;

	}

}

//Toggles GPIO  any freq from 0.5 MHz , 
//with some extra (4 ns + 2* wait fn call ) overhead per cycle 
void toggle_gpio_delay(unsigned int delay_us)
{

	register unsigned char mask = (1 << 2);
	volatile unsigned char* FIOSET2 = &LPC_GPIO1->FIOSET2;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO1->FIOCLR2;

	LPC_GPIO1->FIODIR2 = mask;
	while (1) 
	{ 
		*FIOSET2 = mask;
		*FIOSET2 = mask; // 2 extra set operations to match 2 cycles stall due to branch
		*FIOSET2 = mask;
		wait_us(delay_us);
		*FIOCLR2 = mask;
		wait_us(delay_us);
	}
}
void sample_gpio_100MHz(unsigned char *buf)
{
 register unsigned char reg1;
 register unsigned char reg2;
 register unsigned char reg3;
 register unsigned char reg4;
 register unsigned char reg5;
 register unsigned char reg6;
 register unsigned char reg7;
 register unsigned char reg8;


 reg1 = LPC_GPIO0->FIOPIN0;
 reg2 = LPC_GPIO0->FIOPIN0;
 reg3 = LPC_GPIO0->FIOPIN0;
 reg4 = LPC_GPIO0->FIOPIN0;
 reg5 = LPC_GPIO0->FIOPIN0;
 reg6 = LPC_GPIO0->FIOPIN0;
 reg7 = LPC_GPIO0->FIOPIN0;
 reg8 = LPC_GPIO0->FIOPIN0;

 buf[0] = reg1;
 buf[1] = reg2;
 buf[2] = reg3;
 buf[3] = reg4;
 buf[4] = reg5;
 buf[5] = reg6;
 buf[6] = reg7;
 buf[7] = reg8;
 return ;
}

void sample_gpio_50MHz(unsigned char *buf)
{
 register unsigned char reg1;
 register unsigned char reg2;
 register unsigned char reg3;
 register unsigned char reg4;
 register unsigned char reg5;
 register unsigned char reg6;
 register unsigned char reg7;
 register unsigned char reg8;
 register unsigned char reg9;

 reg1 = LPC_GPIO0->FIOPIN0;
 buf[0] = reg1;
 reg2 = LPC_GPIO0->FIOPIN0;
 buf[1] = reg2;
 reg3 = LPC_GPIO0->FIOPIN0;
 buf[2] = reg3;
 reg4 = LPC_GPIO0->FIOPIN0;
buf[3] = reg4;
 reg5 = LPC_GPIO0->FIOPIN0;
 buf[4] = reg5;
 reg6 = LPC_GPIO0->FIOPIN0;
 buf[5] = reg6;
 reg7 = LPC_GPIO0->FIOPIN0;
 buf[6] = reg7;
 reg8 = LPC_GPIO0->FIOPIN0;
 buf[7] = reg8;
 return ;
}

void sample_gpio_delay(unsigned int delay_us, unsigned char *buf)
{

// register unsigned char mask = (1 << 2);
 register unsigned char mask = (1 << 6);
// volatile 
register unsigned char reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8;


 // set gpio port 0 as input
 LPC_GPIO0->FIODIR0 = 0;
 
 // read into registers 
 reg1= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg2= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg3= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg4= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg5= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg6= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg7= LPC_GPIO0->FIOPIN0;
 wait_us(delay_us);
 reg8= LPC_GPIO0->FIOPIN0;


 // read into array
 buf[0] = reg1;
 buf[1] = reg2;
 buf[3] = reg3;
 buf[4] = reg4;
 buf[5] = reg5;
 buf[6] = reg6;
 buf[7] = reg7;
 buf[8] = reg8;


}
/*

// 50 MHz sampling is achieved for 10 cycles.
// as gap between subsequent samples was 20ns, per pipeline evaluation
__inline void sample_gpio_asm_50() 
{
__asm__ __volatile__(
  //"LDR     R0, =0x2009C014\n\t"
  "push {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11}\n\t"
	
  "LDR     R0, =0x10000a90\n\t"
  "LDR     R1, =0x55\n\t"
	"STRB    R1,[R0]\n\t"
  "LDR     R1, [R0]\n\t"
  "LDR     R2, [R0]\n\t"
  "LDR     R3, [R0]\n\t"
  "LDR     R4, [R0]\n\t"
  "LDR     R5, [R0]\n\t"
  "LDR     R6, [R0]\n\t"
  "LDR     R7, [R0]\n\t"
  "LDR     R8, [R0]\n\t"
  "LDR     R9, [R0]\n\t"
  "LDR     R10, [R0]\n\t"
  "LDR     R11, [R0]\n\t"

  "LDR     R0, =0x10000aa0\n\t" // storing to the end of heap
  "STRB     R1, [R0]\n\t"
  "STRB     R2, [R0, #1]\n\t"
  "STRB     R3, [R0, #2]\n\t"
  "STRB     R4, [R0, #3]\n\t"
  "STRB     R5, [R0, #4]\n\t"
  "STRB     R6, [R0, #5]\n\t"
  "STRB     R7, [R0, #6]\n\t"
  "STRB     R8, [R0, #7]\n\t"
  "STRB     R9, [R0, #8]\n\t"
  "STRB     R10, [R0, #9]\n\t"
  "STRB     R11, [R0, #10]\n\t"
  "pop {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11}\n\t"
);
}


// 50 MHz sampling is achieved for 10 cycles.
// as gap between subsequent samples was 20ns, per pipeline evaluation
void sample_gpio_asm_25() 
{
__asm__ __volatile__(
  "LDR     R0, =0x2009C014\n\t"
	
   // test pattern loading
	//"LDR     R0, =0x10000a90\n\t"
  //"LDR     R1, =0x55\n\t"
	//"STRB    R1,[R0]\n\t"

  "LDR     R1, [R0]\n\t"
	"nop\n\t"
  "LDR     R2, [R0]\n\t"
	"nop\n\t"
  "LDR     R3, [R0]\n\t"
	"nop\n\t"
  "LDR     R4, [R0]\n\t"
	"nop\n\t"
  "LDR     R5, [R0]\n\t"
	"nop\n\t"
  "LDR     R6, [R0]\n\t"
	"nop\n\t"
  "LDR     R7, [R0]\n\t"
	"nop\n\t"
  "LDR     R8, [R0]\n\t"
	"nop\n\t"

  "LDR     R0, =0x10000aa0\n\t" // storing to the end of heap
  "STRB     R1, [R0]\n\t"
  "STRB     R2, [R0, #1]\n\t"
  "STRB     R3, [R0, #2]\n\t"
  "STRB     R4, [R0, #3]\n\t"
  "STRB     R5, [R0, #4]\n\t"
  "STRB     R6, [R0, #5]\n\t"
  "STRB     R7, [R0, #6]\n\t"
  "STRB     R8, [R0, #7]\n\t"
  "STRB     R9, [R0, #8]\n\t"
  "STRB     R10, [R0, #9]\n\t"
  "STRB     R11, [R0, #10]\n\t"

);
}
*/

// function that takes buf_len samples stored in the array, and computes the average
// to estimate input frequency
unsigned int compute_input_freq( unsigned char* buf, unsigned int buf_len, unsigned int sample_freq )
{

  unsigned int sample_length;
  unsigned int toggle_count;
  unsigned int input_freq;
  int i;

  
	sample_length = 1000000000/sample_freq; // sample length in ns
  for( i=0 ; i< buf_len-1 ; i++)
	{
		if(buf[i] != buf[i+1])
			toggle_count++;
	}
	
	// there were toggle_count/2 cycles in the duration sample_length*buflen.
  // thus freq in us is:
  if(sample_length !=0 && buf_len !=0)
	{
  	input_freq = ((toggle_count/2)*1000000000)/(buf_len*sample_length);
	}
	else
	{
		input_freq = 0;
	}
	return input_freq;

}


int main(void)
{ 

	//unsigned char* buf = (unsigned char*)0x10000aa0;
  unsigned int i, delay_us_i;
  unsigned int  freq; 
  float delay_us_f;
  unsigned char *p = buffer;
  unsigned char is_generator;

  do
	{
		printf ("\r\n\r\nEnter 0 for signal generation, 1 for sampling:\r\n");
		scanf("%u",&is_generator);
	}while (!((is_generator == 0)||(is_generator == 1)));
	
  do
	{
  printf ("\r\n\r\nEnter freq in Hz\r\n");
  scanf("%u",&freq);
	}while (freq == 0);
  
  delay_us_f = 1000000/(freq*2);
  delay_us_i = (unsigned int) delay_us_f;
  printf(" freq = %u, delay = %u, delay_f=%f\r\n", freq, delay_us_i, delay_us_f);

  if(is_generator == 0) // signal generating mode
	{
		if(delay_us_i == 0)
		{
			if(freq == 166666667)
			{
				printf("toggling at 16666667 Hz\r\n");
				toggle_gpio_16MHz();
			}
			else if (freq == 25000000)
			{
				printf("toggling at 25000000 Hz\r\n");
				toggle_gpio_25MHz();
			}
			else if (freq == 50000000)
			{
				printf("toggling at 50000000 Hz\r\n");
				toggle_gpio_50MHz();
			}
		}
		else
		{
			toggle_gpio_delay(delay_us_i);
		}
	}
	else  // sampling mode
	{	
		delay_us_i *= 2;
		if(delay_us_i == 0)
		{
			if(freq == 100000000) // 100 MHz sampling
			{		
				while(p < &buffer[BUF_LEN - 1]) 
				{

					sample_gpio_100MHz(p);
					p += 8;
				}
			}
			else if(freq == 50000000) //
			{
				while(p < &buffer[BUF_LEN - 1]) 
				{
					sample_gpio_50MHz(p);
					p += 8;
				}
			}
		 	
		}
		else
		{
			while(p < &buffer[BUF_LEN - 1]) 
			{
				sample_gpio_delay(delay_us_i, p);
				p+=8;
			}
		}
	
		printf( "Input frequency estimate = %lu", compute_input_freq(buffer, BUF_LEN, freq));
		
	}
	printf("byebye");
	return 0;
}
