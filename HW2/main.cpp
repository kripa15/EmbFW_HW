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

#define SYS_TICK_CTRL					((volatile unsigned int *)(0xE000E010) )
#define SYS_TICK_LOAD					((volatile unsigned int *)(0xE000E014) )
#define SYS_TICK_VAL					((volatile unsigned int *)(0xE000E018) )


#define TOGGLE_FREQ  1MHz


#define BUF_LEN  2048
#define MASK  ((unsigned char )(1))

#define DELAY_100MHZ 10
#define DELAY_50MHZ  20
#define DELAY_16MHZ  60

unsigned int delay_dont_opt;

unsigned char buffer[BUF_LEN];
// Toggles at 50MHz for 40 cycles and then there is a 3 times long half cycle 
// Introduced by branch

void delay_50ns(unsigned int count)
{
	unsigned int i;
	for( i=0 ; i<count ; i++ )
	{
		delay_dont_opt += i;
	}
}

/*
 Delay function based on SysTickTimer - counts down every CPU cycle (10ns).
 In the -O3 optimization mode this delay function seems to get inlined.
 Thus there is no function call/return overhead
 The overhead within the loop is about 8 instructions, and one branch
 So a guesstimate is made and 9 cycles are reduced from each loop/microsecond,
 ie., 91 cycles.
*/
void delay_us(unsigned int us)
{
	unsigned int i;
	for( i=0 ; i<us ; i++)
  {
		*SYS_TICK_LOAD = 94 ;//- overhead;
		*SYS_TICK_CTRL = 0x5;
		*SYS_TICK_LOAD = 0; 
		while(*SYS_TICK_VAL != 0);
  }
	
}

void toggle_gpio_50MHz(void)
{

	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;

	}

}

// Toggles at 25MHz for 10 cycles and then there is a 1.5 times long half cycle 
// Introduced by branch
void toggle_gpio_25MHz(void)
{

	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
		// CYCLE 1
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOCLR2 = MASK;
	}

}

/* Function that toggles GPIO P0.pin6 at 16.667 MHz
  which is the fastest possible 50-50 dutycycle frequency
  that is achievable with mbed runing at 96 MHz (10ns time period) */
void toggle_gpio_16MHz(void)
{

	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
    // GPIO is kept SET for 3 cycles, to balance 
    // 2 cycles of CLR state during branch to the 
    // beginning of the loop.
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
  
		*FIOCLR2 = MASK;
	}

}

/* Function that toggles GPIO P0.pin6 at 16.667 MHz
  which is the fastest possible 50-50 dutycycle frequency
  that is achievable with mbed runing at 96 MHz (10ns time period) */
void toggle_gpio_4MHz(void)
{

	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
    // GPIO is kept SET for 3 cycles, to balance 
    // 2 cycles of CLR state during branch to the 
    // beginning of the loop.
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
		*FIOSET2 = MASK;
  
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;
		*FIOCLR2 = MASK;

	}

}

/* Toggles GPIO any freq from 0.5 MHz , 
 with some extra (4 ns + 2* wait fn call ) overhead per cycle */
void toggle_gpio_delay(unsigned int us)
{

	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
    // 2 extra set operations to match 
    // 2 cycles stall due to branch
		*FIOSET2 = MASK;
		*FIOSET2 = MASK; 
		*FIOSET2 = MASK;
		delay_us(us);
		*FIOCLR2 = MASK;
		delay_us(us);
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
	register unsigned char reg9;
	register unsigned char reg10;

	volatile unsigned char* FIOPIN1 = &LPC_GPIO0->FIOPIN1;

  LPC_GPIO0->FIOMASK1 = ~(MASK);
  LPC_GPIO0->FIODIR1 = 0;


	reg1 = *FIOPIN1;
	reg2 = *FIOPIN1;
	reg3 = *FIOPIN1;
	reg4 = *FIOPIN1;
	reg5 = *FIOPIN1;
	reg6 = *FIOPIN1;
	reg7 = *FIOPIN1;
	reg8 = *FIOPIN1;
  reg9 = *FIOPIN1;
  reg10 = *FIOPIN1;


	buf[0] = reg1;
	buf[1] = reg2;
	buf[2] = reg3;
	buf[3] = reg4;
	buf[4] = reg5;
	buf[5] = reg6;
	buf[6] = reg7;
	buf[7] = reg8;
	buf[8] = reg9;
  buf[9] = reg10;

	return ;
}

void sample_gpio_50MHz(unsigned char *buf)
{
	register unsigned char reg1;
	volatile unsigned char* FIOPIN1 = &LPC_GPIO0->FIOPIN1;
 

  LPC_GPIO0->FIOMASK1 = ~(MASK);
  LPC_GPIO0->FIODIR1 = 0;

	reg1 = *FIOPIN1;
	buf[0] = reg1;
	reg1 = *FIOPIN1;
	buf[1] = reg1;
	reg1 = *FIOPIN1;
	buf[2] = reg1;
	reg1 = *FIOPIN1;
	buf[3] = reg1;
	reg1 = *FIOPIN1;
	buf[4] = reg1;
	reg1 = *FIOPIN1;
	buf[5] = reg1;
	reg1 = *FIOPIN1;
	buf[6] = reg1;
	reg1 = *FIOPIN1;
	buf[7] = reg1;
	reg1 = *FIOPIN1;
	buf[8] = reg1;
	reg1 = *FIOPIN1;
	buf[9] = reg1;
	reg1 = *FIOPIN1;
	buf[10] = reg1;
	reg1 = *FIOPIN1;
	buf[11] = reg1;
	reg1 = *FIOPIN1;
	buf[12] = reg1;
	reg1 = *FIOPIN1;
	buf[13] = reg1;
	reg1 = *FIOPIN1;
	buf[14] = reg1;
	reg1 = *FIOPIN1;
	buf[15] = reg1;
	reg1 = *FIOPIN1;
	buf[16] = reg1;
	reg1 = *FIOPIN1;
	buf[17] = reg1;
	reg1 = *FIOPIN1;
	buf[18] = reg1;
	reg1 = *FIOPIN1;
	buf[19] = reg1;
	reg1 = *FIOPIN1;
	buf[20] = reg1;
	reg1 = *FIOPIN1;
	buf[21] = reg1;
	reg1 = *FIOPIN1;
	buf[22] = reg1;
	reg1 = *FIOPIN1;
	buf[23] = reg1;
	return ;
}

void sample_gpio_16MHz(unsigned char *buf, int buf_len)
{
	int i;
	volatile unsigned char* FIOPIN1 = &LPC_GPIO0->FIOPIN1;


  LPC_GPIO0->FIOMASK1 = ~(MASK);
  LPC_GPIO0->FIODIR1 = 0;
	for(i=0 ; i<buf_len ; i++)
	{

		buffer[i] = *FIOPIN1;

	}

}


void sample_gpio_delay(unsigned int us, unsigned char *buf, int buf_len)
{
	int i;
	volatile unsigned char* FIOPIN1 = &LPC_GPIO0->FIOPIN1;

  LPC_GPIO0->FIOMASK1 = ~(MASK);
  LPC_GPIO0->FIODIR1 = 0;
	for(i=0 ; i<buf_len ; i++)
	{

		buffer[i] = *FIOPIN1;
		delay_us(us);
	}

}


// function that takes buf_len samples stored in the array, and computes the average
// to estimate input frequency
float compute_input_freq( unsigned char* buf, unsigned int buf_len, unsigned int delay_ns )
{

  unsigned int sample_length;
  unsigned int sample_count;
  unsigned int toggle_count;
  unsigned int cycle_count;
  float input_freq;
  unsigned int leading_samples;
  unsigned int i = 0;
	/*
	printf("\r\n");
  for (i=0 ; i<buf_len; i++)
	{
		printf("%x ", buf[i]);

	}
  printf("\r\n");
	*/
  i = 0;
  if(delay_ns >= 1000)
	{
		delay_ns+=40;
	}
	sample_length = delay_ns; // sample length in ns



  // skip the leading bits till the first toggle
  while(buf[i] == buf[i+1] && (++i < buf_len -1));
  
  leading_samples = i+1;
  i = i+1;
  toggle_count = 0;
  cycle_count = 0;
  sample_count = 0;
  //printf("start sample_count %d\r\n",  leading_samples);
  while( i< buf_len-1 )
	{
		if(buf[i] != buf[i+1])
		{
			toggle_count++;
		  // store the most recent even toggle count
		  // the final value of sample_count is used to compute freq    
		  if(toggle_count%2 == 0 && toggle_count >0)
		  {
				cycle_count = toggle_count/2;
		    sample_count = i+1;
		    
			}
		}
    i++;

	}
  if(sample_count>leading_samples)
	{
		sample_count = sample_count - leading_samples;
	}
	// there were cycle_count cycles in the duration sample_length*sample_count.
  // thus freq in us is:

  if(sample_length !=0 && sample_count !=0)
	{
  	input_freq = ((float)(cycle_count)/(float)(sample_count*sample_length)) * 1000000000;
		if(buf_len == BUF_LEN)
		{
		  //printf(" sample count = %u, cycle_count = %u, sample_length = %u\r\n", sample_count, cycle_count, sample_length);
		}
	}
	else
	{
		input_freq = 0;
	}
	return input_freq;

}

void sample_input_signal(unsigned int delay_ns, unsigned int sample_cnt)
{
	unsigned char* 					p = buffer;
	unsigned int 						input_freq_cnt = 0;
	float        						input_freq;
	float        						freq_sum = 0;
  unsigned int i;
  if(delay_ns<=20)
  {
			//printf("fast sample \r\n");
			while(p < &buffer[BUF_LEN - 1]) 
			{
				if(delay_ns ==  DELAY_50MHZ )
				{
					sample_gpio_50MHz(p);
				}
				else
				{
					sample_gpio_100MHz(p);
				}
				p += sample_cnt;
			}

	    // get average freq.
	    p = buffer;
	    input_freq = 0;
			while(p < &buffer[BUF_LEN - 1]) 
			{
	      input_freq = compute_input_freq(p, sample_cnt, delay_ns);
				if(input_freq !=0)
				{
					freq_sum += input_freq;
	        input_freq_cnt++;
				}
				p += sample_cnt;
			}
	}
	else
	{
			// take buf_len samples 100 times and compute average of all 100 freq estimations
      //printf("sample delay\r\n");
		  for ( i=0 ; i<100 ; i++) 
			{
				if(delay_ns >=1000)
				{
					sample_gpio_delay(delay_ns/1000, buffer, BUF_LEN);
          
				} 
				else if (delay_ns ==  DELAY_16MHZ )
				{
					sample_gpio_16MHz(buffer, BUF_LEN);
				}
			  input_freq = compute_input_freq(buffer, BUF_LEN, delay_ns);
				if(input_freq !=0)
				{
					freq_sum += input_freq;
		      input_freq_cnt++;
				}
			}
   input_freq = freq_sum/input_freq_cnt;
	}
  

	printf( "Input frequency estimate = %f Hz\r\n\r\n", input_freq);

}

/*Select sampling rate function */
void sel_sample_rate()
{

	unsigned int 						delay_ns = 0;
  unsigned int            delay_us_i;
  unsigned char           sample_freq_sel;
  unsigned int            sample_freq; 
  float                   delay_us_f;

  while(1)
	{
	do
	{
	printf ("\r\n\r\nEnter freq sel 0: 50 MHz, 1: 100 MHz, 2: 16MHz, 3: freq in Hz (< 500000)\r\n");
	scanf("%hhu",&sample_freq_sel);
	}while (sample_freq_sel > 3);

	switch(sample_freq_sel)
	{
		case 0: // 50000000 Hz
			delay_ns =  DELAY_50MHZ ;
      sample_input_signal(delay_ns, 24);

			break;
		case 1: // 100000000 Hz
	      delay_ns =  DELAY_100MHZ ;	
        sample_input_signal(delay_ns, 10);
				break;
		case 2: // 16MHz
	      delay_ns =  DELAY_16MHZ ;	
        sample_input_signal(delay_ns, BUF_LEN);
				break;
		case 3: // Any other rate

	    do
			{
				printf ("\r\n\r\nEnter freq in Hz (< 500000)\r\n");
				scanf("%u",&sample_freq);
			}while(sample_freq<1 || sample_freq > 500000);

			delay_us_f = 1000000/(sample_freq*2);
			delay_us_i = (unsigned int) delay_us_f;
			printf(" sample_freq = %u, delay = %u, delay_f=%f\r\n", sample_freq, delay_us_i, delay_us_f); 
      sample_input_signal(delay_us_i*1000, BUF_LEN);
			break;
    default:
			break;
	}

	}
}

void toggle_gpio_pin()
{
  unsigned int            delay_us_i;
  unsigned char           freq_sel;
  unsigned int            freq; 
  float                   delay_us_f;
  float                   actual_freq;

		do
		{
		printf ("\r\n\r\nEnter freq sel 0: 16.67 MHz, 1: 25 MHz, , 2: 4MHz, 3: freq in Hz (< 500000)\r\n");
		scanf("%hhu",&freq_sel);
		}while (freq_sel > 4);
		switch(freq_sel)
		{
			case 0: freq = 16666667;
				printf("toggling at 16666667 Hz\r\n");
				toggle_gpio_16MHz();
				break;
			case 1: freq = 25000000;
				printf("toggling at 25000000 Hz\r\n");
				toggle_gpio_25MHz();
				break;
			case 2: freq = 4166667;
				printf("toggling at 4166667 Hz\r\n");
				toggle_gpio_4MHz();
				break;
      case 4:
				printf("toggling at 50000000 Hz\r\n");
				toggle_gpio_50MHz();
				break;
			case 3: 
		    do
				{
				printf ("\r\n\r\nEnter freq in Hz (< 500000)\r\n");
				scanf("%u",&freq);
				}while(freq<1 || freq > 500000);
				delay_us_f = 1000000/(freq*2);
				delay_us_i = (unsigned int) delay_us_f;
        actual_freq = 1000000/(delay_us_i*2);
				printf(" freq = %f, delay = %u, delay_f=%f\r\n", actual_freq, delay_us_i, delay_us_f); 
				toggle_gpio_delay(delay_us_i);
				break;
    default:
        break;
		}
   
}
__attribute__((optimize("00"))) int main(void)
{ 

	//unsigned char* buf = (unsigned char*)0x10000aa0;

  unsigned char           is_generator;
  volatile unsigned int*  PINMODE0;
	
  PINMODE0  = (volatile unsigned int*) 0x4002C040;
  *PINMODE0 = 0xFFFFFFFF;


  do
	{
		printf ("\r\nEnter 0 for signal generation, 1 for sampling:\r\n");
		scanf("%hhu",&is_generator);
	}while (!((is_generator == 0)||(is_generator == 1)));

  if(is_generator == 0) // signal generating mode
	{
		 toggle_gpio_pin();
	}
	else  // sampling mode
	{	
		sel_sample_rate();
	}
  

	return 0;
}
