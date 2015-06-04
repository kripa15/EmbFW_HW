// HW02
// Assigned Dip pin# 6 
// port 0, pin 8 
#include<stdint.h>
#include<LPC17xx.h>
#include<stdio.h>
//#define DBG_PRINT 1
/* GPIOs                                             */

#define LPC_GPIO_BASE         (0x2009C000UL)
      
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


#define BUF_LEN  4096
#define MASK  ((unsigned char )(1))

#define SAMPLE_COUNT_100MHz 10
#define SAMPLE_COUNT_50MHz 10
#define SAMPLE_COUNT_25MHz  32 //10

#define DELAY_100MHZ 10
#define DELAY_50MHZ  20
#define DELAY_25MHZ  40
#define DELAY_16MHZ  60
#define SAMPLE_OVERHEAD 50 // 80 ns or 8 cycles extra overhead for each time the sample_gpio_delay loops.
                           // So this delay is taken into account during freq calculation.
#define SYSTICK_DELAY_1US 90// Systick decrements once per cycle. 
                            // In O3 optimization, there are 9 cycles extra overhead every microsecon 
                            // introduced by the looping. Hence Systick is set to 90 instead of 99.

unsigned int delay_dont_opt;
unsigned char buffer[BUF_LEN];

/*
 Delay function based on SysTickTimer - counts down every CPU cycle (10ns).
 In the -O3 optimization mode this delay function seems to get inlined.
 Thus there is no function call/return overhead
 The overhead within the loop is about 11 instructions, and one branch
 So a guesstimate is made and 13 cycles are reduced from each loop/microsecond.
*/
void delay_us(unsigned int us)
{
	unsigned int i;
  //*SYS_TICK_CTRL = 0x0;
  unsigned int oh  = 13;
	for( i=0 ; i<us ; i++)
  {
		*SYS_TICK_LOAD = 86 - oh;//SYSTICK_DELAY_1US;//88 ;//- overhead;
		*SYS_TICK_CTRL = 0x5;
		*SYS_TICK_LOAD = 0; 
		while(*SYS_TICK_VAL != 0);
    oh = 0x0;  
  }
	*SYS_TICK_LOAD = 0;
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
__attribute__((optimize("align-loops=4"))) void toggle_gpio_25MHz(void)
{
	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
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

/* Function that toggles GPIO P0.pin8 at 16.667 MHz
  which is the fastest possible 50-50 dutycycle frequency
  that is achievable with mbed runing at 96 MHz (10ns time period) */
__attribute__((optimize("align-loops=4"))) void toggle_gpio_16MHz(void)
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

/* Function that toggles GPIO P0.pin8 at 4 MHz */
__attribute__((optimize("align-loops=4"))) void toggle_gpio_4MHz(void)
{
	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{
    /*  unsigned int register sys_tick_val; 

		*SYS_TICK_LOAD = 500 ;//- overhead;
		*SYS_TICK_CTRL = 0x5;
		*SYS_TICK_LOAD = 0; */

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
    //sys_tick_val = *SYS_TICK_VAL;
	}
}

__attribute__((optimize("align-loops=4"))) void toggle_gpio_8MHz(void)
{
	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1 = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{
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
	}
}

/* Toggles GPIO at frequencies <= 0.5 MHz */
void toggle_gpio_delay(unsigned int us)
{
	volatile unsigned char* FIOSET2 = &LPC_GPIO0->FIOSET1;
	volatile unsigned char* FIOCLR2 = &LPC_GPIO0->FIOCLR1;

	LPC_GPIO0->FIODIR1  = MASK;
  LPC_GPIO0->FIOMASK1 = ~(MASK);
	while (1) 
	{ 
    // 2 extra 'set' operations to match 
    // 2 cycles stall due to branch
		*FIOSET2 = MASK;
		*FIOSET2 = MASK; 
		*FIOSET2 = MASK;
		delay_us(us);
		*FIOCLR2 = MASK;
		delay_us(us);
	}
}
/*Samples GPIO at 100MHz*/
__attribute__((optimize("no-inline"))) void sample_gpio_100MHz(unsigned char *buf)
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
  LPC_GPIO0->FIODIR1  = 0;

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

/*Samples GPIO at 25 MHz*/
__attribute__((optimize("no-inline"))) void sample_gpio_25MHz(unsigned char *buf)
{
	register unsigned char reg1;
	register unsigned char reg2;
	register unsigned char reg3;
	register unsigned char reg4;
	volatile unsigned char* FIOPIN1 = &LPC_GPIO0->FIOPIN1; 

  LPC_GPIO0->FIOMASK1 = ~(MASK);
  LPC_GPIO0->FIODIR1 = 0;

	*SYS_TICK_LOAD = 500 ;//- overhead;
	*SYS_TICK_CTRL = 0x5;
	*SYS_TICK_LOAD = 0; 

	reg1 = *FIOPIN1;
	buf[0] = reg1;
	reg2 = *FIOPIN1;
	buf[1] = reg2;
	reg3 = *FIOPIN1;
	buf[2] = reg3;
	reg4 = *FIOPIN1;
	buf[3] = reg4;
	reg1 = *FIOPIN1;
	buf[4] = reg1;
	reg2 = *FIOPIN1;
	buf[5] = reg2;
	reg3 = *FIOPIN1;
	buf[6] = reg3;
	reg4 = *FIOPIN1;
	buf[7] = reg4;
	reg1 = *FIOPIN1;
	buf[8] = reg1;
	reg2 = *FIOPIN1;
	buf[9] = reg2;
	reg3 = *FIOPIN1;
	buf[10] = reg3;
	reg4 = *FIOPIN1;
	buf[11] = reg4;
	reg1 = *FIOPIN1;
	buf[12] = reg1;
	reg2 = *FIOPIN1;
	buf[13] = reg2;
	reg3 = *FIOPIN1;
	buf[14] = reg3;
	reg4 = *FIOPIN1;
	buf[15] = reg4;
	reg1 = *FIOPIN1;
	buf[16] = reg1;
	reg2 = *FIOPIN1;
	buf[17] = reg2;
	reg3 = *FIOPIN1;
	buf[18] = reg3;
	reg4 = *FIOPIN1;
	buf[19] = reg4;
	reg1 = *FIOPIN1;
	buf[20] = reg1;
	reg2 = *FIOPIN1;
	buf[21] = reg2;
	reg3 = *FIOPIN1;
	buf[22] = reg3;
	reg4 = *FIOPIN1;
	buf[23] = reg4;
	reg1 = *FIOPIN1;
	buf[24] = reg1;
	reg2 = *FIOPIN1;
	buf[25] = reg2;
	reg3 = *FIOPIN1;
	buf[26] = reg3;
	reg4 = *FIOPIN1;
	buf[27] = reg4;
	reg1 = *FIOPIN1;
	buf[28] = reg1;
	reg2 = *FIOPIN1;
	buf[29] = reg2;
	reg3 = *FIOPIN1;
	buf[30] = reg3;
	reg4 = *FIOPIN1;
	buf[31] = reg4;
  //printf ("SYS_TICK_VAL = %u\r\n", *SYS_TICK_VAL);
	return ;
}

/* Samples GPIO at 50 MHz - but still getting only 25 MHz, so needs further research */
__attribute__((optimize("no-inline"))) void sample_gpio_50MHz(unsigned char *buf)
{
  __asm__ __volatile__(
  "push {r4, r5, r6, r7, r8, r9, r10, r11}\n\t"
  "LDR     R2,=0x2009c000\n\t"
  "LDR     R3,=0x2009c015\n\t"
  "MOVS    r4,#254\n\t"
  "MOVS    R1,#0\n\t"
  "STRB    R4, [R2, #17]\n\t"
  "STRB    R1, [R2, #1]\n\t"
  ".align 2\n\t"
  "LDRB    R8, [R3, #0]\n\t"
  "LDRB    R9, [R0, #0]\n\t" // dummy load
  "LDRB    R9, [R3, #0]\n\t"
  "LDRB    R10, [R0, #0]\n\t" // dummy load
  "LDRB    R10, [R3, #0]\n\t"
  "LDRB    R11, [R0, #0]\n\t" // dummy load
  "LDRB    R11, [R3, #0]\n\t"
  "LDRB    R4, [R0, #0]\n\t" // dummy load
  "LDRB    R4, [R3, #0]\n\t"
  "LDRB    R5, [R0, #0]\n\t" // dummy load
  "LDRB    R5, [R3, #0]\n\t"
  "LDRB    R6, [R0, #0]\n\t" // dummy load
  "LDRB    R6, [R0, #0]\n\t"
  "LDRB    R7, [R0, #0]\n\t" // dummy load
  "LDRB    R7, [R0, #0]\n\t"

  "STRB    R8, [R0, #0]\n\t"
  "STRB    R9, [R0, #1]\n\t"
  "STRB    R10,[R0, #2]\n\t"
  "STRB    R11, [R0, #3]\n\t"
  "STRB    R4, [R0, #4]\n\t"
  "STRB    R5, [R0, #5]\n\t"
  "STRB    R6, [R0, #6]\n\t"
  "STRB    R7, [R0, #7]\n\t"

  "pop {r4, r5, r6, r7, r8, r9, r10, r11}\n\t"
  );
}

/*Samples GPIO at 16 MHz*/
__attribute__((optimize("align-loops=4"))) void sample_gpio_16MHz(unsigned char *buf, int buf_len)
{
	int i;
	volatile unsigned char* FIOPIN1 = &LPC_GPIO0->FIOPIN1;

  LPC_GPIO0->FIOMASK1 = ~(MASK);
  LPC_GPIO0->FIODIR1 = 0;
	*SYS_TICK_LOAD = 20000 ;//- overhead;
	*SYS_TICK_CTRL = 0x5;
	*SYS_TICK_LOAD = 0; 

	for(i=0 ; i<buf_len ; i++)
	{
		buffer[i] = *FIOPIN1;
	}
 // printf("sys_tick_val = %u \r\n", *SYS_TICK_VAL);
}

/*Samples GPIO at n*us delay - for sampling freq <= 0.5MHz*/
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

/* Function that takes buf_len samples stored in the array, and computes the average
 to estimate input frequency */
float compute_input_freq( unsigned char* buf, unsigned int buf_len, unsigned int delay_ns )
{
  unsigned int sample_length;
  unsigned int sample_count;
  unsigned int toggle_count;
  unsigned int cycle_count;
  float input_freq;
  unsigned int leading_samples;
  unsigned int i = 0;
#ifdef DBG_PRINT //== 1
	printf("\r\n");
  for (i=0 ; i<buf_len; i++)
	{
		printf("%x ", buf[i]);
	}
  printf("\r\n");
#endif	
  i = 0;
  // if delay >= 1us, take into account overhead
  // of the delay function looping 
  if(delay_ns >= 1000)
	{
		delay_ns+=SAMPLE_OVERHEAD;
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
#ifdef DBG_PRINT // == 1
		printf(" sample count = %u, cycle_count = %u, sample_length = %u\r\n", sample_count, cycle_count, sample_length);
#endif
	}
	else
	{
		input_freq = 0;
	}
	return input_freq;
}

float sample_input_signal(unsigned int delay_ns, unsigned int sample_cnt)
{
	unsigned char* 					p = buffer;
	unsigned int 						input_freq_cnt = 0;
	float        						input_freq;
	float        						freq_sum = 0;
  unsigned int i;
  // fast sampling case
  if(delay_ns<=DELAY_25MHZ)
  {
			//printf("fast sample \r\n");
			while(p < &buffer[BUF_LEN - 1]) 
			{
				if(delay_ns ==  DELAY_25MHZ )
				{ 
					sample_gpio_25MHz(p);
				}
				else if (delay_ns == DELAY_50MHZ  )
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
	else // sampling rate <= 500,000
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
	}
  if(input_freq_cnt >=5)
  {
    input_freq = freq_sum/input_freq_cnt;
  }
  else
  {
    input_freq = 0;
  }
  printf( "Input frequency estimate = %f Hz\r\n\r\n", input_freq);
  return input_freq;
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
	  printf ("\r\nEnter Sampling freq sel 0:100M, 1:50M, 2:25M, 3:16M, 4: freq in Hz <= 500000\r\n");
	  scanf("%hhu",&sample_freq_sel);
	  }while (sample_freq_sel > 4);

	  switch(sample_freq_sel)
	  {
		  case 0: // 100000000 Hz
	        delay_ns =  DELAY_100MHZ ;
          printf("  Sampling at 100MHz\r\n");	
          sample_input_signal(delay_ns, SAMPLE_COUNT_100MHz);
				  break;
		  case 1: // 50000000 Hz
	        delay_ns =  DELAY_50MHZ ;
          printf("  Sampling at 50MHz\r\n");	
          sample_input_signal(delay_ns, SAMPLE_COUNT_50MHz);
				  break;
		  case 2: // 50000000 Hz
			  delay_ns =  DELAY_25MHZ ;
        printf("  Sampling at 25MHz\r\n");
        sample_input_signal(delay_ns, SAMPLE_COUNT_25MHz);
			  break;
		  case 3: // 16MHz
	        delay_ns =  DELAY_16MHZ ;	
          printf("  Sampling at 16MHz\r\n");	
          sample_input_signal(delay_ns, BUF_LEN);
				  break;
		  case 4: // Any other rate
	      do
			  {
				  printf ("Enter freq in Hz =< 500000\r\n");
				  scanf("%u",&sample_freq);
			  }while(sample_freq<1 || sample_freq > 500000);

			  delay_us_f = 1000000/(sample_freq*2);
			  delay_us_i = (unsigned int) delay_us_f;
        delay_ns = delay_us_i*1000;
        sample_freq = 1000000000/delay_ns;
			  printf("  Sampling at %uHz, delay = %u, delay_f=%f\r\n", sample_freq, delay_us_i, delay_us_f);   
        sample_input_signal(delay_ns, BUF_LEN);
			  break;
      default:
			  break;
	  }
	}
}
/*
void sweep_and_sample()
{
	unsigned int 						delay_ns = 0;
  unsigned int            delay_us_i;
  float                   sample_freq; 
  float                   input_freq = 0;

  delay_ns =  DELAY_100MHZ ;	
  printf("Sampling at 100MHz\r\n");
  input_freq = sample_input_signal(delay_ns, SAMPLE_COUNT_100MHz);
  if(input_freq == 0)
  {
    delay_ns =  DELAY_25MHZ ;	
    printf("Sampling at 25MHz\r\n");  
    input_freq = sample_input_signal(delay_ns, SAMPLE_COUNT_25MHz);
  }
  if(input_freq == 0)
  {
    delay_ns =  DELAY_16MHZ ;
    printf("Sampling at 16MHz\r\n");
    input_freq = sample_input_signal(delay_ns, BUF_LEN);
  }
  delay_us_i = 1;
  while(input_freq == 0)
  {
    delay_ns = delay_us_i*1000;
    sample_freq = 1000000000/delay_ns;
    printf("Sampling at %fHz\r\n", sample_freq);
    input_freq = sample_input_signal(delay_ns, BUF_LEN);
    delay_us_i++;
    if(delay_us_i == 1000)
      break;
  }
  printf("Computed input freq = %f", input_freq);
}
*/
void toggle_gpio_pin()
{
  unsigned int            delay_us_i;
  unsigned char           freq_sel;
  unsigned int            freq; 
  float                   delay_us_f;
  float                   actual_freq;

	do
	{
	  printf ("\Select freq- 0:25M, 1:16.67M, 2:8M, 3:4M, 4:freq in Hz <= 500000\r\n");
	  scanf("%hhu",&freq_sel);
	}while (freq_sel > 4);
	switch(freq_sel)
	{
		case 0: freq = 25000000;
			printf("  Toggling at 25000000 Hz\r\n");
			toggle_gpio_25MHz();
			break;
		case 1: freq = 16666667;
			printf("  Toggling at 16666667 Hz\r\n");
			toggle_gpio_16MHz();
			break;
		case 2: freq = 8333333;
			printf("  Toggling at 8333333 Hz\r\n");
			toggle_gpio_8MHz();
      //toggle_gpio_multiple60ns(2);
			break;
		case 3: freq = 4166667;
			printf("  Toggling at 4166667 Hz\r\n");
			toggle_gpio_4MHz();
      //toggle_gpio_multiple60ns(2);
			break;
    case 5:
			printf("  Toggling at 50000000 Hz\r\n");
			toggle_gpio_50MHz();
			break;
		case 4: 
	    do
			{
			  printf ("Enter freq in Hz <= 500000\r\n");
			  scanf("%u",&freq);
			}while(freq<1 || freq > 500000);

			delay_us_f = 1000000/(freq*2);
			delay_us_i = (unsigned int) (delay_us_f+0.03);
      if(delay_us_i != 0)
      {
        actual_freq = 1000000/(delay_us_i*2);
      }
			printf("  Toggling at freq = %f, delay = %uuS\r\n", actual_freq, delay_us_i);         
			toggle_gpio_delay(delay_us_i);
			break;
  default:
      break;
	}   
}

__attribute__((optimize("00"))) int main(void)
{ 
  unsigned char           is_generator;
  volatile unsigned int*  PINMODE0;
	
  PINMODE0  = (volatile unsigned int*) 0x4002C040;
  *PINMODE0 = 0xFFFFFFFF;

  do
	{
		printf ("\r\n\r\nEnter 0 for signal generation, 1 for sampling:\r\n");
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
