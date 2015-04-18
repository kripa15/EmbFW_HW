#include "types.h"
#include "mbed_hw.h"

void main()
{
  volatile gpio_reg_t*  gpio_mask0 = NULL;
  volatile gpio_reg_t*  gpio_dir0  = NULL;
  volatile gpio_reg_t*  gpio_set0  = NULL;
  volatile gpio_reg_t*  gpio_clr0  = NULL;

  gpio_mask0 = (gpio_reg_t*)FIO0MASK;
  gpio_dir0  = (gpio_reg_t*)FIO0DIR;
  gpio_set0  = (gpio_reg_t*)FIO0SET;
  gpio_clr0  = (gpio_reg_t*)FIO0CLR;
  // Mask out all GPIO but pin6.
  // Mask out all GPIO but pin6.
	gpio_mask0->reg = 0xFFFFFFFF;
  gpio_mask0->pins_t.pin6  = 0;
  // Set gpio pin 6 as output pin.
  gpio_dir0->pins_t.pin6    = 1;

  while (1)
  {
    gpio_set0->pins_t.pin6 = 1;
    
    gpio_clr0->pins_t.pin6 = 1; 
  }

}

