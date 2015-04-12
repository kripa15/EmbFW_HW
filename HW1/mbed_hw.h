#ifndef __MBED_HW_H
#define __MBED_HW_H




// GPIO Direction Control Registers - 32 bits : 0 is input, 1 is output

#define FIO0DIR 	0x2009C000
#define FIO1DIR 	0x2009C020
#define FIO2DIR 	0x2009C040
#define FIO3DIR 	0x2009C060
#define FIO4DIR 	0x2009C080

// GPIO Set Registers - 32 bits : 0 is o/p unchanged, 1 - pin set to HIGH

#define FIO0SET 	0x2009C018
#define FIO1SET		0x2009C038
#define FIO2SET		0x2009C058
#define FIO3SET		0x2009C078
#define FIO4SET		0x2009C098

// GPIO Clr Registers - 32 bits : 0 is o/p unchanged, 1 - pin set to LOW

#define FIO0CLR 	0x2009C01C
#define FIO1CLR		0x2009C03C
#define FIO2CLR		0x2009C05C
#define FIO3CLR		0x2009C07C
#define FIO4CLR		0x2009C09C

// GPIO Mask Register - 32 bits : 0 is non-masked, 1 - masked

#define FIO0MASK 	0x2009C010
#define FIO1MASK	0x2009C030
#define FIO2MASK	0x2009C050
#define FIO3MASK	0x2009C070
#define FIO4MASK	0x2009C090


#define GPIOMASK_PIN6_SEL   0xFFFFFFBF
//#define GPIOSEL_PIN6_SEL    (~GPIOMASK_PIN6_SEL)

// GPIO register format - assuming little endian
typedef union _gpio_reg_u
{
  struct{
  // reg 0
  unsigned int pin0  : 1;
  unsigned int pin1  : 1;
  unsigned int pin2  : 1;
  unsigned int pin3  : 1;
  unsigned int pin4  : 1;
  unsigned int pin5  : 1;
  unsigned int pin6  : 1;
  unsigned int pin7  : 1;

  // reg 1
  unsigned int pin8  : 1;
  unsigned int pin9  : 1;
  unsigned int pin10 : 1;
  unsigned int pin11 : 1;
  unsigned int pin12 : 1;
  unsigned int pin13 : 1;
  unsigned int pin14 : 1;
  unsigned int pin15 : 1;

  // reg 2
  unsigned int pin16 : 1;
  unsigned int pin17 : 1;
  unsigned int pin18 : 1;
  unsigned int pin19 : 1;
  unsigned int pin20 : 1;
  unsigned int pin21 : 1;
  unsigned int pin22 : 1;
  unsigned int pin23 : 1;

  // reg 3
  unsigned int pin24 : 1;
  unsigned int pin25 : 1;
  unsigned int pin26 : 1;
  unsigned int pin27 : 1;
  unsigned int pin28 : 1;
  unsigned int pin29 : 1;
  unsigned int pin30 : 1;
  unsigned int pin31 : 1;
}pins_t;

unsigned int reg;
  
} gpio_reg_t;

#endif
