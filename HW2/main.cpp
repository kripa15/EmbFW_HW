// HW01
// Assigned Dip pin# 29 
// port 0, pin 5 

#include<stdint.h>
/* GPIOs                                                                      */
#define LPC_GPIO_BASE         (0x2009C000UL)

/*!< Defines 'read / write' permissions              */
#define     __IO    volatile             
#define     __O    volatile             

/*
DIR   0x00
RSVD[3]
MASK  0x10
PIN   0x14
SET   0x18
CLR   0x1c
*/
typedef struct
{
  union {
    __IO uint32_t FIODIR;
    struct {
      __IO uint16_t FIODIRL;
      __IO uint16_t FIODIRH;
    };
    struct {
      __IO uint8_t  FIODIR0;
      __IO uint8_t  FIODIR1;
      __IO uint8_t  FIODIR2;
      __IO uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    __IO uint32_t FIOMASK;
    struct {
      __IO uint16_t FIOMASKL;
      __IO uint16_t FIOMASKH;
    };
    struct {
      __IO uint8_t  FIOMASK0;
      __IO uint8_t  FIOMASK1;
      __IO uint8_t  FIOMASK2;
      __IO uint8_t  FIOMASK3;
    };
  };
  union {
    __IO uint32_t FIOPIN;
    struct {
      __IO uint16_t FIOPINL;
      __IO uint16_t FIOPINH;
    };
    struct {
      __IO uint8_t  FIOPIN0;
      __IO uint8_t  FIOPIN1;
      __IO uint8_t  FIOPIN2;
      __IO uint8_t  FIOPIN3;
    };
  };
  union {
    __IO uint32_t FIOSET;
    struct {
      __IO uint16_t FIOSETL;
      __IO uint16_t FIOSETH;
    };
    struct {
      __IO uint8_t  FIOSET0;
      __IO uint8_t  FIOSET1;
      __IO uint8_t  FIOSET2;
      __IO uint8_t  FIOSET3;
    };
  };
  union {
    __O  uint32_t FIOCLR;
    struct {
      __O  uint16_t FIOCLRL;
      __O  uint16_t FIOCLRH;
    };
    struct {
      __O  uint8_t  FIOCLR0;
      __O  uint8_t  FIOCLR1;
      __O  uint8_t  FIOCLR2;
      __O  uint8_t  FIOCLR3;
    };
  };
} LPC_GPIO_TypeDef;

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



//__asm 
int gpio_sample(void);          // prototype declaration


void toggle_gpio(void)
{
 int i,j;

 register unsigned char mask = (1 << 2);
 LPC_GPIO1->FIODIR2 = mask;
 while (1) 
 { 
 LPC_GPIO1->FIOSET2 = mask;
 for(i=0;i<100000;i++){i++;i--;}
 LPC_GPIO1->FIOCLR2 = mask;
 for(i=0;i<100000;i++){i++;i--;}
 }

}

//__asm 
void sample_gpio(void)
{
 unsigned char sample_arr[20];
// register unsigned char mask = (1 << 2);
 register unsigned char mask = (1 << 6);
// volatile 
register unsigned char reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8,reg9,reg10;


 // set gpio port 0 as input
 LPC_GPIO0->FIODIR0 = 0;
 
 // read into registers 
 reg1= LPC_GPIO0->FIOPIN0;
 reg2= LPC_GPIO0->FIOPIN0;
 reg3= LPC_GPIO0->FIOPIN0;
 reg4= LPC_GPIO0->FIOPIN0;
 reg5= LPC_GPIO0->FIOPIN0;
 reg6= LPC_GPIO0->FIOPIN0;
 reg7= LPC_GPIO0->FIOPIN0;
 reg8= LPC_GPIO0->FIOPIN0;
 reg9= LPC_GPIO0->FIOPIN0;
 reg10= LPC_GPIO0->FIOPIN0;

 // read into array
 sample_arr[0] = reg1;
 sample_arr[1] = reg2;
 sample_arr[3] = reg3;
 sample_arr[4] = reg4;
 sample_arr[5] = reg5;
 sample_arr[6] = reg6;
 sample_arr[7] = reg7;
 sample_arr[8] = reg8;
 sample_arr[9] = reg9;
 sample_arr[10] = reg10;

 

}

void sample_gpio_asm()
{
__asm__ __volatile__(
  "LDR     R1, =0x2009C014\n\t"
  "LDR     R2, =0x2009C014"

);
}
int main(void)
{ 
#ifdef GPIO_OUT
 toggle_gpio();
#else
 sample_gpio();
 //sample_gpio_asm();
#endif
 return 0;
}
